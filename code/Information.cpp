#include "Information.h"

Station* Information::findStationById(vector<Station*>& stations, int station_id)
{
	try {
		for (int i = 0; i < stations.size(); i++) {
			if (stations[i]->getStationId() == station_id) {
				return stations[i];
			}
		}
		throw NoStation();
	}catch (NoStation& e) {
		e.getMessage();
	}
	return stations[0];
}

Line* Information::findLineByMark(vector<Line*>& lines, string line_mark)
{
	try{
		for (int i = 0; i < lines.size(); i++) {
			if (lines[i]->getLineMark() == line_mark) {
				return lines[i];
			}
		}
		throw NoLine();
	}
	catch (NoLine& e) {
		e.getMessage();
	}
	return lines[0];
}

void StationInformation::execute(vector<Station*> &stations, vector<Line*> &lines)
{
	ofstream MyFile("stajaliste_" + to_string(station_id) + ".txt");

	auto old_pos = 0;
	MyFile << to_string(station_id) << ' ' << findStationById(stations, station_id)->getStationName() << " [";
	vector<string> marks_of_lines;
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i]->isInLine(station_id)) {
			marks_of_lines.push_back(lines[i]->getLineMark());
		}
	}

	sort(marks_of_lines.begin(), marks_of_lines.end());

	for (auto& mark : marks_of_lines) {
		MyFile << mark << ' ';
		old_pos = MyFile.tellp();
	}
	
	MyFile.seekp(old_pos-1);
	MyFile << ']';
	MyFile.close();
}

void LinesInformation::execute(vector<Station*> &stations, vector<Line*> &lines)
{
	ofstream MyFile("linija_" + line_mark + ".txt");

	MyFile << line_mark << ' ' << findStationById(stations, (findLineByMark(lines, line_mark)->getTrainStations()[0]))->getStationName() << "->" << findStationById(stations, (findLineByMark(lines, line_mark)->getTrainStations()[findLineByMark(lines, line_mark)->getTrainStations().size()-1]))->getStationName() << "\n";
	for (auto& station : findLineByMark(lines, line_mark)->getTrainStations()) {
		MyFile << findStationById(stations, station)->getStationId() << ' ' << findStationById(stations, station)->getStationName() << "\n";
	}
	MyFile.close();
}

void StaticInformation::execute(vector<Station*> &stations, vector<Line*> &lines)
{
	ofstream MyFile("statistika_" + line_mark + ".txt");
	set<string> crossed_lines;
	
	MyFile << line_mark << "\n";

	auto old_pos = 0;
	for (auto& station : findLineByMark(lines, line_mark)->getTrainStations()){
		for (auto& line : lines) {
			if (line->isInLine(station)) {
				crossed_lines.insert(line->getLineMark());
			}
		}
	}
	for (auto& s : crossed_lines) {
		if (s != line_mark) {
			MyFile << s << " ";
			old_pos = MyFile.tellp();
		}
	}
	MyFile.seekp(old_pos - 1);
	MyFile << "\n";
	double number_of_starts = (findLineByMark(lines, line_mark)->getTime().last_hour*60 + findLineByMark(lines, line_mark)->getTime().last_minute - findLineByMark(lines, line_mark)->getTime().first_hour*60 - findLineByMark(lines, line_mark)->getTime().first_minute) / (findLineByMark(lines, line_mark)->getNextTime()) + 1;
	MyFile << round(number_of_starts);

	MyFile.close();
}