#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <fstream>
#include <vector>

class Book
{
    friend std::wofstream& operator<<(std::wofstream& out, const Book& b);

public:
    std::wstring _no;                   // 书籍编号
    std::wstring _name;                 // 书名
    std::vector<std::wstring> _authors; // 作者（可有多个）
    std::wstring _press;                // 出版社

public:
    Book() : _no(0) {}
    Book(const wchar_t *buf);
};

std::wofstream& operator<<(std::wofstream& out, const Book& b);

#endif // !CFILE_H_

