#ifndef SEARCH_H
#define SEARCH_H

#include "Station.h";
#include "Line.h";
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>

using namespace std;

struct path_of_information {
	int vertex;
	int shortest_distance;
	int previous_vertex;
	string line;
};
struct information {
	int time;
	string line;
};

class Search {
public:
	Search(const vector<Station*>& stations, const int& first_station_, const int& last_station_);
	
	int isVisited(int station);																				//Da li je stanica vec posecena
	void fillTheTableOfInformation(vector<Station*>& stations, vector<Line*>& lines);						//Popunjavanje tablice informacija 
	struct path_of_information findTheSortestUnvisited();													//Pronalazi neobidjeno polje sa najkracom distancom od prvog polja
	struct path_of_information findPathByVertex(int vertex);												//Pronalazi polje tablice informacija preko IDja stanice
	vector<Line*> stationLines(vector<Line*>& lines, int station);											//Vraca sve linije koje prolaze kroz stanicu
	set<int> lineStations(vector<Station*>& stations, vector<Line*> station_lines, int this_station);		//Vraca sve stanice kroz koje prolaze linije
	void setShortestDistance(int vertex, int distance, int prev_vertex);									//Promena vrednosti najkrace putanje kao i prethodnog cvora
	void printTableOfInformation();																			//Stampanje tabele informacija
	vector<int> theShortestPath();																			//Pronalazak najkrace putanje iz tablice informacija
	vector<int> theStationsConection(vector<Line*>& lines, int station1, int station2);						//Sve stanice izmedju dve zadate
	void minimalStopsExecute(vector<Station*>& stations, vector<Line*>& lines);								//Pozivanje gravne funkcije za racunanje putanje sa najmanje presedanja
	string theStationsLineConection(vector<Line*>& lines, int station1, int station2);


	vector<int> theStationsConectionTime(vector<Line*>& lines, int station1, int station2, string line);
	vector<struct information> theShortestPathTime();
	void setShortestDistanceTime(int vertex, int distance, int prev_vertex, string line);
	void fillTheTableOfInformationTime(vector<Station*>& stations, vector<Line*>& lines, int minutes);
	void minimalTimeExecute(vector<Station*>& stations, vector<Line*>& lines, int minutes);
	int distanceFromStations(vector<Line*>& lines, int station1, int station2, int minutes);
	struct information timeOfWaiting(vector<Line*>&  lines, int station1, int station2, int minutes);
	void allPaths(vector<Line*>& lines, vector<Station*>& stations, int minutes);

private:

	vector<int> visited_vertices;
	vector<int> unvisited_vertices;
	vector<struct path_of_information> table_of_information;
	int first_station;
	int last_station;

};

#endif