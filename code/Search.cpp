#include "Search.h"


Search::Search(const vector<Station*> &stations, const int& first_station_, const int& last_station_) : first_station(first_station_), last_station(last_station_)
{
	for (auto& station : stations) {
		unvisited_vertices.push_back(station->getStationId());
		struct path_of_information path;
		path.vertex = station->getStationId();
		path.previous_vertex = 0;
		path.line = "";
		if (station->getStationId() == first_station) {
			path.shortest_distance = 0;
		}
		else {
			path.shortest_distance = std::numeric_limits<int>::max();
		}
		table_of_information.push_back(path);
	}

}

int Search::isVisited(int station) {
	for (auto& visited : visited_vertices) {
		if (visited == station) {
			return 1;
		}
	}
	return 0;
}

struct path_of_information Search::findPathByVertex(int vertex_) {
	for (auto& node : table_of_information) {
		if (node.vertex == vertex_) {
			return node;
		}
	}
	return table_of_information[0];
}

struct path_of_information Search::findTheSortestUnvisited() {
	struct path_of_information first_station = findPathByVertex(unvisited_vertices[0]);
	for (auto& node : unvisited_vertices) {
		if (findPathByVertex(node).shortest_distance < first_station.shortest_distance) {
			first_station.vertex = findPathByVertex(node).vertex;
			first_station.previous_vertex = findPathByVertex(node).previous_vertex;
			first_station.shortest_distance = findPathByVertex(node).shortest_distance;
		}
	}
	return first_station;
}

vector<Line*> Search::stationLines(vector<Line*>& lines, int station)
{
	vector<Line*> station_lines;
	for (auto& line : lines) {
		if (line->isInLine(station)) {
			station_lines.push_back(line);
		}
	}
	return station_lines;
}

set<int> Search::lineStations(vector<Station*>& stations, vector<Line*> station_lines, int this_station)
{
	set<int> line_stations;
	for (auto& station : stations) {
		for (auto& line : station_lines) {
			if (line->isInLine(station->getStationId())) {
				if (station->getStationId() != this_station) {
					line_stations.insert(station->getStationId());
				}
			}
		}
	}

	return line_stations;
}

void Search::setShortestDistance(int vertex, int distance, int prev_vertex) {
	for (auto& information : table_of_information) {
		if (information.vertex == vertex) {
			information.shortest_distance = distance;
			information.previous_vertex = prev_vertex;
		}
	}
}

void Search::fillTheTableOfInformation(vector<Station*>& stations, vector<Line*>& lines) {
	struct path_of_information shortest_distance_unvisited = findTheSortestUnvisited();
	set<int> line_stations = lineStations(stations, stationLines(lines, shortest_distance_unvisited.vertex), shortest_distance_unvisited.vertex);
	for (auto& possible_station : line_stations) {
		int new_distance = shortest_distance_unvisited.shortest_distance + 1;
		if (findPathByVertex(possible_station).shortest_distance > new_distance) {
			setShortestDistance(possible_station, new_distance, shortest_distance_unvisited.vertex);
		}
	}
	visited_vertices.push_back(shortest_distance_unvisited.vertex);
	unvisited_vertices.erase(remove(unvisited_vertices.begin(), unvisited_vertices.end(), shortest_distance_unvisited.vertex), unvisited_vertices.end());
	
	if (!unvisited_vertices.empty()) {
		fillTheTableOfInformation(stations, lines);
	}
}

void Search::printTableOfInformation() {
	for (auto& path : table_of_information) {
		cout << path.vertex << " " << path.shortest_distance << " " << path.previous_vertex << " " << path.line << "\n";
	}
}

vector<int> Search::theShortestPath() {
	struct path_of_information the_shortest_distance = table_of_information[0];
	vector<int> the_shortest_path;
	for (auto& information : table_of_information) {
		if (information.vertex == last_station) {
			the_shortest_distance.shortest_distance = information.shortest_distance;
			the_shortest_distance.vertex = information.vertex;
			the_shortest_distance.previous_vertex = information.previous_vertex;

		}
	}
	the_shortest_path.push_back(the_shortest_distance.vertex);
	while (the_shortest_distance.previous_vertex != 0) {	
		for (auto& information : table_of_information) {
			if (information.vertex == the_shortest_distance.previous_vertex) {
				the_shortest_distance.shortest_distance = information.shortest_distance;
				the_shortest_distance.vertex = information.vertex;
				the_shortest_distance.previous_vertex = information.previous_vertex;
				the_shortest_path.push_back(the_shortest_distance.vertex);
			}
		}
	}

	reverse(the_shortest_path.begin(), the_shortest_path.end());

	return the_shortest_path;
}

vector<int> Search::theStationsConection(vector<Line*>& lines, int station1, int station2) {
	vector<int> middle_stations;
	int is_in_middle = -1;
	for (auto& line : lines) {
		if (line->isInLine(station1) && line->isInLine(station2)) {
			for (auto& station : line->getTrainStations()) {
				if (station == station1 || station == station2) {
					is_in_middle *= -1;
				}
				if (is_in_middle == 1) {
					middle_stations.push_back(station);
				}
			}
			break;
		}
	}
	if (middle_stations[0] == station1) {
		middle_stations.push_back(station2);
	}
	else {
		middle_stations.push_back(station1);
	}
	if (middle_stations[0] != station1) {
		reverse(middle_stations.begin(), middle_stations.end());
	}

	return middle_stations;
}

string Search::theStationsLineConection(vector<Line*>& lines, int station1, int station2) {
	string connection_line;
	for (auto& line : lines) {
		if (line->isInLine(station1) && line->isInLine(station2)) {
			connection_line = line->getLineMark();
		}
	}

	return connection_line;
}

void Search::minimalStopsExecute(vector<Station*>& stations, vector<Line*>& lines) {
	fillTheTableOfInformation(stations, lines);
	vector<int> stop_stations = theShortestPath();
	vector<vector<int>> stations_between_stations;
	vector<string> lines_between_stations;
	for (int i = 0; i < stop_stations.size()-1;i++) {
		stations_between_stations.push_back(theStationsConection(lines, stop_stations[i], stop_stations[i+1]));
		lines_between_stations.push_back(theStationsLineConection(lines, stop_stations[i], stop_stations[i + 1]));
	}

	ofstream MyFile("putanja_" + to_string(first_station) + '_' + to_string(last_station) + ".txt");

	MyFile << "->" << lines_between_stations[0] << "\n";
	for (int i = 1; i < lines_between_stations.size(); i++) {
		for (auto& station : stations_between_stations[i-1]) {
			MyFile << station << " ";
		}
		MyFile << "\n";
		MyFile <<lines_between_stations[i-1] << "->" << lines_between_stations[i]<<"\n";
	}
	for (auto& station : stations_between_stations[lines_between_stations.size() - 1]) {
		MyFile << station << " ";
	}

	MyFile.close();
}



vector<int> Search::theStationsConectionTime(vector<Line*>& lines, int station1, int station2, string this_line) {
	vector<int> middle_stations;
	int is_in_middle = -1;
	for (auto& line : lines) {
		if (line->getLineMark() == this_line) {
			for (auto& station : line->getTrainStations()) {
				if (station == station1 || station == station2) {
					is_in_middle *= -1;
				}
				if (is_in_middle == 1) {
					middle_stations.push_back(station);
				}
			}
			break;
		}
	}
	if (middle_stations[0] == station1) {
		middle_stations.push_back(station2);
	}
	else {
		middle_stations.push_back(station1);
	}
	if (middle_stations[0] != station1) {
		reverse(middle_stations.begin(), middle_stations.end());
	}

	return middle_stations;
}

vector<struct information> Search::theShortestPathTime() {
	struct path_of_information the_shortest_distance;
	vector<struct information> the_shortest_path;
	for (auto& information1 : table_of_information) {
		if (information1.vertex == last_station) {
			the_shortest_distance.shortest_distance = information1.shortest_distance;
			the_shortest_distance.vertex = information1.vertex;
			the_shortest_distance.previous_vertex = information1.previous_vertex;
			the_shortest_distance.line = information1.line;
		}
	}
	struct information element;
	element.time = the_shortest_distance.vertex;
	element.line = the_shortest_distance.line;
	the_shortest_path.push_back(element);
	while (the_shortest_distance.previous_vertex != 0) {
		for (auto& information : table_of_information) {
			if (information.vertex == the_shortest_distance.previous_vertex) {
				the_shortest_distance.shortest_distance = information.shortest_distance;
				the_shortest_distance.vertex = information.vertex;
				the_shortest_distance.previous_vertex = information.previous_vertex;
				the_shortest_distance.line = information.line;
				element.time = the_shortest_distance.vertex;
				element.line = the_shortest_distance.line;
				the_shortest_path.push_back(element);
			}
		}
	}

	reverse(the_shortest_path.begin(), the_shortest_path.end());

	return the_shortest_path;
}

void Search::setShortestDistanceTime(int vertex, int distance, int prev_vertex, string line) {
	for (auto& information : table_of_information) {
		if (information.vertex == vertex) {
			information.shortest_distance = distance;
			information.previous_vertex = prev_vertex;
			information.line = line;
		}
	}
}

int Search::distanceFromStations(vector<Line*>& lines, int station1, int station2, int minute) {
	int number_of_stations = 0; int time_of_waiting = 0; int min_time_of_waiting = 0; int station1_time = 0; int first_time = 0; string line_name = "";
	for (auto& line : lines) {
		if (line->isInLine(station1) && line->isInLine(station2)) {
			int direction = 0;
			for (auto& station : line->getTrainStations()) {
				if (station == station1) {
					direction = 1;
				}
				if (station == station2) {
					direction = 2;
				}
			}
			if (direction == 2) {
				for (auto& station : line->getTrainStations()) {
					if (station == station1) {
						direction = -1;
					}
					if (direction == 2) {
						number_of_stations += 1;
					}
				}
			}
			if (direction == 1) {
				for (auto& station : line->getTrainStations()) {
					if (direction == -1) {
						number_of_stations += 1;
					}
					if (station == station1) {
						direction = -1;
					}
				}
			}

			station1_time = line->getTime().first_hour * 60 + line->getTime().first_minute + 3 * number_of_stations;
			while (station1_time < minute) {
				station1_time += line->getNextTime();
			}
			time_of_waiting = station1_time - minute;

			if (first_time == 0) {
				min_time_of_waiting = time_of_waiting;
				line_name = line->getLineMark();
				first_time = 1;
			}
			else if (time_of_waiting < min_time_of_waiting) {
				min_time_of_waiting = time_of_waiting;
				line_name = line->getLineMark();
			}
		}
	}
	int distance = 0;
	int in_the_middle = -1;
	for (auto& line : lines) {
		if (line->getLineMark() == line_name) {
			for (auto& station : line->getTrainStations()) {
				if (station == station1 || station == station2) {
					in_the_middle *= -1;
				}
				if (in_the_middle == 1) {
					distance += 1;
				}
			}
		}
	}

	return distance;
}

struct information Search::timeOfWaiting(vector<Line*>& lines, int station1, int station2, int minute) {
	struct information result;
	int number_of_stations = 0; int time_of_waiting = 0; int min_time_of_waiting = 0; int station1_time = 0; int first_time = 0; string line_name = "";
	for (auto& line : lines) {
		if (line->isInLine(station1) && line->isInLine(station2)) {
			int direction = 0;
			for (auto& station : line->getTrainStations()) {
				if (station == station1) {
					direction = 1;
				}
				if (station == station2) {
					direction = 2;
				}
			}
			if (direction == 2) {
				for (auto& station : line->getTrainStations()) {
					if (station == station1) {
						direction = -1;
					}
					if (direction == 2) {
						number_of_stations += 1;
					}
				}
			}
			if (direction == 1) {
				for (auto& station : line->getTrainStations()) {
					if (direction == -1) {
						number_of_stations += 1;
					}
					if (station == station1) {
						direction = -1;
					}
				}
			}

			station1_time = line->getTime().first_hour * 60 + line->getTime().first_minute + 3 * number_of_stations;
			int station1_last_time = line->getTime().last_hour * 60 + line->getTime().last_minute + 3 * number_of_stations;
			while (station1_time < minute) {
				station1_time += line->getNextTime();
			}
			
			time_of_waiting = station1_time - minute;
			if (station1_time > station1_last_time) {
				time_of_waiting = line->getTime().first_hour * 60 + line->getTime().first_minute + 3 * number_of_stations - minute;
				while (time_of_waiting < 0) {
					time_of_waiting += 24*60;
				}
			}

			if (first_time == 0) {
				min_time_of_waiting = time_of_waiting;
				line_name = line->getLineMark();
				first_time = 1;
			}
			else if (time_of_waiting < min_time_of_waiting) {
				min_time_of_waiting = time_of_waiting;
				line_name = line->getLineMark();
			}
		}
	}
	result.line = line_name;
	result.time = min_time_of_waiting;
	return result;
}

void Search::fillTheTableOfInformationTime(vector<Station*>& stations, vector<Line*>& lines, int minutes) {
	struct path_of_information shortest_distance_unvisited = findTheSortestUnvisited();
	int new_minutes = minutes - shortest_distance_unvisited.shortest_distance;
	set<int> line_stations = lineStations(stations, stationLines(lines, shortest_distance_unvisited.vertex), shortest_distance_unvisited.vertex);
	for (auto& possible_station : line_stations) {
		int distance_from_stations = distanceFromStations(lines, shortest_distance_unvisited.vertex, possible_station, minutes);
		int time_of_waiting = timeOfWaiting(lines, shortest_distance_unvisited.vertex, possible_station, minutes).time;
		int new_distance = shortest_distance_unvisited.shortest_distance + 3* distance_from_stations + time_of_waiting;
		if (findPathByVertex(possible_station).shortest_distance > new_distance) {
			setShortestDistanceTime(possible_station, new_distance, shortest_distance_unvisited.vertex, timeOfWaiting(lines, shortest_distance_unvisited.vertex, possible_station, minutes).line);
		}
	}

	visited_vertices.push_back(shortest_distance_unvisited.vertex);
	unvisited_vertices.erase(remove(unvisited_vertices.begin(), unvisited_vertices.end(), shortest_distance_unvisited.vertex), unvisited_vertices.end());
	
	if (!unvisited_vertices.empty()) {
		shortest_distance_unvisited = findTheSortestUnvisited();
		fillTheTableOfInformationTime(stations, lines, new_minutes + shortest_distance_unvisited.shortest_distance);
	}
}

void Search::minimalTimeExecute(vector<Station*>& stations, vector<Line*>& lines, int minutes) {
	fillTheTableOfInformationTime(stations, lines, minutes);
	vector<struct information> stop_stations = theShortestPathTime();
	vector<vector<int>> stations_between_stations;
	vector<string> lines_between_stations;
	stations_between_stations.push_back(theStationsConectionTime(lines, stop_stations[0].time, stop_stations[1].time, stop_stations[1].line));
	for (int i = 1; i < stop_stations.size() - 1; i++) {
		stations_between_stations.push_back(theStationsConectionTime(lines, stop_stations[i].time, stop_stations[i + 1].time, stop_stations[i+1].line));
		lines_between_stations.push_back(stop_stations[i].line);
	}

	lines_between_stations.push_back(stop_stations[stop_stations.size() - 1].line);

	ofstream MyFile("putanja_" + to_string(first_station) + '_' + to_string(last_station) + ".txt");

	MyFile << "->" << lines_between_stations[0] << "\n";
	for (int i = 1; i < lines_between_stations.size(); i++) {
		for (auto& station : stations_between_stations[i - 1]) {
			MyFile << station << " ";
		}
		MyFile << "\n";
		MyFile << lines_between_stations[i - 1] << "->" << lines_between_stations[i] << "\n";
	}
	for (auto& station : stations_between_stations[lines_between_stations.size() - 1]) {
		MyFile << station << " ";
	}

	MyFile.close();
}

void Search::allPaths(vector<Line*>& lines, vector<Station*>& stations, int minutes) {
	for (int i = 0; i < stations.size(); i++) {
		for (int j = 0; j < stations.size(); j++) {
			if (i != j) {
				Search* a = new Search(stations, stations[i]->getStationId(), stations[j]->getStationId());
				a->minimalTimeExecute(stations, lines, minutes);
			}
			
		}	
	}
}