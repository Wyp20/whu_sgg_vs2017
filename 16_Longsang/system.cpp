#include "system.h"
#include"math_helper.h"
#include"txt_helper.h"
#include<fstream>
#include<iomanip>
#define PI 3.14159265358979
using namespace std;


System::System(txt_helper& txt)
{
	ofstream out("out.txt");
	out.setf(ios::fixed);
	int n = txt.table.size() - 2;
	char d = '*', m = '\'', s = '\"';
	double dms[3], Acd;
	string save, temp;
	//��ȡ�۲����ݵ������
	{
		txt.Show();
	}
	//������ʼ��λ�Ǻͽ�����λ��
	{
		out << "��ʼ��λ�Ǻͽ�����λ��======\n";
		save = txt.table[txt.first].next;
		math_helper::OriA(txt.table[txt.first], txt.table[save]);
		save = txt.table[txt.end].last;
		math_helper::OriA(txt.table[save], txt.table[txt.end]);
		trans(txt.table[txt.first].A, dms);
		out << "��ʼ��λ�ǣ�" << setprecision(0) << dms[0] << d << setprecision(0) << dms[1] << m << setprecision(4) << dms[2] << s << endl;
		trans(txt.table[save].A, dms);
		Acd = txt.table[save].A;
		out << "������λ�ǣ�" << setprecision(0) << dms[0] << d << setprecision(0) << dms[1] << m << setprecision(4) << dms[2] << s << endl;
	}
	//ת�Ǽ���
	{
		out << "ת�Ǽ�����==========	====\n";
		save = txt.first;
		while (txt.table[save].next != txt.blank)
		{
			if (txt.table[save].last != txt.blank) {
				math_helper::ComputB(txt.table[save]);
				trans(txt.table[save].L2, dms);
				out << save << '\t' << setprecision(0) << dms[0] << d << setprecision(0) << dms[1] << m << setprecision(4) << dms[2] << s << endl;
			}
			save = txt.table[save].next;
		}
	}
	//Ŀ�귽λ�Ǽ���
	{
		out << "Ŀ�귽λ�Ǽ�����=========\n";
		save = txt.first;
		while (txt.table[save].next != txt.blank)
		{
			temp = txt.table[save].next;
			if (txt.table[temp].next != txt.blank) {
				math_helper::ComputeA(txt.table[save], txt.table[temp]);
				trans(txt.table[temp].A, dms);
				out << temp << '\t' << setprecision(0) << dms[0] << d << setprecision(0) << dms[1] << m << setprecision(4) << dms[2] << s << endl;
			}
			save = txt.table[save].next;
		}
	}
	//���㷽λ�Ǳպϲ�
	{
		out << "��λ�Ǳպϲ������========\n";

		save = txt.table[txt.end].last;
		double fb = txt.table[save].A - Acd;
		trans(fb, dms);
		out << "fb��\t" << setprecision(0) << dms[0] << d << setprecision(0) << dms[1] << m << setprecision(4) << dms[2] << s << endl;
		out << "��λ�Ǳպϲ��޲���========\n";
		if (abs(fb) <= 24. / 3600 * sqrt(n)) {
			out << "���޲���\n";
		}
		else {
			out << "���޲���\n";
		}

		//���������ĸ�ת�۽�

		out << "������ĸ�ת�۽�===========\n";
		double vb = -fb / n;
		save = txt.first;
		while (txt.table[save].next != txt.blank)
		{
			if (txt.table[save].last != txt.blank) {
				txt.table[save].L2 += vb;
				trans(txt.table[save].L2, dms);
				out << save << '\t' << setprecision(0) << dms[0] << d << setprecision(0) << dms[1] << m << setprecision(4) << dms[2] << s << endl;
			}
			save = txt.table[save].next;
		}
	}
	//�������귽λ��
	{
		out << "���º�����귽λ��=========\n";
		save = txt.first;
		while (txt.table[save].next != txt.blank)
		{
			temp = txt.table[save].next;
			if (txt.table[temp].next != txt.blank) {
				math_helper::ComputeA(txt.table[save], txt.table[temp]);
				trans(txt.table[temp].A, dms);
				out << temp << '\t' << setprecision(0) << dms[0] << d << setprecision(0) << dms[1] << m << setprecision(4) << dms[2] << s << endl;
			}
			save = txt.table[save].next;
		}
	}
	//�����ݺ���������
	{
		out << "��� �ݺ���������==========\n";
		save = txt.first;
		while (txt.table[save].next != txt.blank)
		{
			temp = txt.table[save].next;
			if (txt.table[save].last != txt.blank && txt.table[temp].next != txt.blank && txt.table[txt.table[temp].next].next != txt.blank) {
				math_helper::ComputeXY(txt.table[save], txt.table[temp]);
				out << temp
					<< "\tx:" << setprecision(3) << txt.table[temp].X - txt.table[save].X
					<< "\ty:" << setprecision(3) << txt.table[temp].Y - txt.table[save].Y
					<< endl;
			}
			save = temp;
		}
	}
	//�ݺ�����պϲ� ����ȫ���պϲ�
	{
		out << "�ݺ����ꡢ����ȫ���պϲ�====\n";
		double f[3];
		save = txt.table[txt.end].last;
		temp = txt.table[save].last;
		math_helper::ComputeXY(txt.table[temp], txt.table[save], f);
		out << "fx��" << setprecision(3) << f[0] << endl;
		out << "fy��" << setprecision(3) << f[1] << endl;
		out << "fs��" << setprecision(3) << f[2] << endl;

		double SUM = 0;
		save = txt.first;
		while (txt.table[save].next != txt.blank)
		{
			temp = txt.table[save].next;
			if (txt.table[save].last != txt.blank) {
				SUM += txt.table[save].S;
			}
			save = temp;
		}

		out << "�����������������������==\n";
		double v[2];
		save = txt.first;
		while (txt.table[save].next != txt.blank)
		{
			temp = txt.table[save].next;
			if (txt.table[save].last != txt.blank && txt.table[txt.table[temp].next].next != txt.blank) {
				v[0] = -f[0] / SUM * txt.table[save].S;
				v[1] = -f[1] / SUM * txt.table[save].S;

				math_helper::ReXY(txt.table[save], txt.table[temp], v);

				out << temp
					<< "\tVx��\t" << setprecision(3) << v[0]
					<< "\tVy��\t" << setprecision(3) << v[1]
					<< "\tX��\t" << setprecision(3) << txt.table[temp].X
					<< "\tY��\t" << setprecision(3) << txt.table[temp].Y
					<< endl;
			}
			save = temp;
		}

	}
	printf("Happy ending");
}

void System::trans(double A, double dms[3])
{
	dms[0] = int(A);
	dms[1] = int((A - dms[0]) * 60);
	dms[2] = (((A - dms[0]) * 60) - dms[1]) * 60;
}
