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
    //std::cout << *it << std::endl;  // 插入数据后迭代器失效

    it = vec.begin();
    std::cout << *it << std::endl;

    it = it + 2;
    vec.erase(it);
    //std::cout << *it << std::endl;  // 删除数据后迭代器失效


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
    members.insert(std::make_pair(12005, "张小五"));
    members.insert(std::make_pair(12002, "张小二"));
    members.insert(std::make_pair(12012, "张十二"));
    members.insert(std::make_pair(12001, "张小一"));
    members.insert(std::make_pair(12009, "张小九"));
    members[12007] = "张小七"; // 如果members中没有12007这个key对应的数据，则添加，如果有，则修改其value
    
    std::map<int, std::string>::iterator itMap;
    for (itMap = members.begin(); itMap != members.end(); ++itMap)
    {
        std::cout << itMap->first << ": " << itMap->second << std::endl;
    }

    if ((itMap = members.find(12001)) == members.end())
    {
        std::cout << "查无此人!" << std::endl;
    }
    else
    {
        std::cout << "找到了" << itMap->first << ": " << itMap->second << std::endl;
    }

    std::cout << members[12045] << std::endl; // 添加后的value为""

    return 0;
}
