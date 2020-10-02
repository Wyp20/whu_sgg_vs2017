#include <vector>
#include <iostream>
#include <string>
#include <regex>
#include "book.h"

// 一本书的信息不论是文本格式存放在文本文件中，还是二进制方式存放在二进制文件中，都遵循以下格式：
// 书籍编号\t书名\t作者1&作者2&作者3&...\t出版社
// 每一项信息之间使用tab键隔开，可以有多个作者，每个作者之间用&隔开

Book::Book(const wchar_t *buf)
{
    // 取缓冲区buf中字符串的长度，遇到'\0'时结束，所以若buf中没有'\0'该函数将会出错
    size_t len = std::wcslen(buf);

    // C++标准模板库没有提供分割字符串的函数，有多种方法可以实现类似split()的功能，本例中使用的是
    // 正则表达式方法。正则表达式对象wc_re的值为tab键，用来分割buf中字符串的每一项
    std::wregex wc_re(L"\\t");

    // 构造了一个wcregex_token_iterator对象，它从buf的首字节开始，一直到最后一个字节，以满足wc_re（即一个
    // tab键）规则的字符串为分隔符，将buf中的内容进行分割，分割后得到的子字符串存放在vector容器v中
    std::vector<std::wstring> v(std::wcregex_token_iterator(buf, buf + len, wc_re, -1),
                                std::wcregex_token_iterator());

    _no = v[0];     // v的第一个元素是书籍编号
    _name = v[1];   // v的第二个元素是书名

    // 把正则表达式换成"&"，用于分割多个作者，通过assign()放在_authors中
    wc_re = L"&";
    _authors.assign(std::wsregex_token_iterator(v[2].begin(), v[2].end(), wc_re, -1),
                    std::wsregex_token_iterator());

    _press = v[3];  // v的第四个元素是出版社
}

// 重载<<，使其可以直接写出Book对象
std::wofstream& operator<<(std::wofstream& out, const Book& b)
{
    // 先写：书籍编号\t书名\t
    out << b._no << L"\t" << b._name << L"\t";

    // 因为有多个作者，输出时根据是否为最后一个作者，其后接的分隔符不一样
    // 不是最后一个作者，用"&"连接，最后一个作者接tab键，如：作者1&作者2&作者3\t
    int i(0), last(b._authors.size() - 1);
    for (auto const &s : b._authors)
    {
        i == last ? (out << s << L"\t") : (out << s << L"&");
        ++i;
    }
    
    // 最后写出版社
    out << b._press;

    // 返回wofstream对象实现链式编程
    return out;
}