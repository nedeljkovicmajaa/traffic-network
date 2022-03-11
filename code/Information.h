#ifndef INFORMATION_H
#define INFORMATION_H

#include "Exceptions.h"
#include "Line.h"
#include "Station.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Information {

public:
	
	Station* findStationById(vector<Station*> &stations, int station_id);			//Pronalazi sve informacije o stanici pomocu njenog ID
	Line* findLineByMark(vector<Line*>& lines, string line_mark);					//Pronalazi sve informacije o liniji pomocu njene oznake
	virtual string getName(Information* &t) { return t->information_name; }
	virtual void execute(vector<Station*> &stations, vector<Line*> &lines) = 0;		//funkcija koja predstavlja prikaz podataka u zavisnosti od klase u kojoj se nalazi

private:
	string information_name = "";
};

class StationInformation : public Information {
public:

	StationInformation(int station_id_) : station_id(station_id_) {}
	void execute(vector<Station*> &stations, vector<Line*> &lines) override;
	
private:
	string information_name = "StationInformation";
	int station_id;
};

class LinesInformation : public Information {
public:

	LinesInformation(string line_mark_) : line_mark(line_mark_) {}
	void execute(vector<Station*> &stations, vector<Line*> &lines) override;

private:
	string information_name = "LinesInformation";
	string line_mark;
};

class StaticInformation : public Information {
public:

	StaticInformation(string line_mark_) : line_mark(line_mark_) {}
	void execute(vector<Station*> &stations, vector<Line*> &lines) override;

private:
	string information_name = "StaticInformation";
	string line_mark;
};



#endif