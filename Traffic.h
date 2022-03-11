#ifndef TRAFFIC_H
#define TRAFFIC_H

#include "Exceptions.h" 
#include "Line.h" 
#include "Station.h" 
#include "Information.h" 
#include "Search.h" 

#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <vector>

using namespace std;


class Traffic {

public:
	Traffic() {};
	Traffic(const vector <Station*>& stations_, const vector<Line*>& lines_) : stations(stations_), lines(lines_) {};
	~Traffic();

	void loadingFiles(string name_of_file1, string name_of_file2);		//Ucitavanje fajlova u vektore stanica i linija
	void printStations();												
	void printLines();
	vector<Station*> getStations() { return stations; }
	vector<Line*> getLines() { return lines; }
	int isInLines(vector<Line*> &lines, string line);
	int isInStations(vector<Station*> &stations, int station);

private:

	vector<Station*> stations; 
	vector<Line*> lines;

};

#endif