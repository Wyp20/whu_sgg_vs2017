/* 
   本例字符集设置为unicode，每个字符编码需要2个字节保存，所以代码中使用宽字符wchar_t
   wchar_t与char的功能一样，char使用1字节存放，wchar_t使用2字节存放
   对于一个char *p，当p+1时移动一个字节，指向下一个char类型的字符
   对于wchar_t *p，当p+1时移动两个字节，指向下一个wchar_t类型的字符
   可以像使用char a[10]一样使用宽字符数组wchar_t wa[10]，wa[0]表示第一个宽字符，wa[1]表示第二个宽字符
   宽字符串常量的前面需要加一个大写字母L，如L"Hello world!"，宽字符串的长度和实际占用的字节数是不一样的
   示例参见arrayLenth()
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

// 全局变量，存放从books.txt中读入的书籍信息
std::map<std::wstring, Book> books;

// 缓冲区存放字符个数
const unsigned int BUFFLEN = 256;

// 功能：从文本文件中读取信息，转换成Book对象存放在books中
// 输入参数：const std::wstring &file：文件名
void readBookInfoFromTxt(const std::wstring &file)
{
    // 用于打开指定文件的宽字符输入文件流对象，默认文本方式读取，打开标记为ios_base::in
    std::wifstream in(file);

    // 检验文件是否打开成功，不成功则返回
    if (!in.is_open())
    {
        std::wcout << L"Failed to open: " << file << std::endl;
        return;
    }

    // 使用wchar_t只是指明程序中的字符类型数据使用2个字节存放，但存的是哪种字符编码与wchar_t无关
    // 测试使用的books.txt是utf-8编码，这里指定中文区域设置，以及UTF-8转换器
    in.imbue(std::locale(std::locale("zh-CN"), new std::codecvt_utf8<wchar_t>()));

    // buf：缓冲区，存放读进来的每一行内容，总字节数为BUFFLEN*sizeof(wchar_t)，但只能存BUFFLEN个宽字符
    wchar_t buf[BUFFLEN];

    // 文本文件读入时，使用eof()函数判断是否已经读完：true--读完了，false--未读完
    while (!in.eof())
    {
        // 读入一行放在buf中，自动填充字符串结束符'\0'，最多读入BUFFLEN-1个字符，最后一个字符存放结束符'\0'
        in.getline(buf, BUFFLEN);

        // 通过buf中的内容构造一个Book对象，并将该对象放在map容器books中，以书籍编号做为key，书籍对象作为value
        Book book(buf);
        books.insert(std::make_pair(book._no, book));

        // 将缓冲区中读入的内容重置为'\0'
        std::wmemset(buf, L'\0', std::wcslen(buf));
    }

    // 读入结束后关闭文件
    in.close();
}

// 功能：将books中的Book对象存入文本文件中
// 输入参数：const std::wstring &file：文件名
void writeBookInfoToTxt(const std::wstring &file)
{
    // 用于打开指定文件的宽字符输出文件流对象，默认文本方式写出，打开标记为ios_base::out
    std::wofstream out(file);

    // 检验文件是否打开成功，不成功则返回
    if (!out.is_open())
    {
        std::wcout << L"Failed to open: " << file << std::endl;
        return;
    }

    // 使用wchar_t只是指明程序中的字符类型数据使用2个字节存放，但存的是哪种字符编码与wchar_t无关
    // 测试使用的books.txt是utf-8编码，这里指定中文区域设置，以及UTF-8转换器
    out.imbue(std::locale(std::locale("zh-CN"), new std::codecvt_utf8<wchar_t>()));

    // 在books中查找书籍编号为00001的书，如果找到了，就把该书的信息写出到一个文本文件中，没有找到则写出Not found！
    // 调用map容器的find()成员函数，查找的结果存放在一个迭代器对象中
    std::map<std::wstring, Book>::iterator it = books.find(L"00001");
    if (it != books.end()) // 迭代器对象没有指向结束，说明指向容器中的某个元素，即找到了
    {
        // 通过重载<<，使之可以处理Book类的对象，见book.cpp
        // it->first：引用it所指元素的key，本例中为书籍编号，类型为std::wstring
        // it->second：引用it所指元素的value，本例中为Book类的对象
        out << it->second << std::endl;
    }
    else // 如果迭代器对象指向books的结束位置，说明一直到最后一个元素都没有匹配的结果，即没有找到
    {
        out << std::wstring(L"Not found!") << std::endl;
    }

    // 写出完毕后关闭文件
    out.close();
}

// 功能：从二进制文件中读取信息，转换成Book对象，并将书籍信息打印在命令行窗口中
// 输入参数：const std::wstring &file：文件名
void read_binary(const std::wstring &file)
{
    // 二进制文件可以看成是内存->磁盘文件的映射，写出磁盘时，它将内存中每一个字节的信息直接存放在文件中，读入时，
    // 以指定的数量读入N个字节的信息，因此这里并没有像readBookInfoFromTxt()、writeBookInfoToTxt()那样使
    // 用宽字符文件流，而是使用fstream，以单字节的方式读入
    // 用于打开指定文件的宽字符输入输出文件流对象，需指定标记位：in：读入，binary：二进制方式
    std::fstream in(file, std::ios::in | std::ios::binary);

    // 检验文件是否打开成功，不成功则返回
    if (!in.is_open())
    {
        std::wcout << L"Failed to open: " << file << std::endl;
        return;
    }

    // 在命令行上打印中文，设置一下区域信息
    std::wcout.imbue(std::locale(std::locale("zh-CN")));

    // 本例中二进制文件的格式：字节总数N1+book1信息+字节总数N2+book2信息……
    // 前面的字节总数表示后面的book信息占多少字节，读取时先读取sizeof(int)长度的内容放在len中，即N值
    // 再读取N长度的内容放在buf中
    // len：存放每个book信息所占的字节总数
    int len(0);

    // buf：缓冲区，存放读进来的每一行内容，总字节数为BUFFLEN*sizeof(wchar_t)，但只能存BUFFLEN个宽字符
    wchar_t buf[BUFFLEN];

    // 二进制文件读入时，内部有一个文件指针，以字节为单位向前移动，peek()函数不改变指针，返回指针当前位置
    // EOF表示文件结尾，当文件指针==EOF时表示读完了
    while (in.peek() != EOF)
    {
        // 重置缓冲区，将buf中的字符都替换成'\0'
        std::wmemset(buf, L'\0', 256);

        // 读入sizeof(int)个字节的内容，存放在len中
        in.read((char *)&len, sizeof(int));

        // 读入len个字节的内容，存放在buf中
        in.read((char *)buf, len);

        // 通过buf构造一个Book类的对象
        Book book(buf);

        // 打印该对象中的数据检验读取结果
        std::wcout << book._no << std::endl;
        std::wcout << book._name << std::endl;
        for (auto const & au : book._authors)
        {
            std::wcout << au << ", ";
        }
        std::wcout << std::endl;
        std::wcout << book._press << std::endl;
    }

    // 读入完毕后关闭文件
    in.close();
}

void write_binary(const std::wstring &file)
{
    // 二进制文件可以看成是内存->磁盘文件的映射，写出磁盘时，它将内存中每一个字节的信息直接存放在文件中，读入时，
    // 以指定的数量读入N个字节的信息，因此这里并没有像readBookInfoFromTxt()、writeBookInfoToTxt()那样使
    // 用宽字符文件流，而是使用fstream，以单字节的方式写出
    // 用于打开指定文件的宽字符输入输出文件流对象，需指定标记位：out：写出，binary：二进制方式
    std::fstream out(file, std::ios::out | std::ios::binary);

    // 检验文件是否打开成功，不成功则返回
    if (!out.is_open())
    {
        std::wcout << L"Failed to open: " << file << std::endl;
        return;
    }

    // 宽字符串流，用于把Book对象中的信息连接成一个字符串，方便写出
    std::wstringstream data;

    // 循环容器books中的每一个book对象
    for (auto const & b : books)
    {
        // 书籍信息写出的格式为：书籍编号\t书名\t作者1&作者2&作者3&...\t出版社
        // 每一项信息之间使用tab键隔开，可以有多个作者，每个作者之间用&隔开
        data << b.second._no.c_str() << L"\t" << b.second._name.c_str() << L"\t";

        // 因为有多个作者，这里处理一下：如果不是最后一个作者，后面接&，最后一个作者后面接tab键
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

        // data.str().size()：字符串的长度，以字符为单位（不是以字节为单位），每个字符占sizeof(wchar_t)个字节
        // 所以要乘以sizeof(wchar_t)
        int len = data.str().size() * sizeof(wchar_t);

        // 先写总数，将变量len的地址转换为char*，即从变量len的第一个字节开始写，总共写sizeof(int)个字节的内容
        out.write((const char *)&len, sizeof(int));

        // 再写书籍信息字符串的内容，将字符串的首地址转换成char*，即从字符串流中存放字符串的第一个地址开始写，
        // 总共写len个字节的内容
        out.write((const char *)data.str().c_str(), len);

        // 重复使用字符串流对象data，清空标记位以及重置缓冲区
        data.clear();
        data.str(L"");
    }

    // 写出完毕后关闭文件
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
    // 比较char数组、wchar_t数组、char字符串、wchar_t字符串长度
    arrayLenth();

    // 文本文件读测试：从books.txt读入数据信息存入容器books中
    std::wstring file = L"books.txt";
    readBookInfoFromTxt(file);

    // 文本文件写测试：从books中找到指定编号的书籍，并将其信息写入select.txt
    file = L"select.txt";
    writeBookInfoToTxt(file);

    // 二进制文件写测试：将books中的所有书籍的信息写入books.bin中
    file = L"books.bin";
    write_binary(file);

    // 二进制文件读测试：从books.bin读入所有书籍信息并在命令行中打印
    read_binary(file);

    return 0;
}