#include"txt_helper.h"
#include"system.h"
#include<iostream>
#include<fstream>
using namespace std;

int main() {
	ifstream in("test.txt");
	if (in) {
		txt_helper txt(in);
		txt.out();
		System text(txt);
	}
	return 0;
}