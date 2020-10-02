/* 
   �����ַ�������Ϊunicode��ÿ���ַ�������Ҫ2���ֽڱ��棬���Դ�����ʹ�ÿ��ַ�wchar_t
   wchar_t��char�Ĺ���һ����charʹ��1�ֽڴ�ţ�wchar_tʹ��2�ֽڴ��
   ����һ��char *p����p+1ʱ�ƶ�һ���ֽڣ�ָ����һ��char���͵��ַ�
   ����wchar_t *p����p+1ʱ�ƶ������ֽڣ�ָ����һ��wchar_t���͵��ַ�
   ������ʹ��char a[10]һ��ʹ�ÿ��ַ�����wchar_t wa[10]��wa[0]��ʾ��һ�����ַ���wa[1]��ʾ�ڶ������ַ�
   ���ַ���������ǰ����Ҫ��һ����д��ĸL����L"Hello world!"�����ַ����ĳ��Ⱥ�ʵ��ռ�õ��ֽ����ǲ�һ����
   ʾ���μ�arrayLenth()
*/

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <locale>
#include <codecvt>
#include "book.h"

// ȫ�ֱ�������Ŵ�books.txt�ж�����鼮��Ϣ
std::map<std::wstring, Book> books;

// ����������ַ�����
const unsigned int BUFFLEN = 256;

// ���ܣ����ı��ļ��ж�ȡ��Ϣ��ת����Book��������books��
// ���������const std::wstring &file���ļ���
void readBookInfoFromTxt(const std::wstring &file)
{
    // ���ڴ�ָ���ļ��Ŀ��ַ������ļ�������Ĭ���ı���ʽ��ȡ���򿪱��Ϊios_base::in
    std::wifstream in(file);

    // �����ļ��Ƿ�򿪳ɹ������ɹ��򷵻�
    if (!in.is_open())
    {
        std::wcout << L"Failed to open: " << file << std::endl;
        return;
    }

    // ʹ��wchar_tֻ��ָ�������е��ַ���������ʹ��2���ֽڴ�ţ�������������ַ�������wchar_t�޹�
    // ����ʹ�õ�books.txt��utf-8���룬����ָ�������������ã��Լ�UTF-8ת����
    in.imbue(std::locale(std::locale("zh-CN"), new std::codecvt_utf8<wchar_t>()));

    // buf������������Ŷ�������ÿһ�����ݣ����ֽ���ΪBUFFLEN*sizeof(wchar_t)����ֻ�ܴ�BUFFLEN�����ַ�
    wchar_t buf[BUFFLEN];

    // �ı��ļ�����ʱ��ʹ��eof()�����ж��Ƿ��Ѿ����꣺true--�����ˣ�false--δ����
    while (!in.eof())
    {
        // ����һ�з���buf�У��Զ�����ַ���������'\0'��������BUFFLEN-1���ַ������һ���ַ���Ž�����'\0'
        in.getline(buf, BUFFLEN);

        // ͨ��buf�е����ݹ���һ��Book���󣬲����ö������map����books�У����鼮�����Ϊkey���鼮������Ϊvalue
        Book book(buf);
        books.insert(std::make_pair(book._no, book));

        // ���������ж������������Ϊ'\0'
        std::wmemset(buf, L'\0', std::wcslen(buf));
    }

    // ���������ر��ļ�
    in.close();
}

// ���ܣ���books�е�Book��������ı��ļ���
// ���������const std::wstring &file���ļ���
void writeBookInfoToTxt(const std::wstring &file)
{
    // ���ڴ�ָ���ļ��Ŀ��ַ�����ļ�������Ĭ���ı���ʽд�����򿪱��Ϊios_base::out
    std::wofstream out(file);

    // �����ļ��Ƿ�򿪳ɹ������ɹ��򷵻�
    if (!out.is_open())
    {
        std::wcout << L"Failed to open: " << file << std::endl;
        return;
    }

    // ʹ��wchar_tֻ��ָ�������е��ַ���������ʹ��2���ֽڴ�ţ�������������ַ�������wchar_t�޹�
    // ����ʹ�õ�books.txt��utf-8���룬����ָ�������������ã��Լ�UTF-8ת����
    out.imbue(std::locale(std::locale("zh-CN"), new std::codecvt_utf8<wchar_t>()));

    // ��books�в����鼮���Ϊ00001���飬����ҵ��ˣ��ͰѸ������Ϣд����һ���ı��ļ��У�û���ҵ���д��Not found��
    // ����map������find()��Ա���������ҵĽ�������һ��������������
    std::map<std::wstring, Book>::iterator it = books.find(L"00001");
    if (it != books.end()) // ����������û��ָ�������˵��ָ�������е�ĳ��Ԫ�أ����ҵ���
    {
        // ͨ������<<��ʹ֮���Դ���Book��Ķ��󣬼�book.cpp
        // it->first������it��ָԪ�ص�key��������Ϊ�鼮��ţ�����Ϊstd::wstring
        // it->second������it��ָԪ�ص�value��������ΪBook��Ķ���
        out << it->second << std::endl;
    }
    else // �������������ָ��books�Ľ���λ�ã�˵��һֱ�����һ��Ԫ�ض�û��ƥ��Ľ������û���ҵ�
    {
        out << std::wstring(L"Not found!") << std::endl;
    }

    // д����Ϻ�ر��ļ�
    out.close();
}

// ���ܣ��Ӷ������ļ��ж�ȡ��Ϣ��ת����Book���󣬲����鼮��Ϣ��ӡ�������д�����
// ���������const std::wstring &file���ļ���
void read_binary(const std::wstring &file)
{
    // �������ļ����Կ������ڴ�->�����ļ���ӳ�䣬д������ʱ�������ڴ���ÿһ���ֽڵ���Ϣֱ�Ӵ�����ļ��У�����ʱ��
    // ��ָ������������N���ֽڵ���Ϣ��������ﲢû����readBookInfoFromTxt()��writeBookInfoToTxt()����ʹ
    // �ÿ��ַ��ļ���������ʹ��fstream���Ե��ֽڵķ�ʽ����
    // ���ڴ�ָ���ļ��Ŀ��ַ���������ļ���������ָ�����λ��in�����룬binary�������Ʒ�ʽ
    std::fstream in(file, std::ios::in | std::ios::binary);

    // �����ļ��Ƿ�򿪳ɹ������ɹ��򷵻�
    if (!in.is_open())
    {
        std::wcout << L"Failed to open: " << file << std::endl;
        return;
    }

    // ���������ϴ�ӡ���ģ�����һ��������Ϣ
    std::wcout.imbue(std::locale(std::locale("zh-CN")));

    // �����ж������ļ��ĸ�ʽ���ֽ�����N1+book1��Ϣ+�ֽ�����N2+book2��Ϣ����
    // ǰ����ֽ�������ʾ�����book��Ϣռ�����ֽڣ���ȡʱ�ȶ�ȡsizeof(int)���ȵ����ݷ���len�У���Nֵ
    // �ٶ�ȡN���ȵ����ݷ���buf��
    // len�����ÿ��book��Ϣ��ռ���ֽ�����
    int len(0);

    // buf������������Ŷ�������ÿһ�����ݣ����ֽ���ΪBUFFLEN*sizeof(wchar_t)����ֻ�ܴ�BUFFLEN�����ַ�
    wchar_t buf[BUFFLEN];

    // �������ļ�����ʱ���ڲ���һ���ļ�ָ�룬���ֽ�Ϊ��λ��ǰ�ƶ���peek()�������ı�ָ�룬����ָ�뵱ǰλ��
    // EOF��ʾ�ļ���β�����ļ�ָ��==EOFʱ��ʾ������
    while (in.peek() != EOF)
    {
        // ���û���������buf�е��ַ����滻��'\0'
        std::wmemset(buf, L'\0', 256);

        // ����sizeof(int)���ֽڵ����ݣ������len��
        in.read((char *)&len, sizeof(int));

        // ����len���ֽڵ����ݣ������buf��
        in.read((char *)buf, len);

        // ͨ��buf����һ��Book��Ķ���
        Book book(buf);

        // ��ӡ�ö����е����ݼ����ȡ���
        std::wcout << book._no << std::endl;
        std::wcout << book._name << std::endl;
        for (auto const & au : book._authors)
        {
            std::wcout << au << ", ";
        }
        std::wcout << std::endl;
        std::wcout << book._press << std::endl;
    }

    // ������Ϻ�ر��ļ�
    in.close();
}

void write_binary(const std::wstring &file)
{
    // �������ļ����Կ������ڴ�->�����ļ���ӳ�䣬д������ʱ�������ڴ���ÿһ���ֽڵ���Ϣֱ�Ӵ�����ļ��У�����ʱ��
    // ��ָ������������N���ֽڵ���Ϣ��������ﲢû����readBookInfoFromTxt()��writeBookInfoToTxt()����ʹ
    // �ÿ��ַ��ļ���������ʹ��fstream���Ե��ֽڵķ�ʽд��
    // ���ڴ�ָ���ļ��Ŀ��ַ���������ļ���������ָ�����λ��out��д����binary�������Ʒ�ʽ
    std::fstream out(file, std::ios::out | std::ios::binary);

    // �����ļ��Ƿ�򿪳ɹ������ɹ��򷵻�
    if (!out.is_open())
    {
        std::wcout << L"Failed to open: " << file << std::endl;
        return;
    }

    // ���ַ����������ڰ�Book�����е���Ϣ���ӳ�һ���ַ���������д��
    std::wstringstream data;

    // ѭ������books�е�ÿһ��book����
    for (auto const & b : books)
    {
        // �鼮��Ϣд���ĸ�ʽΪ���鼮���\t����\t����1&����2&����3&...\t������
        // ÿһ����Ϣ֮��ʹ��tab�������������ж�����ߣ�ÿ������֮����&����
        data << b.second._no.c_str() << L"\t" << b.second._name.c_str() << L"\t";

        // ��Ϊ�ж�����ߣ����ﴦ��һ�£�����������һ�����ߣ������&�����һ�����ߺ����tab��
        int i(0), last(b.second._authors.size() - 1);
        for (auto const & au : b.second._authors)
        {
            if (i == last)
            {
                data << au.c_str() << L"\t";
            }
            else
            {
                data << au.c_str() << L"&";
            }
            ++i;
        }
        data << b.second._press.c_str();

        // data.str().size()���ַ����ĳ��ȣ����ַ�Ϊ��λ���������ֽ�Ϊ��λ����ÿ���ַ�ռsizeof(wchar_t)���ֽ�
        // ����Ҫ����sizeof(wchar_t)
        int len = data.str().size() * sizeof(wchar_t);

        // ��д������������len�ĵ�ַת��Ϊchar*�����ӱ���len�ĵ�һ���ֽڿ�ʼд���ܹ�дsizeof(int)���ֽڵ�����
        out.write((const char *)&len, sizeof(int));

        // ��д�鼮��Ϣ�ַ��������ݣ����ַ������׵�ַת����char*�������ַ������д���ַ����ĵ�һ����ַ��ʼд��
        // �ܹ�дlen���ֽڵ�����
        out.write((const char *)data.str().c_str(), len);

        // �ظ�ʹ���ַ���������data����ձ��λ�Լ����û�����
        data.clear();
        data.str(L"");
    }

    // д����Ϻ�ر��ļ�
    out.close();
}

void arrayLenth()
{
    char a[] = { "12345678" };
    wchar_t w[] = { L"12345678" };

    std::wcout << L"Bytes of a: " << sizeof(a) << std::endl;
    std::wcout << L"Bytes of w: " << sizeof(w) << std::endl;
    std::wcout << L"String lenth of a: " << std::strlen(a) << std::endl;
    std::wcout << L"String lenth of w: " << std::wcslen(w) << std::endl;
}

int main(void)
{
    // �Ƚ�char���顢wchar_t���顢char�ַ�����wchar_t�ַ�������
    arrayLenth();

    // �ı��ļ������ԣ���books.txt����������Ϣ��������books��
    std::wstring file = L"books.txt";
    readBookInfoFromTxt(file);

    // �ı��ļ�д���ԣ���books���ҵ�ָ����ŵ��鼮����������Ϣд��select.txt
    file = L"select.txt";
    writeBookInfoToTxt(file);

    // �������ļ�д���ԣ���books�е������鼮����Ϣд��books.bin��
    file = L"books.bin";
    write_binary(file);

    // �������ļ������ԣ���books.bin���������鼮��Ϣ�����������д�ӡ
    read_binary(file);

    return 0;
}