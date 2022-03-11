#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Station {
public:

	Station(const int &station_id_, const string &station_name_) : station_id(station_id_), station_name(station_name_) {};
	int getStationId() { return station_id; }
	string getStationName() { return station_name; }

private:

	int station_id;					// šifra_stajališta
	string station_name;			// naziv_stajališta

};

#endif