#include "math_helper.h"
#define PI 3.14159265358979

double trans(double A) {
	A = A / PI * 180;
	A = A < 0 ? A + 360 : A;
	return A;
}

void math_helper::OriA(point& A, point& B)
{
	A.A = trans(atan2(B.Y - A.Y, B.X - A.X));
	A.S = (B.Y - A.Y) / sin(A.A / 180 * PI);
}

void math_helper::ComputB(point& A)
{

	if ( fabs(A.L1) > 1e-6) {
		double L1 = A.L1, L2 = A.L2;
		A.L1 = 0;
		A.L2 = L2 - L1;
		A.L2 = A.L2 >= 360 ? A.L2 - 360 : A.L2;
		A.L2 = A.L2 < 0 ? A.L2 + 360 : A.L2;
	}
}

void math_helper::ComputeA(point& A,point& B)
{
	B.A = A.A + B.L2 - 180;
	B.A = B.A >= 360 ? B.A - 360 : B.A;
	B.A = B.A < 0 ? B.A + 360 : B.A;
}

void math_helper::ComputeXY(point& A, point& B)
{

	B.X = A.X + A.S * cos(A.A / 180 * PI);
	B.Y = A.Y + A.S * sin(A.A / 180 * PI);
}

void math_helper::ComputeXY(point& A, point& B, double f[3])
{
	f[0] = A.X + A.S * cos(A.A / 180 * PI) - B.X;
	f[1] = A.Y + A.S * sin(A.A / 180 * PI) - B.Y;
	f[2] = sqrt(pow(f[0], 2) + pow(f[1], 2));
}

void math_helper::ReXY(point& A, point& B, double v[2])
{

	B.X = A.X + A.S * cos(A.A / 180 * PI) + v[0];
	B.Y = A.Y + A.S * sin(A.A / 180 * PI) + v[1];

}



