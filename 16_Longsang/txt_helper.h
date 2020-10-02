#pragma once
#include<fstream>
#include<map>
#include<string>

using namespace std;

struct point
{
	string name;
	string last;
	string next;
	double X;
	double Y;
	double L1;
	double L2;
	double S;
	double A;
};

class txt_helper
{public:
	txt_helper(ifstream&);
	string first, end;
	map<string, point> table;
	double para[3];
	string blank = "None";
public:
	void out();
	string sort();
	void Show();

private:
	
};

