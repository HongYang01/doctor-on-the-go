#include <iostream>
#include <Windows.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
//#include <conio.h>
//#include <cstdlib>

using namespace std;

#include "display.h"

int display_welcome(){
	
	int nav;
	system("CLS");
	cout << "------------------------------------" << endl;
	cout << "Welcome to [DOCTOR ON THE GO] system" << endl;
	cout << "------------------------------------" << endl;
	cout << "[1] Login\n";
	cout << "[2] Signup\n";
	cout << "\nChoose [0]Exit : ";
	cin >> nav;
	
	if(nav==0){
		system("CLS"); cout << "Thank you"; exit(0);
	}
	
return nav;
}

string display_role(int num){ //-1:Display All Role, except ADMIN
	
	string role[]={"ADMIN", "PATIENT", "DOCTOR", "NURSE", "MEDICAL ASSISTANT", "SPECIALIST"};
	
	if(num==0){
		for(int d=0; d<sizeof(role)/sizeof(string); d++)
			cout << "[" << d+1 << "] " << role[d] << endl;
	}
	else if(num==-1){
		for(int d=1; d<sizeof(role)/sizeof(string); d++)
			cout << "[" << d << "] " << role[d] << endl;
	}
	else{
		return role[num-1];
	}

return "";
}

string display_gender(int num){ //0:Display All Gender
	
	string gender[]={"MALE","FEMALE"};
	
	if(num==0){
		for(int d=0; d<sizeof(gender)/sizeof(string); d++)
			cout << "[" << d+1 << "] " << gender[d] << endl;
		cout << endl;
	}
	else if(num<=sizeof(gender)/sizeof(string)){
		return gender[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_city(int num){ //0:Display All City
	
	string city[]={"KUCHING","SAMARAHAN","SRI AMAN","KAPIT","BINTULU","MIRI"};
	
	if(num==0){
		for(int d=0; d<sizeof(city)/sizeof(string); d++)
			cout << "[" << d+1 << "] " << city[d] << endl;
	}
	else if(num<=sizeof(city)/sizeof(string)){
		return city[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_race(int num){ //0:Display All Race
	
	string race[]={"CHINESE","MELAYU","IBAN","BIDAYUH","MELANAU","OTHERS"};
	
	if(num==0){
		for(int d=0; d<sizeof(race)/sizeof(string); d++)
			cout << "[" << d+1 << "] " << race[d] << endl;
	}
	else if(num>0 && num<=sizeof(race)/sizeof(string)){
		return race[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_month(int num){
	
	string month_list[]={"JAN","FEB","MAC","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
	
	if(num==0){
		for(int i=0; i<sizeof(month_list)/sizeof(string); i++)
			cout << left << "["
				 << setw(2) << i+1 << "] " << month_list[i] << endl;
	}
	else if(num>0 && num<=sizeof(month_list)/sizeof(string)){
		return month_list[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__ << "\r"; sleep(2);
	}
return "";
}

string display_hour(int num){
	
	const string hour_list[]={"08:00","09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00","17:00","18:00"};
	
	if(num==0){
		for(int i=0; i<sizeof(hour_list)/sizeof(string); i++)
			cout << left << "[" 
				 << setw(2) << i+1 << "] " << hour_list[i] << endl;
	}
	else if(num>0 && num<=sizeof(hour_list)/sizeof(string)){
		return hour_list[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_appointment_method(int num){
	
	const string method[]={"ONLINE CONSULTATION","HEALTH SCREENING"};
	
	if(num==0){
		for(int i=0; i<sizeof(method)/sizeof(string); i++)
			cout << "[" << i+1 << "] " << method[i] << endl;
	}
	else if(num>0 && num<=sizeof(method)/sizeof(string)){
		return method[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}

return "";
}

string display_appointment_status(int num){
	
	const string status[]={"PENDING", "APPROVED", "REJECTED"};
	
	if(num==0){
		for(int i=0; i<sizeof(status)/sizeof(string); i++)
			cout << "[" << i+1 << "] " << status[i] << endl;
	}
	else if(num>0 && num<=sizeof(status)/sizeof(string)){
		return status[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_priority_type(int num){
	
	string priority_type[]={"UNRATED","LOW","MODERATE","EMERGENCY"};
	
	if(num==0){
		for(int i=0; i<sizeof(priority_type)/sizeof(string); i++)
			cout << "[" << i+1 << "] " << priority_type[i] << endl;
	}
	else if(num>0 && num<=sizeof(priority_type)/sizeof(string)){
		return priority_type[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_health_condition(int num){
	
	const string condition_type[]={"Arthritis","Alzheimer's disease","Diabetes","Heart Disease","High Blood Pressure","Kidney Disease"};
	
	if(num==0){
		for(int i=0; i<sizeof(condition_type)/sizeof(string); i++)
			cout << "[" << i+1 << "] " << condition_type[i] << endl;
	}
	else if(num>0 && num<=sizeof(condition_type)/sizeof(string)){
		return condition_type[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_symptom(int num){
	
	string symptom_type[]={"Fever","Cough","Fatigue","Body Ache","Headache","Chest Pain","Breathing Diffuculty","Chills","Stomachache","Dizziness","Tasteless","Nausea","Stress"};
	
	if(num==0){
		for(int i=0; i<sizeof(symptom_type)/sizeof(string); i++)
			cout << left << "["
				 << setw(2) << i+1 << "] " << symptom_type[i] << endl;
	}
	else if(num>0 && num<=sizeof(symptom_type)/sizeof(string)){
		return symptom_type[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";	
}

string display_trans(int num){
	
	//bus & boat = mobile clinic
	
	const string trans_type[]={"BUS","BOAT","AIRCRAFT"};
	
	if(num==0){
		for(int i=0; i<sizeof(trans_type)/sizeof(string); i++)
			cout << "[" << i+1 << "] " << trans_type[i] << endl;
	}
	else if(num>0 && num<=sizeof(trans_type)/sizeof(string)){
		return trans_type[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_visitation_type(int num){
	
	const string v_type[]={"ONE-TIME","ROUTINE"};
	
	if(num==0){
		for(int i=0; i<sizeof(v_type)/sizeof(string); i++)
			cout << "[" << i+1 << "] " << v_type[i] << endl;
	}
	else if(num>0 && num<=sizeof(v_type)/sizeof(string)){
		return v_type[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}

string display_hc_type(int num){
	
	const string hc_type[]={"ASTHMA", "HEART DISEASE", "STROKE", "DIABETES", "ARTHRITIS"};
	
	if(num==0){
		for(int i=0; i<sizeof(hc_type)/sizeof(string); i++)
			cout << "[" << i+1 << "] " << hc_type[i] << endl;
	}
	else if(num>0 && num<=sizeof(hc_type)/sizeof(string)){
		return hc_type[num-1];
	}
	else{
		cout << ">>> Error: display.cpp/line-" << __LINE__; sleep(2);
	}
return "";
}


//Other
bool file_is_empty(ifstream& checkFile){
	return checkFile.peek() == std::ifstream::traits_type::eof();
}

string join(vector<string>vec,string delim){
	
    if (vec.empty()) {
        return "";
    }
 	else{
 		string str="";
 		for(int i=0; i<vec.size(); i++){
 			str.append(vec.at(i));
 			if(i<vec.size()-1) str.append(delim);
		}
		return str;
	}
}

vector<string> separate(string str, string delim){
	
	vector<string> vec;
	size_t pos=0;
	
	while((pos = str.find(delim)) != string::npos){ //put data into vector using delimeter
		
		vec.push_back(str.substr(0, pos));
		str.erase(0, pos + delim.length());
		
    }
	vec.push_back(str.substr(0, pos)); //the last data from the line
	
	
	return vec;
}

bool date_is_valid(int day, int month, int year){
	
	//dates started in 1582 (gregorian)
  if (!(1582<= year))
     return false;
  if (!(1<= month && month<=12))
     return false;
  if (!(1<= day && day<=31))
     return false;
  if ((day==31) && (month==2 || month==4 || month==6 || month==9 || month==11))
     return false;
  if ((day==30) && (month==2))
     return false;
  if ((month==2) && (day==29) && (year%4!=0))
     return false;
  if ((month==2) && (day==29) && (year%400==0))
     return true;
  if ((month==2) && (day==29) && (year%100==0))
     return false;
  if ((month==2) && (day==29) && (year%4==0))
     return true;
 
  return true;
	
}

bool date_smaller_than_today(int day, int month, int year){
	
	time_t now = time(0);
	tm *get = localtime(&now);
	
	if(get->tm_year+1900>year){ //year
		return true;
	}
	else if(get->tm_year+1900==year && get->tm_mon+1>month){ //year month
		return true;
	}
	else if(get->tm_year+1900==year && get->tm_mon+1==month && get->tm_mday>day){ //year month day
		return true;
	}

return false;
}

