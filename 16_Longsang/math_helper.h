#pragma once
#include"txt_helper.h"
class math_helper
{
public:
	static void OriA(point&, point&);//��ʼ��λ��
	static void ComputB(point&);//ת��    Ĭ��λ���
	static void ComputeA(point&,point&);//Ŀ�귽λ��
	// static void AddV(point&, double); ֱ��д��ȥ
	static void ComputeXY(point&, point&);
	static void ComputeXY(point&, point&, double[3]);
	static void ReXY(point&, point&, double[2]);
};

