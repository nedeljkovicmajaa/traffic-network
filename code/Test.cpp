#include "Traffic.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main() {

	/*
	try {

		cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju:\n1. Ucitavanje podataka o mrezi gradskog prevoza\n0. Kraj rada\n";
		int option = 1;
		while (option != 0) {
			try{
				cin >> option;
				if (option != 1 && option != 0) {
					throw WrongOperation();
				}
				if (option == 0) {
					break;
				}
			
				string file_stations; string file_lines;
				cout << "\nMolimo Vas, unesite putanju fajla sa stanicama:\n";
				cin >> file_stations;
				cout << "\nMolimo Vas, unesite putanju fajla sa linijama:\n";
				cin >> file_lines;
				Traffic* traffic_example1 = new Traffic();
				Traffic* traffic_example(traffic_example1);

				traffic_example->loadingFiles(file_stations, file_lines);
				vector<Station*> stations = traffic_example->getStations();
				vector<Line*> lines = traffic_example->getLines();
				int option_show_informations = 1;
				cout << "\nMreza gradskog prevoza je uspesno ucitana.\n";
				while (option_show_informations != 0) {
					try {

						if (option_show_informations != 0) {
							cout << "\nMolimo Vas, odaberite opciju:\n1. Prikaz informacija o stajalistu\n2. Prikaz osnovnih informacija o liniji gradskog prevoza\n3. Prikaz statickih informacija o liniji gradskog prevoza\n4. Pronalazak putanje izmedju dva stajalista\n0. Kraj rada\n";
						}
		
						cin >> option_show_informations;
						if (option_show_informations != 0 && option_show_informations != 1 && option_show_informations != 2 && option_show_informations != 3 && option_show_informations != 4) {
							throw WrongOperation();
						}
						if (option_show_informations == 1) {
							cout << "\nUnesite ID stanice o kojoj zelite da dobijete informacije:\n";
							int id;
							cin >> id;
							if (!traffic_example->isInStations(stations, id)) {
								throw NoStation();
							}

							StationInformation* station_information = new StationInformation(id);
							station_information->execute(stations, lines);
							cout << "\nUspesno je generisan fajl: stajaliste_" << to_string(id) << ".txt, sa podacima o trazenoj stanici.\n";
							delete station_information;
						}
						else if (option_show_informations == 2) {
							cout << "\nUnesite naziv linije o kojoj zelite da dobijete informacije:\n";
							string line_mark;
							cin >> line_mark;
							if (!traffic_example->isInLines(lines, line_mark)) {
								throw NoLine();
							}

							LinesInformation* line_information = new LinesInformation(line_mark);
							line_information->execute(stations, lines);
							cout << "\nUspesno je generisan fajl: linija_" << line_mark << ".txt, sa podacima o trazenoj stanici.\n";
							delete line_information;
						}
						else if (option_show_informations == 3) {
							cout << "\nUnesite naziv linije da dobijete statisticke informacije:\n";
							string line_mark;
							cin >> line_mark;
							if (!traffic_example->isInLines(lines, line_mark)) {
								throw NoLine();
							}

							StaticInformation* static_information = new StaticInformation(line_mark);
							static_information->execute(stations, lines);
							cout << "\nUspesno je generisan fajl: statistika_" << line_mark << ".txt, sa podacima o trazenoj stanici.\n";
							delete static_information;
						}
						else if (option_show_informations == 4) {
							cout << "\nIzabrali ste opciju generisanja putanje izmedju dva stajalista. Izaberite novu opciju:\n1. Generisanje vremenski najkrace putanje\n2. Generisanje putanje sa najmanje presedanja\n";
							int path_option;
							cin >> path_option;
							if (path_option != 1 && path_option != 2) {
								throw WrongOperation();
							}
							if (path_option == 1) {
								cout << "\nUnesite ID polazne stanice:\n";
								int id_start; int id_end;
								cin >> id_start;
								cout << "\nUnesite ID krajnje stanice:\n";
								cin >> id_end;
								while (!(traffic_example->isInStations(stations, id_start) && traffic_example->isInStations(stations, id_start))) {
									cout << "\nNisu svi uneti podaci ispravni. Unesite ponovo:\n";
									cout << "\nUnesite ID polazne stanice:\n";
									cin >> id_start;
									cout << "\nUnesite ID krajnje stanice:\n";
									cin >> id_end;
								}
								cout << "\nUnesite sat dolaska na pocetnu stanicu:\n";
								int h; int min;
								cin >> h;
								cout << "\nUnesite minut dolaska na pocetnu stanicu:\n";
								cin >> min;
								Search* path_information = new Search(stations, id_start, id_end);
								int minutes = h * 60 + min;

								path_information->minimalTimeExecute(stations, lines, minutes);

								cout << "\nUspesno je generisan fajl: putanja_" << to_string(id_start) << "_" << to_string(id_end) << ".txt, koji sadrzi najbrzu putanju.\n";
								delete path_information;
							}
							else if (path_option == 2) {
								cout << "\nUnesite ID polazne stanice:\n";
								int id_start; int id_end;
								cin >> id_start;
								cout << "\nUnesite ID krajnje stanice:\n";
								cin >> id_end;
								while (!(traffic_example->isInStations(stations, id_start) && traffic_example->isInStations(stations, id_start))) {
									cout << "\nNisu svi uneti podaci ispravni. Unesite ponovo:\n";
									cout << "\nUnesite ID polazne stanice:\n";
									cin >> id_start;
									cout << "\nUnesite ID krajnje stanice:\n";
									cin >> id_end;
								}
								

								Search* path_information = new Search(stations, id_start, id_end);

								path_information->minimalStopsExecute(stations, lines);

								cout << "\nUspesno je generisan fajl: putanja_" << to_string(id_start) << "_" << to_string(id_end) << ".txt, koji sadrzi putanju sa najmanje presedanja.\n";
								delete path_information;
							}
						}
					}
					catch (WrongOperation& wo) {
						wo.getMessage();
					}
					catch (NoStation& ns) {
						ns.getMessage();
					}
					catch (NoLine& nl) {
						nl .getMessage();
					}
				}
				
				traffic_example->~Traffic();
				option = 0;

			}
			catch (WrongOperation& wo) {
				wo.getMessage();
			}
			
		}
		
	}
	catch (FileCouldNotBeOpened& fo) {
		fo.getMessage();
	}
	*/

string file_stations = "C:/Users/Zephyrus/Downloads/test/stajalista.txt"; string file_lines = "C:/Users/Zephyrus/Downloads/test/linije.txt";
Traffic* traffic_example1 = new Traffic();
Traffic* traffic_example(traffic_example1);

traffic_example->loadingFiles(file_stations, file_lines);
vector<Station*> stations = traffic_example->getStations();
vector<Line*> lines = traffic_example->getLines();
int h; int min;
cin >> h;
cout << "\nUnesite minut dolaska na pocetnu stanicu:\n";
cin >> min;
Search* path_information = new Search(stations, 1, 111);
int minutes = h * 60 + min;

path_information->allPaths(lines,stations, minutes);

	return 0;
}