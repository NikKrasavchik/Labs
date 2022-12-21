#pragma once

#include <iostream>

class CPoint
{
private:
	int _x0;
	int _y0;
	int _v0;
	int _a;

public:
	CPoint();
	CPoint(int a_);
	CPoint(int v_, int a_);
	CPoint(int x_, int y_, int v_, int a_);

	void setX0(int x0_) { this->_x0 = x0_; }
	void setY0(int y0_) { this->_y0 = y0_; }
	
	int getV(int t_);
	int getS(int t_);
	int getXinT(int t_);
	int getYinT(int t_);
	
	void info();
};

