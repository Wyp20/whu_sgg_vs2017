#include "mytemplate.h"

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

int main(void)
{
    int x(10), y(5);
    swap(x, y);

    double m(1.2), n(4.3);
    swap<double>(m, n);

    Pair p1(2, 2.0), p2(1, 1.0);
    std::cout << (p1<p2) << std::endl;

    // ########## vector #############
    std::vector<int> vec;
    for (int i(0); i < 10; ++i)
    {
        vec.push_back(i);
    }

    std::vector<int>::iterator it = vec.begin();
    ++it;
    --it;
    vec.insert(it, 100);
    //std::cout << *it << std::endl;  // �������ݺ������ʧЧ

    it = vec.begin();
    std::cout << *it << std::endl;

    it = it + 2;
    vec.erase(it);
    //std::cout << *it << std::endl;  // ɾ�����ݺ������ʧЧ


    // ########## list #############
    std::list<int> l;
    for (int i(0); i < 10; ++i)
    {
        l.push_back(i);
    }
    for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        if (*it != 6)
        {
            continue;
        }
        
        l.erase(it);
        break;
    }

    // ########## map #############
    std::map<int, std::string> members;
    members.insert(std::make_pair(12005, "��С��"));
    members.insert(std::make_pair(12002, "��С��"));
    members.insert(std::make_pair(12012, "��ʮ��"));
    members.insert(std::make_pair(12001, "��Сһ"));
    members.insert(std::make_pair(12009, "��С��"));
    members[12007] = "��С��"; // ���members��û��12007���key��Ӧ�����ݣ�����ӣ�����У����޸���value
    
    std::map<int, std::string>::iterator itMap;
    for (itMap = members.begin(); itMap != members.end(); ++itMap)
    {
        std::cout << itMap->first << ": " << itMap->second << std::endl;
    }

    if ((itMap = members.find(12001)) == members.end())
    {
        std::cout << "���޴���!" << std::endl;
    }
    else
    {
        std::cout << "�ҵ���" << itMap->first << ": " << itMap->second << std::endl;
    }

    std::cout << members[12045] << std::endl; // ��Ӻ��valueΪ""

    return 0;
}
