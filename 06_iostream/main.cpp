#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

int main(void)
{
    int i = 143;
    std::cout << i << std::endl;
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << i << std::endl;
    std::cout.unsetf(std::ios::hex);

    std::ifstream in;
    in.open("iostream_text.txt");

    if (!in.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return 0;
    }

    std::cout.setf(std::ios::fixed | std::ios::right);
    std::cout << std::setprecision(3);// << std::setfill('*');

    char array[16] = { '0' };
    double x = 0.0;
    std::stringstream ss;

    while (!in.eof())
    {
        in.getline(array, 16);
        ss << array;
        ss >> x;
        std::cout << std::setw(10) << x;
        ss.clear();
    }
    std::cout << std::endl;

    return 0;
}