#include <iostream>
#include <vector>
#include <locale>
#include <ctime>
#include "CAutomobile.h"

string genNumber()
{
	string number;
	vector<char> letters = { 'A', 'B', 'C', 'E', 'H', 'K', 'M', 'O', 'P', 'T', 'X', 'Y' };
	number += letters[rand() % letters.size()];
	string n;
	do {
		n = to_string(rand() % 1000);
	} while (n == "000");
	number += n;
	number += letters[rand() % letters.size()];
	number += letters[rand() % letters.size()];
	return number;
}

string genColour()
{
	string number = "#";
	for (int i = 0; i < 6; i++)
		number += ((rand() % 2) ? char(rand() % 10 + 48) : char(rand() % 6 + 65));
	return number;
}

string genBrand()
{
	vector<string> brands = { "Audi", "BMW", "Mercedes", "Opel", "Porsche", "Volkswagen", "ГАЗ", "Lada", "УАЗ", "ЗиЛ", "Cadilla", "Ford", "Jeep", "Tesla" };
	return brands[rand() % brands.size()];
}

string genTypeOfDrive()
{
	return (rand() % 2 ? "petrol" : "diesel");
}

int genMileage()
{
	return rand() % 100000;
}

int genCostNew()
{
	int costNew;
	do {
		costNew = rand() % 100 * 100000 * (rand() % 2 ? 1 : 10);
	} while (costNew == 0);
	return costNew;
}

int genCostNow(int costNew)
{
	int costNow;
	do {
		costNow = rand() % 100 * 100000 * (rand() % 2 ? 1 : 10);
	} while (costNow > costNew);
	return costNow;
}

pair<int, int> genGPS()
{
	int x = rand() % 1000;
	int y = rand() % 1000;
	pair<int, int> GPS = { x, y };
	return GPS;
}

int genMaxSpeed()
{
	return ((rand() % 20) + 10) * 10;
}

string genEngineType()
{
	vector<string> engine = { "Поршневые Двигатели Внутреннего сгорания", "Роторные Двигатели Внутреннего сгорания", "Газотурбинные Двигатели", "Двигатели Внешнего сгорания", "Электрические Двигатели", "Криогенные Двигатели", "Инерционные Двигатели" };
	return engine[rand() % engine.size()];
}

int genFuelConsumption()
{
	return rand() % 10 + 10;
}

int genFuel()
{
	return rand() % 100;
}

int genServiceInterval()
{
	return rand() % 55 + 6;
}


int main()
{
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	string number = genNumber();
	string colour = genColour();
	string brand = genBrand();
	string typeOfDrive = genTypeOfDrive();
	int mileage = genMileage();
	int costNew = genCostNew();
	int costNow = genCostNow(costNew);
	pair<int, int> GPS = genGPS();
	int maxSpeed = genMaxSpeed();
	string engineType = genEngineType();
	int fuelConsumption = genFuelConsumption();
	int fuel = genFuel();
	int serviceInterval = genServiceInterval();
	CAutomobile a(number, colour, brand, typeOfDrive, mileage, costNew, costNow, GPS, maxSpeed, engineType, fuelConsumption, fuel, serviceInterval);

	cout << "Number: " << a.getNumber() << endl;
	cout << "Colour: " << a.getColour() << endl;
	cout << "Brand: " << a.getBrand() << endl;
	cout << "Type of Drive: " << a.getTypeOfDrive() << endl;
	cout << "Mileage: " << a.getMileage() << endl;
	cout << "Cost new: " << a.getCostNew() << endl;
	cout << "Cost now: " << a.getCostNow() << endl;
	cout << "GPS: " << a.getGPS().first << ":" << a.getGPS().second << endl;
	cout << "Max speed: " << a.getMaxSpeed() << endl;
	cout << "Engine type: " << a.getEngineType() << endl;
	cout << "Fuel consumption: " << a.getFuelConsumption() << endl;
	cout << "Fuel:" << a.getFuel() << endl;
	cout << "Service interval: " << a.getServiceInterval() << endl;
	cout << endl;
	int distance = rand() % 1000;
	cout << "Distance: " << distance << endl;
	cout << "Will there: " << ( a.willThere(distance) ? "Yes" : "No") << endl << endl;
	pair<int, int> location = { rand() % 1000, rand() % 1000 };
	cout << "Location: " << location.first << ":" << location.second << endl;
	cout << "Distance GPS: " << a.distanceGPS(location) << endl << endl;
	cout << "Location: " << location.first << ":" << location.second << endl;
	int fuelCost = rand() % 30 + 35;
	cout << "Fuel cost: " << fuelCost << endl;
	cout << "Trip cost: " << a.tripCost(location, fuelCost) << endl << endl;
	cout << "Location: " << location.first << ":" << location.second << endl;
	cout << "Trip time: " << a.tripTime(location) << endl << endl;
	cout << "Price lost: " << a.priceLoss() << endl;
}