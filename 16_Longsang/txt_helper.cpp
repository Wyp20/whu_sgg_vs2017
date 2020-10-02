#include "txt_helper.h"
#include<fstream>
#include<map>
#include<sstream>
#include<string>
#include<iostream>
using namespace std;

void _replace(string& ori) {
	for (size_t i = 0; i < ori.length(); i++)
	{
		ori[i] = ori[i] == ',' ? ' ' : ori[i];
	}
}

double Trans(double ori) {
	double d, m, s;
	d = int(ori);
	m = int((ori - d) * 100);
	s = ((ori - d) * 100 - m) * 100;
	return d + m / 60 + s / 3600;
}

ostream& operator<<(ostream& out, point P) {
	out << P.name << " " << P.last << " " << P.next << " " << P.X << " " << P.Y << " " << P.L1 << " " << P.L2 << " " << P.S << " " << P.A;
	return out;
}

txt_helper::txt_helper(ifstream& in)
{
	string line;
	stringstream ss;
	string name,last,next;
	double X, Y, L, S;
	// para
	getline(in, line);_replace(line);
	ss << line; 
	ss >> para[0] >>para[1]>> para[2];
	ss.str(""); ss.clear();

	while (!in.eof())
	{
		getline(in, line); _replace(line);
		if (line.length() > 1) {
			if (isalpha(line[0])) {

				if (line.length() == 3) {
					ss << line;
					ss >> name;
					ss.str(""); ss.clear();

					getline(in, line); _replace(line);
					if (line[4] == 'L') {
						ss << line;
						ss >> last >> next >> L;

						
						table[name].last = last;
						table[name].L1 = Trans(L);
						if (table[last].next == blank)table[last].next = name;
						ss.str(""); ss.clear();
						//
						getline(in, line); _replace(line);
						ss << line;
						ss >> next >> last >> L;

						if (table.find(next) == table.end()) table[next] = point{ next, blank, blank, 0., 0., 0., 0. ,0. ,0. };
						
						table[name].L2 = Trans(L);
						table[name].next = next;
						if (table[next].last == blank)table[next].last = name;
						ss.str(""); ss.clear();
					}
					else
					{
						ss << line;
						ss >> next >> last >> S;
						table[name].S = S;
						ss.str(""); ss.clear();
					}
				}
				else
				{
					ss << line;
					ss >> name >> X >> Y;
					table[name] = point{ name, blank, blank, X, Y, 0., 0. ,0.,0. };
					ss.str(""); ss.clear();
				}

			}
		}
		else {
			continue;
		}
	}
	sort();
}

void txt_helper::out()
{
	for (map<string, point>::iterator it = table.begin(); it  != table.end(); it++)
	{
		cout << it->second << endl;
	}
	cout << para[0] << " " << para[1] << " " << para[2] << endl;
}

string txt_helper::sort()
{

	for (map<string,point>::iterator it = table.begin(); it != table.end(); it++)
	{
		if (it->second.last == blank) {
			end = first = it->first;
			
			while (table[end].next != blank)
			{
				end = table[end].next;
			}
			return it->first;

		}
			
	}
	return "None";
}

void txt_helper::Show()
{

}
