#include<iostream>
using namespace std;

void main1() {
	double a = 1;
	cout << atan2(a, a) << endl;
	cout << atan2(-a, a) << endl;
	cout << atan2(-a, -a) << endl;
	cout << atan2(a, -a) << endl;
	

}

void main2(double f[]) {
	f[0] = 10;
	f[1] = 100;
}

void main() {
	double f[2] = { 1,10 };
	cout << f[0] << "|" << f[1] << endl;
	main2(f);
	cout << f[0] << "|" << f[1] << endl;

}