#include <thread>
#include <iostream>
#include <list>
#include <queue>
#include <mutex>
#include <condition_variable>
//
//std::list<int> l;
//std::mutex gMutex; // 全局mutex对象，线程会争抢该资源，第一个抢到该资源的线程可以继续执行
//
//void mutexTest()
//{
//    std::thread::id id = std::this_thread::get_id();
//
//    // 线程在这一句争抢mutext，第一个抢到的线程将其锁住，其他线程没抢到，在此处阻塞等待
//    gMutex.lock(); 
//
//    for (int k(0); k < 20; ++k)
//    {
//        l.push_back(k);
//    }
//
//    // 用完了要解锁，阻塞在lock()处的线程继续争抢
//    gMutex.unlock(); 
//
//    // 假如之后还有一些语句要执行，但与共享变量无关，要提前释放mutex，锁的范围太大会降低程序效率
//    // ##########################
//    // statments unrelated to l
//    // ##########################
//}
//
//void guardTest()
//{
//    std::thread::id id = std::this_thread::get_id();
//
//    // 使用guard对象将mutex上锁，第一个锁上mutex的线程得以继续执行，后来的mutex则在该语句上阻塞，
//    // 等待mutex被释放，当线程执行完退出该函数时，guard因为是局部对象所以会被自动销毁，同时自动解锁
//    // 它守护的mutex，这样就避免了mutex没有释放的问题
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

std::mutex gMutex; // 全局mutex对象
std::condition_variable gCV;  // 全局条件变量
std::queue<int> queue; 
bool ready = false; // 等待运行的信号，当ready为true时子线程才启动

void produce()
{
    int good = 0;
    std::thread::id id = std::this_thread::get_id();

    std::unique_lock<std::mutex> lock(gMutex); // 此时并未对gMutex上锁

    std::cout << "Producer " << id << " enter!" << std::endl;

    while (!ready) // 当ready为false时
    {
        std::cout << "Producer " << id << " wait!" << std::endl;

        // 线程在此处等待通知信号，当得到信号时，就尝试争抢lock对gMutex上锁
        // 抢到的线程往下执行，发现ready已经为true，退出循环继续
        // 没抢到的线程则在此处阻塞，等待锁被释放时继续争抢
        gCV.wait(lock); 
    }
    // 相当于：gCV.wait(lock, [] {return ready;}); 

    // 走到这里说明已经得到lock对gMutex上了锁
    std::cout << "Producer " << id << " start!" << std::endl;
    
    while (true)
    {
        queue.push(good);
        lock.unlock();

        std::cout << "Producer " << id << ": " << good << std::endl;
        ++good;

        // 休息一会儿，不要一直争抢CPU使用
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // 休息完毕，尝试获得锁，以便继续往队列中放入商品
        lock.lock();
    }
}

void consume()
{
    int good = 0;
    std::thread::id id = std::this_thread::get_id();

    std::unique_lock<std::mutex> lock(gMutex); // 此时并未对gMutex上锁

    std::cout << "Cunsumer " << id << " enter!" << std::endl;

    while (!ready)
    {
        std::cout << "Cunsumer " << id << " wait!" << std::endl;
        gCV.wait(lock);
    }
    
    // 走到这里说明已经得到lock对gMutex上了锁
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
    // 准备工作
    // ##########################

    // 使用lock_guard保护信号变量ready值的修改
    {
        std::lock_guard<std::mutex> lock(gMutex);
        ready = true;
        std::cout << "Ready go!" << std::endl;
        gCV.notify_all(); // 通知所有通过gCV等待信号的线程，可以退出等待继续运行
    }
   
    p1.join();
    p2.join();
    c1.join();

    return 0;
}
