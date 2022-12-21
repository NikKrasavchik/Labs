#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CAutomobile
{
private:
	string _number;
	string _colour;
	string _brand;
	string _typeOfDrive;
	int _mileage;
	int _costNew;
	int _costNow;
	pair<int, int> _GPS;

	int _maxSpeed;
	string _engineType;
	int _fuelConsumption;
	int _fuel;
	int _serviceInterval;

public:
	CAutomobile();
	CAutomobile(string number_, string colour_, string brand_, string typeOfDrive_, int mileage_, int costNew_, int costNow_, pair<int, int> GPS_, int maxSpeed_, string engineType_, int fuelConsumption_, int fuel_, int serviceInterval_);

	void setServiceInterval(int serviceInterval_) { this->_serviceInterval = serviceInterval_; }
	string getNumber() { return this->_number; }
	string getColour() { return this->_colour; }
	string getBrand() { return this->_brand; }
	string getTypeOfDrive() { return this->_typeOfDrive; }
	int getMileage() { return this->_mileage; }
	int getCostNew() { return this->_costNew; }
	int getCostNow() { return this->_costNow; }
	pair<int, int> getGPS() { return this->_GPS; }
	int getMaxSpeed() { return this->_maxSpeed; }
	string getEngineType() { return this->_engineType; }
	int getFuelConsumption() { return this->_fuelConsumption; }
	int getFuel() { return this->_fuel; }
	int getServiceInterval() { return this->_serviceInterval; }

	bool willThere(int distance_);
	int distanceGPS(pair<int, int> location_);
	int tripCost(pair<int, int> GPS_, int fuelCost_);
	int tripTime(pair<int, int> GPS_);
	int priceLoss();
};

