#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
using namespace std;

class FileCouldNotBeOpened : public exception {
public:
	FileCouldNotBeOpened(string name_of_file) { msg_ = "\nFajl " + name_of_file + " nije mogao da se otvori.\n"; }
	void getMessage() { cout << msg_; }
private:
	string msg_;
};

class NoStation : public exception {
public:
	NoStation() { msg_ = "\nStanica koju ste uneli je nepostojeca.\n"; }
	void getMessage() { cout << msg_; }
private:
	string msg_;
};

class NoLine : public exception {
public:
	NoLine() { msg_ = "\nLinija koju ste uneli je nepostojeca.\n"; }
	void getMessage() { cout << msg_; }
private:
	string msg_;
};

class WrongOperation : public exception {
public:
	WrongOperation() { msg_ = "\nOdaberite ispravnu opciju. Uneli ste nepostojecu.\n"; }
	void getMessage() { cout << msg_; }
private:
	string msg_;
};

