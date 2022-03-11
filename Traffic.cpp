#include "Traffic.h"

Traffic::~Traffic() {
	for (auto& station : stations) {
		delete station;
	}
	for (auto& line : lines) {
		delete line;
	}
}

void Traffic::loadingFiles(string name_of_file1, string name_of_file2)
{	
	
	string text;

	fstream inputFile1(name_of_file1, ios::in);
	if (!inputFile1) {
		throw FileCouldNotBeOpened(name_of_file1);
	}

	while (getline(inputFile1, text)) {
		int position_of_space = text.find(' ');
		stations.push_back(new Station(stoi(text.substr(0, position_of_space)), text.substr(position_of_space + 1)));
	}
	inputFile1.close();

	fstream inputFile2(name_of_file2, ios::in);
	if (!inputFile2) {
		throw FileCouldNotBeOpened(name_of_file2);
	}

	while (getline(inputFile2, text)) {
		string line_mark = text.substr(0, text.find(' '));
		text.erase(0, text.find(' ') + 2);
		struct time work_time;
		work_time.first_hour = stoi(text.substr(0, text.find(':')));
		text.erase(0, text.find(':') + 1);
		work_time.first_minute = stoi(text.substr(0, text.find('-')));
		text.erase(0, text.find('-') + 1);
		work_time.last_hour = stoi(text.substr(0, text.find(':')));
		text.erase(0, text.find(':') + 1);
		work_time.last_minute = stoi(text.substr(0, text.find('#')));
		text.erase(0, text.find('#') + 1);
		int next_time = stoi(text.substr(0, text.find(']')));
		text.erase(0, text.find(']') + 2);
		vector<int> stations_of_line;
		while (text.find(' ')!= string::npos) {
			stations_of_line.push_back(stoi(text.substr(0, text.find(' '))));
			text.erase(0, text.find(' ') + 1);
		}
		stations_of_line.push_back(stoi(text.substr(0, text.find(' '))));
		lines.push_back(new Line(line_mark, work_time, next_time, stations_of_line));

	}
	inputFile2.close();
	
}

void Traffic::printStations()
{
	for (auto& station : stations) {
		cout << "\t" << station->getStationId() << "\t" << station->getStationName() << "\n";
	}
}

void Traffic::printLines()
{
	for (auto& station : lines) {
		cout << "\t" << station->getLineMark() << "\t" <<"[" << station->getTime().first_hour <<":" << station->getTime().first_minute <<"-" << station->getTime().last_hour<<":" << station->getTime().last_minute<< "] "<< station->getNextTime()<< "\n";
		for (auto& item : station->getTrainStations()) {
			cout << item << " ";
		}
		cout<< "\n";
	}
}

int Traffic::isInLines(vector<Line*>& lines, string line) {
	for (auto& line_ : lines) {
		if (line_->getLineMark() == line) {
			return 1;
		}
	}
	return 0;
}
int Traffic::isInStations(vector<Station*>& stations, int station) {
	for (auto& station_ : stations) {
		if (station_->getStationId() == station) {
			return 1;
		}
	}
	return 0;
}