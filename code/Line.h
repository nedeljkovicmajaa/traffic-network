#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct time {			//Struktura vremena; sadrzi informacije o prvom i poslednjem polasku
	int first_hour;
	int first_minute;
	int last_hour;
	int last_minute;
};

class Line {
public:

	Line(const string& line_mark_, const struct time& work_time_, const int& next_time_, const vector<int>& train_stations_) : line_mark(line_mark_),
		work_time(work_time_), next_time(next_time_), train_stations(train_stations_) {}

	int isInLine(int station_id);								//Proverava da li linija prolazi kroz zadatu stanicu
	string getLineMark() { return line_mark; }
	struct time getTime() { return work_time; }
	int getNextTime() { return next_time; }
	vector<int> getTrainStations() { return train_stations; }


private:

	string line_mark;				// oznaka_linije
	struct time work_time;			//  prvi_i_poslednji_polazak
	int next_time;					//  razmak_između_polazaka
	vector<int> train_stations;		//  stajališta_redom
	
};

#endif