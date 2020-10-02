#pragma once
#include"txt_helper.h"
class math_helper
{
public:
	static void OriA(point&, point&);//初始方位角
	static void ComputB(point&);//转角    默认位左角
	static void ComputeA(point&,point&);//目标方位角
	// static void AddV(point&, double); 直接写进去
	static void ComputeXY(point&, point&);
	static void ComputeXY(point&, point&, double[3]);
	static void ReXY(point&, point&, double[2]);
};

