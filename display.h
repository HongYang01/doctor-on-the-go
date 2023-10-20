/*
	Implemedted by: Everyone
*/


#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <numeric>
using namespace std;

int display_welcome();

//Role in system
string display_role(int);

//Gender
string display_gender(int);

//City
string display_city(int);

//Race
string display_race(int);

//Month
string display_month(int);

//Time
string display_hour(int);

//Method
string display_appointment_method(int);

//Status
string display_appointment_status(int);

//Priority
string display_priority_type(int);

//Symptom
string display_symptom(int);

//Transportation
string display_trans(int);

//Visitation type
string display_visitation_type(int);

//Type of health condition
string display_hc_type(int);

//Others
bool file_is_empty(std::ifstream& checkFile);
string join(vector<string>vec,string delim);
vector<string> separate(string str, string delim);
bool date_is_valid(int,int,int);
bool date_smaller_than_today(int,int,int);

#endif
