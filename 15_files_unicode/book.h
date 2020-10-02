#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <fstream>
#include <vector>

class Book
{
    friend std::wofstream& operator<<(std::wofstream& out, const Book& b);

public:
    std::wstring _no;                   // �鼮���
    std::wstring _name;                 // ����
    std::vector<std::wstring> _authors; // ���ߣ����ж����
    std::wstring _press;                // ������

public:
    Book() : _no(0) {}
    Book(const wchar_t *buf);
};

std::wofstream& operator<<(std::wofstream& out, const Book& b);

#endif // !CFILE_H_

