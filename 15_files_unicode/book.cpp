#include <vector>
#include <iostream>
#include <string>
#include <regex>
#include "book.h"

// һ�������Ϣ�������ı���ʽ������ı��ļ��У����Ƕ����Ʒ�ʽ����ڶ������ļ��У�����ѭ���¸�ʽ��
// �鼮���\t����\t����1&����2&����3&...\t������
// ÿһ����Ϣ֮��ʹ��tab�������������ж�����ߣ�ÿ������֮����&����

Book::Book(const wchar_t *buf)
{
    // ȡ������buf���ַ����ĳ��ȣ�����'\0'ʱ������������buf��û��'\0'�ú����������
    size_t len = std::wcslen(buf);

    // C++��׼ģ���û���ṩ�ָ��ַ����ĺ������ж��ַ�������ʵ������split()�Ĺ��ܣ�������ʹ�õ���
    // ������ʽ������������ʽ����wc_re��ֵΪtab���������ָ�buf���ַ�����ÿһ��
    std::wregex wc_re(L"\\t");

    // ������һ��wcregex_token_iterator��������buf�����ֽڿ�ʼ��һֱ�����һ���ֽڣ�������wc_re����һ��
    // tab����������ַ���Ϊ�ָ�������buf�е����ݽ��зָ�ָ��õ������ַ��������vector����v��
    std::vector<std::wstring> v(std::wcregex_token_iterator(buf, buf + len, wc_re, -1),
                                std::wcregex_token_iterator());

    _no = v[0];     // v�ĵ�һ��Ԫ�����鼮���
    _name = v[1];   // v�ĵڶ���Ԫ��������

    // ��������ʽ����"&"�����ڷָ������ߣ�ͨ��assign()����_authors��
    wc_re = L"&";
    _authors.assign(std::wsregex_token_iterator(v[2].begin(), v[2].end(), wc_re, -1),
                    std::wsregex_token_iterator());

    _press = v[3];  // v�ĵ��ĸ�Ԫ���ǳ�����
}

// ����<<��ʹ�����ֱ��д��Book����
std::wofstream& operator<<(std::wofstream& out, const Book& b)
{
    // ��д���鼮���\t����\t
    out << b._no << L"\t" << b._name << L"\t";

    // ��Ϊ�ж�����ߣ����ʱ�����Ƿ�Ϊ���һ�����ߣ����ӵķָ�����һ��
    // �������һ�����ߣ���"&"���ӣ����һ�����߽�tab�����磺����1&����2&����3\t
    int i(0), last(b._authors.size() - 1);
    for (auto const &s : b._authors)
    {
        i == last ? (out << s << L"\t") : (out << s << L"&");
        ++i;
    }
    
    // ���д������
    out << b._press;

    // ����wofstream����ʵ����ʽ���
    return out;
}