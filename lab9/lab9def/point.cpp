#include "point.h"

CPoint::CPoint()
{
    this->_x0 = 0;
    this->_y0 = 0;
    this->_v0 = 0;
    this->_a = 0;
}

CPoint::CPoint(int a_)
{
    this->_x0 = 0;
    this->_y0 = 0;
    this->_v0 = 0;
    this->_a = a_;
}

CPoint::CPoint(int v_, int a_)
{
    this->_x0 = 0;
    this->_y0 = 0;
    this->_v0 = v_;
    this->_a = a_;
}

CPoint::CPoint(int x_, int y_, int v_, int a_)
{
    this->_x0 = x_;
    this->_y0 = y_;
    this->_v0 = v_;
    this->_a = a_;
}

int CPoint::getV(int t_)
{
    return this->_v0 + this->_a * t_;
}

int CPoint::getS(int t_)
{
    return this->_v0 * t_ + (this->_a * t_ * t_) / 2;
}

int CPoint::getXinT(int t_)
{
    return this->_x0 + this->_v0 * t_ + (this->_a * t_ * t_) / 2;
}

int CPoint::getYinT(int t_)
{
    return this->_y0 + this->_v0 * t_ + (this->_a * t_ * t_) / 2;
}

void CPoint::info()
{
    std::cout << "x0 = " << this->_x0 << std::endl;
    std::cout << "y0 = " << this->_y0 << std::endl;
    std::cout << "v0 = " << this->_v0 << std::endl;
    std::cout << "a = " << this->_a << std::endl << std::endl;
}
