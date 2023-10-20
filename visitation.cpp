#include <iostream>
#include <Windows.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
//#include <conio.h>
//#include <cstdlib>

#include "display.h"
#include "visitation.h"

using namespace std;

visitation::visitation(){
}

visitation::~visitation(){
}

bool visitation::add_visitation(string visitID, string docID, int type){
	
	//v_id can be unique or same with app_id
	//(1=ONE-TIME) app_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	//(2=ROUTINE) v_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	
	int nav;
	vector<string> tempV;
	vector<string> appDetail;
	
	//get appointment detail based on app_id
	//app_ID,patient_IC,app_method,day,month,year,time,priority,app_status,ms_ID
	if(type==1){ //ONE-TIME VISITATION
		appDetail = app4.search_appointment(visitID);
		//get user detail based on userID
		//verification,role,IC,name,age,gender,race,street,city,phone,email,password
		if(u3.search_user(appDetail.at(1))==false){ //fail to get patient data
			system("CLS"); cout << "Fail to get patient data"; sleep(2); return false;
		}
	}
	
	if(hos5.get_medical_staff_hos(docID)==false){
		system("CLS"); cout << "Fail to get doctor data"; sleep(2); return false;	
	}

	tempV.push_back(visitID);
	tempV.push_back(to_string(type));


start_add_visitation2:
	
	char ch;
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "             Add Visitation Schedule             " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ID       : " << tempV.at(0) << endl;
	cout << "Type     : " << display_visitation_type(stoi(tempV.at(1))) << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Date [dd/mm/yyyy] : "; cin >> this->v_day >> ch >> this->v_month >> ch >> this->v_year;
	cin.clear(); cin.ignore(INT_MAX,'\n');
	
	if(	date_is_valid(this->v_day,this->v_month,this->v_year)==false ||
		date_smaller_than_today(this->v_day,this->v_month,this->v_year)==true){
		system("CLS");
		cout << "Your date might be: \n";
		cout << ">>> invalid\n>>> smaller than today\n\n";
		system("PAUSE");
		goto start_add_visitation2;
	}
		
	if(visitation_clash(docID,stoi(tempV.at(1)),this->v_day,this->v_month,this->v_year)==true){
		system("CLS");
		cout << ">>> Date : " << this->v_day << "-" << display_month(this->v_month) << "-" << this->v_year << endl;
		cout << ">>> Please change the date. It clashed with another schedule\n\n";
		system("PAUSE");
		goto start_add_visitation2;
	}
		
		tempV.push_back(to_string(this->v_day));
		tempV.push_back(to_string(this->v_month));
		tempV.push_back(to_string(this->v_year));
	
	
	do{
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "             Add Visitation Schedule             " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "ID       : " << tempV.at(0) << endl;
		cout << "Type     : " << display_visitation_type(stoi(tempV.at(1))) << endl;
		cout << "Date     : " << tempV.at(2) << "-" << display_month(stoi(tempV.at(3))) << "-" << tempV.at(4) << endl;
		cout << "-------------------------------------------------" << endl;
		display_hour(0);
		cout << "Time     : "; cin >> this->v_time;
		cin.clear(); cin.ignore(INT_MAX,'\n');
	}while(this->v_time<1 || this->v_time>11);
	
	tempV.push_back(to_string(this->v_time));
	
	
	
	if(type==1){ //ONE-TIME VISITATION
		
		tempV.push_back(u3.get_userStreet()); //patient street
		tempV.push_back(to_string(u3.get_userCity())); //patient city
		
	}
	else if(type==2){ //ROUTINE VISITATION
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "             Add Visitation Schedule             " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "ID       : " << tempV.at(0) << endl;
		cout << "Type     : " << display_visitation_type(stoi(tempV.at(1))) << endl;
		cout << "Date     : " << tempV.at(2) << "-" << display_month(stoi(tempV.at(3))) << "-" << tempV.at(4) << endl;
		cout << "Time     : " << display_hour(stoi(tempV.at(5))) << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Street   : "; getline(cin >> ws, this->v_street);
		
		tempV.push_back(this->v_street);
		
		do{
			system("CLS");
			cout << "-------------------------------------------------" << endl;
			cout << "             Add Visitation Schedule             " << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "ID       : " << tempV.at(0) << endl;
			cout << "Type     : " << display_visitation_type(stoi(tempV.at(1))) << endl;
			cout << "Date     : " << tempV.at(2) << "-" << display_month(stoi(tempV.at(3))) << "-" << tempV.at(4) << endl;
			cout << "Time     : " << display_hour(stoi(tempV.at(5))) << endl;
			cout << "Street   : " << tempV.at(6) << endl;
			cout << "-------------------------------------------------" << endl;
			display_city(0);
			cout << "City     : "; cin >> this->v_city;
			cin.clear(); cin.ignore(INT_MAX,'\n');
			
		}while(this->v_city<1 || this->v_city>6);
		
		tempV.push_back(to_string(this->v_city));
		
	}
	
	
	vector<vector<string>> trans2D;
	
	if(type==1){ //ONE-TIME VISIT
		
		//if doctor hospital city not match then cannot
		
		//choose transport based on 
		//choose only bus(1) or boat(2)
		//preview
		
		//id,docid,type
		
		do{
			system("CLS");
			cout << "-------------------------------------------------" << endl;
			cout << "             Add Visitation Schedule             " << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "ID       : " << tempV.at(0) << endl;
			cout << "Type     : " << display_visitation_type(stoi(tempV.at(1))) << endl;
			cout << "Date     : " << tempV.at(2) << "-" << display_month(stoi(tempV.at(3))) << "-" << tempV.at(4) << endl;
			cout << "Time     : " << display_hour(stoi(tempV.at(5))) << endl;
			cout << "Street   : " << tempV.at(6) << endl;
			cout << "City     : " << display_city(stoi(tempV.at(7))) << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "              Assign Transportation              " << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "[1] Bus" << endl;
			cout << "[2] Boat" << endl;
			cout << "\nChoose : "; cin >> nav;
			cin.clear(); cin.ignore(INT_MAX,'\n');
			
			trans2D = trans3.search_transportation(hos5.get_hosID(),nav);
			
			if(nav>0 && nav<=2){ //check trans availability
				
				for(int j=0; j<trans2D.size(); j++){
					
					if(trans3.trans_schedule_clash(trans2D[j][0],stoi(tempV.at(2)),stoi(tempV.at(3)),stoi(tempV.at(4)))==true){ //check if clashS
						
						trans2D.erase(trans2D.begin() + j);
						j=0;
					}
					
				}
			}
			
		}while(nav<1 || nav>2);
		
	}
	else if(type==2){ //ROUTINE VISIT
		
		do{
			system("CLS");
			cout << "-------------------------------------------------" << endl;
			cout << "             Add Visitation Schedule             " << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "ID       : " << tempV.at(0) << endl;
			cout << "Type     : " << display_visitation_type(stoi(tempV.at(1))) << endl;
			cout << "Date     : " << tempV.at(2) << "-" << display_month(stoi(tempV.at(3))) << "-" << tempV.at(4) << endl;
			cout << "Time     : " << display_hour(stoi(tempV.at(5))) << endl;
			cout << "Street   : " << tempV.at(6) << endl;
			cout << "City     : " << display_city(stoi(tempV.at(7))) << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "              Assign Transportation              " << endl;
			cout << "-------------------------------------------------" << endl;
			
			display_trans(0);
			cout << "\nChoose : "; cin >> nav;
			cin.clear(); cin.ignore(INT_MAX,'\n');
			
			trans2D = trans3.search_transportation(hos5.get_hosID(),nav);
			
			if(nav>0 && nav<=3){ //check trans availability
				
				for(int j=0; j<trans2D.size(); j++){
					
					if(trans3.trans_schedule_clash(trans2D[j][0],stoi(tempV.at(2)),stoi(tempV.at(3)),stoi(tempV.at(4)))==true){ //check if clashS
						
						trans2D.erase(trans2D.begin() + j);
						j=0;
					}
					
				}
			}
			
		}while(nav<=0 || nav>3);
		
	}
	
	if(trans2D.size()==0){
		system("CLS"); 
		cout << ">>> Date     : " << tempV.at(2) << "-" << display_month(stoi(tempV.at(3))) << "-" << tempV.at(4) << endl;
		cout << ">>> No transportation are available, please choose another date.\n\n";
		system("PAUSE");
		return false;
		
	}
	
	//choose transportation (same hospital as doctor)
	//trans_id,hos_ID,trans_type
	int i, transType=nav ,chooseTrans;
	do{
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "             Add Visitation Schedule             " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "ID       : " << tempV.at(0) << endl;
		cout << "Type     : " << display_visitation_type(stoi(tempV.at(1))) << endl;
		cout << "Date     : " << tempV.at(2) << "-" << display_month(stoi(tempV.at(3))) << "-" << tempV.at(4) << endl;
		cout << "Time     : " << display_hour(stoi(tempV.at(5))) << endl;
		cout << "Street   : " << tempV.at(6) << endl;
		cout << "City     : " << display_city(stoi(tempV.at(7))) << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "              Assign Transportation              " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Type     : " << display_trans(transType) << endl;
		cout << "-------------------------------------------------" << endl;
		
		i=1;
		for(vector<string> temp : trans2D){
			
			cout << left << "[" 
				 << setw(2) << i++ << "] "
				 << temp.at(0) << endl;
			
		}
		
		cout << "\nChoose a " << display_trans(transType) << " : "; cin >> chooseTrans;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
	}while(chooseTrans<1 || chooseTrans>trans2D.size());
	
	tempV.push_back(trans2D[chooseTrans-1][0]); //assign trans_id
	
	//Assigning other MS
	//MS must have same hos_id as doctor (same hospital)
	vector<string> assignMS;
	assignMS = add_ms_to_visitation(docID,stoi(tempV.at(7)),stoi(tempV.at(2)),stoi(tempV.at(3)),stoi(tempV.at(4)));
	
	if(assignMS.size()==0){
		system("CLS"); return false;
	}
	
	bool flag;
	do{
		flag=false;
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "             Add Visitation Schedule             " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "ID       : " << tempV.at(0) << endl;
		cout << "Type     : " << display_visitation_type(stoi(tempV.at(1))) << endl;
		cout << "Date     : " << tempV.at(2) << "-" << display_month(stoi(tempV.at(3))) << "-" << tempV.at(4) << endl;
		cout << "Time     : " << display_hour(stoi(tempV.at(5))) << endl;
		cout << "Street   : " << tempV.at(6) << endl;
		cout << "City     : " << display_city(stoi(tempV.at(7))) << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "              Assign Transportation              " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Type     : " << display_trans(transType) << endl;
		cout << "ID       : " << tempV.at(8) << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "              Assign Medical Staff               " << endl;
		cout << "-------------------------------------------------" << endl;
		
		int count=1;
		string data,delimiter=",", filename="../data/userData.txt";
		ifstream readFile;
		readFile.open(filename);
		while(getline(readFile,data)){
			
			for(int i=0; i<assignMS.size(); i++){
				
				if(separate(data,delimiter).at(2)==assignMS.at(i)){
					
					cout << left << "[" 
						 << setw(2) << count++ << "] " 
						 << setw(20) << separate(data,delimiter).at(2)
						 << separate(data,delimiter).at(3) << endl;
				}
				
			}
			
		}
		readFile.close();
		
		cout << "-------------------------------------------------" << endl;
		cout << "\nSave Visitation Schedule? [1]Yes [0]No : "; cin >> nav;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
		
		if(nav==1){ //save
			cout << "Confirm? [1]Yes [0]No : "; cin >> nav;
			cin.clear(); cin.ignore(INT_MAX,'\n');
			
			if(nav==0){
				flag=false;
			}
			else if(nav==1){
				flag=true;
			}
			else{
				flag=false;
			}
			
		}
		else if(nav==0){ //cancel
			cout << "Cancel Visitation? [1]Yes [0]No : "; cin >> nav;
			cin.clear(); cin.ignore(INT_MAX,'\n');
			
			if(nav==0){
				flag=false;
			}
			else if(nav==1){ //canvel visitation
				return false;
			}
			else{
				flag=false;
			}
			
		}
		else{
			flag=false;
		}
			
	}while(flag==false);
	
	//save visitation detail & assigned MS
	save_visitation("../data/visitation.txt",tempV);
	
	//v_id,docID,msID_1,msID_2,msID_3,...,n
	assignMS.insert(assignMS.begin(),tempV.at(0)); //
	assignMS.insert(assignMS.begin()+1,docID);
	save_visitation("../data/visitation_medical_staff.txt",assignMS);
	
	tempV.clear();
	assignMS.clear();
	
	return true;
}

vector<string> visitation::add_ms_to_visitation(string docID, int city, int day, int month, int year){
	
	//get visitation city
	//get docID to eliminate 
	//get date to check clashes
	
	string data, delimiter=",", filename;
	ifstream readFile;

	
	hos6.get_medical_staff_hos(docID); //get doctor hospital detail
	
	
	filename="../data/medical_staff_hospital.txt";
	readFile.open(filename);
	
	//ms_id,ms_type,hos_id
	vector<string> matchMS;
	while(getline(readFile,data)){
		
		if(separate(data,delimiter).at(2)==hos6.get_hosID() && separate(data,delimiter).at(0)!=docID){ //same hospital (excluding himself)
			
			matchMS.push_back(separate(data,delimiter).at(0));
			
		}
		
	}
	readFile.close();
	
	
	filename="../data/visitation.txt";
	readFile.open(filename);
	
	//v_id,v_type,v_day,v_month,v_year,v_street,v_city,v_trans_id	
	
	vector<string> matchV;
	while(getline(readFile,data)){
		
		if(	stoi(separate(data,delimiter).at(2)) == day &&
			stoi(separate(data,delimiter).at(3)) == month &&
			stoi(separate(data,delimiter).at(4)) == year)
		{
			matchV.push_back(separate(data,delimiter).at(0)); //get v_id
		}
	}
	readFile.close();
	
	
	loop:
		
	filename="../data/visitation_medical_staff.txt";
	readFile.open(filename);
	
	vector<string> tempMS;
	
	while(getline(readFile,data)){
		
		tempMS = separate(data,delimiter);
		
		for(int i=0; i<matchV.size(); i++){ //v_id
			
			for(int j=0; j<matchMS.size(); j++){ //ms_id
				
				for(int k=1; k<tempMS.size(); k++){ //1=v_id(skip this) 
					
					//match v_id & match MSid
					if(tempMS.at(0)==matchV.at(i) && tempMS.at(k)==matchMS.at(j)){
						
						matchMS.erase(matchMS.begin()+j); //reemove those that clashes
						goto loop;
					}
					
				}
				
			}
			
		}
		
	}
	readFile.close();
	
	
	if(matchMS.size()==0){ //no available medical staff
		system("CLS");
		cout << ">>> No medical staff available on this date: " << day << "-" << display_month(month) << "-" << year << endl;
		cout << ">>> Please reschedule\n\n";
		system("PAUSE");
		return matchMS;
	}
	
	
	vector<string> returnLine;
	filename="../data/userData.txt";
	int count;
	bool done,dup;
	
	do{
		done=dup=false;
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "              Assign Medical Staff               " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << left << "No.  " << setw(20) << "IC" << "Name" << endl;
		
		count=1;
		if(returnLine.size()>0){ //chosen MS
			
			cout << "-------------------------------------------------" << endl;
			
			readFile.open(filename);
			while(getline(readFile,data)){
				
				for(int i=0; i<returnLine.size(); i++){
					
					if(separate(data,delimiter).at(2)==returnLine.at(i)){
						
						cout << left << "[" 
							 << setw(2) << count++ << "] " 
							 << setw(20) << separate(data,delimiter).at(2)
							 << separate(data,delimiter).at(3) << endl;
					}
					
				}
				
			}
			readFile.close();
			
		}
		
		cout << "-------------------------------------------------" << endl;
		cout << "              Select Medical Staff               " << endl;
		cout << "-------------------------------------------------" << endl;
		
		count=1;
		readFile.open(filename);
		while(getline(readFile,data)){
			
			for(int i=0; i<matchMS.size() ;i++){
				
				//verification,role,IC,name,age,gender,race,street,city,phone,email,password
				if(separate(data,delimiter).at(2)==matchMS.at(i)){
					
					cout << left << "[" 
						 << setw(2) << count++ << "] " 
						 << setw(20) << separate(data,delimiter).at(2)
						 << separate(data,delimiter).at(3) << endl;
				}
				
			}
			
		}
		readFile.close();
		
		int nav;
		cout << "-------------------------------------------------" << endl;
		if(returnLine.size()>0) cout << "\nTo remove any medical staff use negative value [-n]remove";
		
		cout << "\nChoose [0]Done : "; cin >> nav;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
		done=false;
		
		if(nav==0 && returnLine.size()>0){
			done=true;
		}
		else if(nav>0 && nav<=matchMS.size()){ //good attempt
			
			for(int i=0; i<returnLine.size(); i++){
				if(matchMS.at(nav-1)==returnLine.at(i)){ //check duplication
					dup=true; break;
				}
			}
				
			if(dup==false) returnLine.push_back(matchMS.at(nav-1));
			
		}
		else if(nav<0 && (abs(nav)-1)<=returnLine.size() && returnLine.size()>0){ //removing MS
			
			returnLine.erase(returnLine.begin() + abs(nav)-1 ); //using negative value to remove medical staff
						
		}
		else if(nav==0 && returnLine.size()==0){ //not yet select any symptom
			system("CLS"); cout << ">>> No medical staff selected yet"; sleep(2); done=false;
		}
		else if(nav<0 && abs(nav)>returnLine.size()){ //removing symptom that is not in the list
			system("CLS"); cout << ">>> Nothing to remove at " << nav; sleep(2); done=false;
		}
		else{
			system("CLS"); cout << ">>> Nothing found : " << nav; sleep(2); done=false;
		}
		
	}while(done==false);
	
	return returnLine;

}

void visitation::save_visitation(string filename, vector<string> tempLine){
	
	ifstream readFile;
	readFile.open(filename);
	string delimiter = ",";
	string data;
	
	vector<vector<string>> line2D;
	while(getline(readFile,data)){
		
		line2D.push_back(separate(data,delimiter));
		
	}
	readFile.close();
	
	int i;
	bool flag=false;
	
	for(i=0; i<line2D.size(); i++){
		
		if(line2D[i][0]==tempLine.at(0)){ //same v_id
			
			line2D[i] = tempLine; //replace the line
			flag=true;
			break;
		}
	}
	
	if(flag==false) line2D.push_back(tempLine); //if data is unique
	
	ofstream writeFile;
	writeFile.open(filename);
	
	i=0;
	for(vector<string> temp1D : line2D){
		
		writeFile << join(temp1D,delimiter) << (i<line2D.size()-1 ? "\n" : "");
		i++;
		
	}
	
	tempLine.clear();
	line2D.clear();
	writeFile.close();
	
	system("CLS"); cout << ">>> Changes are updated successfully"; sleep(2);
	
}

bool visitation::search_visitation(string ID){
	
	//get v_id
	
	string data,delimiter=",", filename="../data/visitation.txt";
	
	ifstream readFile;
	readFile.open(filename);
	
	
	//(ONE-TIME) app_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	//(ROUTINE) v_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	while(getline(readFile,data)){
		
		if(separate(data,delimiter).at(0) == ID){
			
			this->v_id = separate(data,delimiter).at(0);
			this->v_type = stoi(separate(data,delimiter).at(1));
			this->v_day = stoi(separate(data,delimiter).at(2));
			this->v_month = stoi(separate(data,delimiter).at(3));
			this->v_year = stoi(separate(data,delimiter).at(4));
			this->v_time = stoi(separate(data,delimiter).at(5));
			this->v_street = separate(data,delimiter).at(6);
			this->v_city = stoi(separate(data,delimiter).at(7));
			this->v_trans_id = separate(data,delimiter).at(8);
			readFile.close();
			return true;
		}
		
	}
	readFile.close();
	
//	sytem("CLS"); cout << ">>> Visitation: "<< ID << ", details not found"; sleep(3); 
	return false;
	
}

void visitation::preview_visitation(vector<string> temp){
	
	//(ONE-TIME) app_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	//(ROUTINE) v_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	
	//type,date,city,trans_id
	
	//cout << left << "No.  " << "Type" << setw(15) << "Date" << setw(15) << "City" << "Transport ID";
	
	cout << left
		 << setw(10) << display_visitation_type(stoi(temp.at(1)))
		 << temp.at(2) << "-" << display_month(stoi(temp.at(3))) << "-" << temp.at(4) << "\t";
	
	cout << left
		 << setw(15) << display_city(stoi(temp.at(7)))
		 << temp.at(8) << endl;
	
	
}

void visitation::fullview_visitation(vector<string> temp){
	
	//(ONE-TIME) app_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	//(ROUTINE) v_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	cout << "-------------------------------------------------" << endl;
	cout << "                Visitation Detail                " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ID      : " << temp.at(0) << endl;
	cout << "Type    : " << display_visitation_type(stoi(temp.at(1))) << endl;
	cout << "Date    : " << temp.at(2) << "-" << display_month(stoi(temp.at(3))) << "-" << temp.at(4) << endl;
	cout << "Time    : " << display_hour(stoi(temp.at(5))) << endl;
	cout << "Address : " << temp.at(6) << ", " << display_city(stoi(temp.at(7))) << endl;
	
	ifstream readFile;
	readFile.open("../data/transportation.txt");
	
	string data,delimiter=",";
	
	//trans_id,hos_ID,trans_type
	while(getline(readFile,data)){
		
		if(separate(data,delimiter).at(0) == temp.at(8)){
			trans3.fullview_trans_detail(separate(data,delimiter));
			break;
		}
		
	}
	readFile.close();
	return;
}

bool visitation::visitation_clash(string docID, int type,int day,int month,int year){
	
	string data, delimiter="," , filename;
	ifstream readFile;

	vector<string> temp;
	vector<string> tempV;
	
	filename="../data/visitation_medical_staff.txt";
	readFile.open(filename);
	
	//v_id,docID,msID_1,msID_2,msID_3,...,n
	while(getline(readFile,data)){
		
		temp = separate(data,delimiter);
		
		for(int i=1; i<temp.size(); i++){
			
			if(temp.at(i)==docID){ //found docID
				
				tempV.push_back(temp.at(0)); //get v_id
				break;
			}
		}
	}
	readFile.close();
	
	
	filename="../data/visitation.txt";
	readFile.open(filename);
	
	//v_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	while(getline(readFile,data)){
		
		temp = separate(data,delimiter);
		
		for(int i=0; i<tempV.size(); i++){
			
			if(tempV.at(i)==temp.at(0)){ //found v_id
				
				//check if clash
				if(type==1){ //ONE-TIME
					
					if(day==stoi(temp.at(2)) && month==stoi(temp.at(3)) && year==stoi(temp.at(4))){
						return true; //clashed						
					}
					
				}
				else if(type=2){ //ROUTINE (check day only)
					
					if(day==stoi(temp.at(2))){
						return true; //clashed
					}
				}
			}
		}
	}
	readFile.close();
	
	
	filename="../data/appointment.txt";
	readFile.open(filename);
	
	//app_ID,patient_IC,app_method,day,month,year,time,priority,app_status,ms_ID(9)
	while(getline(readFile,data)){
	
		temp = separate(data,delimiter);
		
		if (temp.at(9) == docID && stoi(temp.at(7)) != 4){ //same ms_ID & not emergency
			
			if(day==stoi(temp.at(3)) && month==stoi(temp.at(4)) && year==stoi(temp.at(5))){
				return true; //clashed with appointment
			}
			
		}

	}
	readFile.close();
	
	return false;
}

