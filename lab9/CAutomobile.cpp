#include "CAutomobile.h"

CAutomobile::CAutomobile()
{
	this->_number = "";
	this->_colour = "";
	this->_brand = "";
	this->_typeOfDrive = "";
	this->_mileage = 0;
	this->_costNew = 0;
	this->_costNow = 0;
	pair<int, int> GPS = { 0, 0 };
	this->_GPS = GPS;
	this->_maxSpeed = 0;
	this->_engineType = "";
	this->_fuelConsumption = 0;
	this->_fuel = 0;
	this->_serviceInterval = 0;
}

CAutomobile::CAutomobile(string number_, string colour_, string brand_, string typeOfDrive_, int mileage_, int costNew_, int costNow_, pair<int, int> GPS_, int maxSpeed_, string engineType_, int fuelConsumption_, int fuel_, int serviceInterval_)
{
	this->_number = number_;
	this->_colour = colour_;
	this->_brand = brand_;
	this->_typeOfDrive = typeOfDrive_;
	this->_mileage = mileage_;
	this->_costNew = costNew_;
	this->_costNow = costNow_;
	this->_GPS = GPS_;
	this->_maxSpeed = maxSpeed_;
	this->_engineType = engineType_;
	this->_fuelConsumption = fuelConsumption_;
	this->_fuel = fuel_;
	this->_serviceInterval = serviceInterval_;
}


bool CAutomobile::willThere(int distance_)
{
	if (this->_fuel / (double)this->_fuelConsumption * 100 > distance_)
		return true;
	return false;
}

int CAutomobile::distanceGPS(pair<int, int> location_)
{
	return (int)sqrt(pow((location_.first - this->_GPS.first), 2) + pow((location_.second - this->_GPS.second), 2));
}


int CAutomobile::tripCost(pair<int, int> GPS_, int fuelCost_)
{
	return (int)this->distanceGPS(GPS_) / 100.0 * this->_fuelConsumption * fuelCost_;
}

int CAutomobile::tripTime(pair<int, int> GPS_)
{
	return this->distanceGPS(GPS_) / this->_maxSpeed;
}

int CAutomobile::priceLoss()
{
	return this->_costNew - this->_costNow;
}


