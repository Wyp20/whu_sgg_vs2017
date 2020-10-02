#include <thread>
#include <iostream>
#include <list>
#include <queue>
#include <mutex>
#include <condition_variable>
//
//std::list<int> l;
//std::mutex gMutex; // ȫ��mutex�����̻߳���������Դ����һ����������Դ���߳̿��Լ���ִ��
//
//void mutexTest()
//{
//    std::thread::id id = std::this_thread::get_id();
//
//    // �߳�����һ������mutext����һ���������߳̽�����ס�������߳�û�������ڴ˴������ȴ�
//    gMutex.lock(); 
//
//    for (int k(0); k < 20; ++k)
//    {
//        l.push_back(k);
//    }
//
//    // ������Ҫ������������lock()�����̼߳�������
//    gMutex.unlock(); 
//
//    // ����֮����һЩ���Ҫִ�У����빲������޹أ�Ҫ��ǰ�ͷ�mutex�����ķ�Χ̫��ή�ͳ���Ч��
//    // ##########################
//    // statments unrelated to l
//    // ##########################
//}
//
//void guardTest()
//{
//    std::thread::id id = std::this_thread::get_id();
//
//    // ʹ��guard����mutex��������һ������mutex���̵߳��Լ���ִ�У�������mutex���ڸ������������
//    // �ȴ�mutex���ͷţ����߳�ִ�����˳��ú���ʱ��guard��Ϊ�Ǿֲ��������Իᱻ�Զ����٣�ͬʱ�Զ�����
//    // ���ػ���mutex�������ͱ�����mutexû���ͷŵ�����
//    {
//        std::lock_guard<std::mutex> guard(gMutex);
//
//        for (int k(0); k < 20; ++k)
//        {
//            l.push_back(k);
//        }
//    }// unlock
//}
//
//int main(void)
//{
//    //std::thread t1(mutexTest), t2(mutexTest);
//    std::thread t1(guardTest), t2(guardTest);
//
//    t1.join();
//    t2.join();
//
//    std::cout << "size(l): " << l.size() << std::endl;
//
//    for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
//    {
//        std::cout << *it << " ";
//    }
//
//    return 0;
//}

std::mutex gMutex; // ȫ��mutex����
std::condition_variable gCV;  // ȫ����������
std::queue<int> queue; 
bool ready = false; // �ȴ����е��źţ���readyΪtrueʱ���̲߳�����

void produce()
{
    int good = 0;
    std::thread::id id = std::this_thread::get_id();

    std::unique_lock<std::mutex> lock(gMutex); // ��ʱ��δ��gMutex����

    std::cout << "Producer " << id << " enter!" << std::endl;

    while (!ready) // ��readyΪfalseʱ
    {
        std::cout << "Producer " << id << " wait!" << std::endl;

        // �߳��ڴ˴��ȴ�֪ͨ�źţ����õ��ź�ʱ���ͳ�������lock��gMutex����
        // �������߳�����ִ�У�����ready�Ѿ�Ϊtrue���˳�ѭ������
        // û�������߳����ڴ˴��������ȴ������ͷ�ʱ��������
        gCV.wait(lock); 
    }
    // �൱�ڣ�gCV.wait(lock, [] {return ready;}); 

    // �ߵ�����˵���Ѿ��õ�lock��gMutex������
    std::cout << "Producer " << id << " start!" << std::endl;
    
    while (true)
    {
        queue.push(good);
        lock.unlock();

        std::cout << "Producer " << id << ": " << good << std::endl;
        ++good;

        // ��Ϣһ�������Ҫһֱ����CPUʹ��
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // ��Ϣ��ϣ����Ի�������Ա�����������з�����Ʒ
        lock.lock();
    }
}

void consume()
{
    int good = 0;
    std::thread::id id = std::this_thread::get_id();

    std::unique_lock<std::mutex> lock(gMutex); // ��ʱ��δ��gMutex����

    std::cout << "Cunsumer " << id << " enter!" << std::endl;

    while (!ready)
    {
        std::cout << "Cunsumer " << id << " wait!" << std::endl;
        gCV.wait(lock);
    }
    
    // �ߵ�����˵���Ѿ��õ�lock��gMutex������
    std::cout << "Cunsumer " << id << " start!" << std::endl;

    while (true)
    {
        if (!queue.empty())
        {
            good = queue.front();
            queue.pop();
            std::cout << "Cunsumer " << id << ": " << good << std::endl;   
        }
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        lock.lock();
    }
}

int main(void)
{
    std::thread p1(produce), p2(produce), c1(consume);

    // ##########################
    // ׼������
    // ##########################

    // ʹ��lock_guard�����źű���readyֵ���޸�
    {
        std::lock_guard<std::mutex> lock(gMutex);
        ready = true;
        std::cout << "Ready go!" << std::endl;
        gCV.notify_all(); // ֪ͨ����ͨ��gCV�ȴ��źŵ��̣߳������˳��ȴ���������
    }
   
    p1.join();
    p2.join();
    c1.join();

    return 0;
}
