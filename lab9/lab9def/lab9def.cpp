#include "point.h"
#include <iostream>
#include <iomanip>
#include <locale>

double distance(CPoint first, CPoint second, int t)
{
    return sqrt(pow((second.getXinT(t) - first.getXinT(t)), 2) + pow((second.getYinT(t) - first.getYinT(t)), 2));
}

int main()
{
    setlocale(LC_ALL, "RU");
    CPoint p1(rand() % 10);
    CPoint p2(rand() % 10, rand() % 10);
    CPoint p3(rand() % 10, rand() % 10, rand() % 10, rand() % 10);

    std::cout << "P1 info:" << std::endl;
    p1.info();
    std::cout << "P2 info:" << std::endl;
    p2.info(); 
    std::cout << "P3 info:" << std::endl;
    p3.info();

    int t;
    std::cout << "Введите t: ";
    std::cin >> t;
    std::cout << std::endl; 
    
    std::cout << std::setw(5) << "t |" << std::setw(12) << "P1-P2 |" << std::setw(12) << "P1-P3 |" << std::setw(10) << "P3-P3" << std::endl;
    std::cout << "_______________________________________" << std::endl;
    for (int i = 0; i < t+1; i++)
    {
        std::cout << std::setw(3) << i << " |";
        std::cout << std::setw(10) << distance(p1, p2, i) << " |";
        std::cout << std::setw(10) << distance(p1, p3, i) << " |";
        std::cout << std::setw(10) << distance(p2, p3, i);
        std::cout << std::endl;
    }
}
