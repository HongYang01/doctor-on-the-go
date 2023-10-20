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

#include "appointment.h"
#include "display.h"

appointment::appointment(){
	app_priority=1; 	 //unrated
	app_status=1;	 	 //pending
	ms_ID="0";
}

appointment::~appointment(){
}

string appointment::create_id(){
	
	//appointment id format: day month year hour minute second
	
	time_t now = time(0);
	tm *get = localtime(&now);
	
	string date_time;
	
	date_time.append(to_string(get->tm_mday));
	date_time.append(to_string(get->tm_mon+1));
	date_time.append(to_string(get->tm_year+1900));
	date_time.append(to_string(get->tm_hour));
	date_time.append(to_string(get->tm_min));
	date_time.append(to_string(get->tm_sec));

	return date_time;
	
}

void appointment::add_appointment(string patientID){
	
	//get patient IC
	//create appointment ID
	//input information
	//sapp_ID,patient_IC,app_method,day,month,year,time,priority,app_status

	vector<string> line;
	
	start_appointment:
	
	this->app_id = create_id();
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                 Add Appointment                 " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Appointment ID : " << this->app_id << endl;
	cout << "Patient IC     : " << patientID << endl;
	cout << "-------------------------------------------------" << endl;
	
	display_appointment_method(0);	
	cout << "\nChoose Method [0]Back: "; cin >> this->app_method; //offline and online will be stored in a separated file
	
	if(this->app_method==0) return;
	
		char ch;
		
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "                 Add Appointment                 " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Appointment ID : " << this->app_id << endl;
		cout << "Patient IC     : " << patientID << endl;
		cout << "Method         : " << display_appointment_method(this->app_method) << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Date [dd/mm/yyyy] : "; cin >> this->app_day >> ch >> this->app_month >> ch >> this->app_year;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
		if(	date_is_valid(this->app_day,this->app_month,this->app_year)==false ||
			date_smaller_than_today(this->app_day,this->app_month,this->app_year)==true){
			system("CLS");
			cout << "Your date might be: \n";
			cout << ">>> invalid\n>>> smaller than today\n\n";
			system("PAUSE");
			goto start_appointment;
		}
		
		line.push_back(this->app_id);
		line.push_back(patientID);
		line.push_back(to_string(this->app_method));
		line.push_back(to_string(this->app_day));
		line.push_back(to_string(this->app_month));
		line.push_back(to_string(this->app_year));
		
		
		if(	appointment_clash(line)==true){
			system("CLS");
			cout << ">>> Date : " << this->app_day << "-" << display_month(this->app_month) << "-" << this->app_year << endl;
			cout << ">>> Please change the date. It clashed with another schedule\n\n";
			line.clear();
			system("PAUSE");
			goto start_appointment;
		}
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                 Add Appointment                 " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Appointment ID : " << this->app_id << endl;
	cout << "Patient IC     : " << patientID << endl;
	cout << "Method         : " << display_appointment_method(this->app_method) << endl;
	cout << "Date           : " << this->app_day << "-" << display_month(this->app_month) << "-" << this->app_year << endl;
	cout << "-------------------------------------------------" << endl;	
	
	display_hour(0);
	cout << "\nChoose Time: ";
	cin >> this->app_time;
	line.push_back((to_string(this->app_time)));
	
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                 Add Appointment                 " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Appointment ID : " << this->app_id << endl;
	cout << "Patient IC     : " << patientID << endl;
	cout << "Method         : " << display_appointment_method(this->app_method) << endl;
	cout << "Date           : " << this->app_day << "-" << display_month(this->app_month) << "-" << this->app_year << endl;
	cout << "Time           : " << display_hour(this->app_time) << endl;
	cout << "-------------------------------------------------" << endl;	
	
	//Choosing symptom
	vector<string> chosen;
	
	if(this->app_method==1){ //online : choose symptom
		
		chosen = add_symptom(); //passing app_id
	
	}	
	
	line.push_back(to_string(this->app_priority));	//default=1=UNRATED
	line.push_back(to_string(this->app_status));	//default=1=PENDING
	line.push_back(this->ms_ID);					//default=0=none
	


	/* ---------------------------- Confirm Appointment ---------------------------- */
	start_appointment2:
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                 Add Appointment                 " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Appointment ID : " << this->app_id << endl;
	cout << "Patient IC     : " << patientID << endl;
	cout << "Method         : " << display_appointment_method(this->app_method) << endl;
	cout << "Date           : " << this->app_day << "-" << display_month(this->app_month) << "-" << this->app_year << endl;
	cout << "Time           : " << display_hour(this->app_time) << endl;
	
	if(this->app_method==1){
		cout << "Symptom        : ";
	
		for(int i=0; i<chosen.size(); i++){
			cout << display_symptom(stoi(chosen.at(i))) << (i<chosen.size()-1 ? ", " : "");
		}
		cout << endl;
	}
	
	cout << "Priority       : " << display_priority_type(this->app_priority) << endl;
	cout << "Status         : " << display_appointment_status(this->app_status) << endl;
	
		
	int nav;
	cout << "-------------------------------------------------" << endl;
	cout << "You may edit the appointment later" << endl;
	cout << "Confirm this appointment? [0]No [1]Yes : ";
	cin >> nav;
	
	if(nav==0){ //cancel appointment
	
		cout << "Sure to cancel the appointment? [0]No [1]Yes : ";
		cin >> nav;
		
		if(nav==1){
			chosen.clear();
			line.clear();
			return;
		}
		else{
			goto start_appointment2;
		}
		
	}
	else if(nav==1){ //save appointment
		
		save_appointment("../data/appointment.txt",line);
		
		if(this->app_method==1){ //ONLINE CONSULTATION
			//save appointment symptom
			chosen.insert(chosen.begin() + 0, this->app_id); //insert app_id to front
			save_appointment("../data/appointment_symptom.txt",chosen);
		}
		
		line.clear();
		chosen.clear();
		
	}
	else{
		goto start_appointment2;
	}
	
}

vector<string> appointment::add_symptom(){
	
	//patient can choose symptom only if select ONLINE CONSULTATTION
	//return the selected symptom
	
	vector<string> tempLine;
	int nav;
	bool dup=false, done=false;
	
	while(done==false){
		
		dup=false;
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "                   Add Symptom                   " << endl;
		cout << "-------------------------------------------------" << endl;
		
		if(tempLine.size()>0){
			for(int i=0; i<tempLine.size(); i++){
				cout << left << "["
					 << setw(2) << i+1 << "] " << display_symptom(stoi(tempLine.at(i))) << endl; 
			}
			cout << "-------------------------------------------------" << endl;
		}
		
		display_symptom(0);
		
		if(tempLine.size()>0) cout << "\nTo remove any symptom use negative value [-n]remove";
		
		cout << "\nChoose [0]Done : ";
		cin >> nav;
		
		if(nav==0 && tempLine.size()>0){
			done=true;
		}
		else if(nav>0 && nav<=13){ //good attempt
			
			for(int i=0; i<tempLine.size(); i++){
				if(nav==stoi(tempLine.at(i))){ //check duplication
					dup=true; break;
				}
			}
				
			if(dup==false) tempLine.push_back(to_string(nav));
			
		}
		else if(nav<0 && (abs(nav)-1)<=tempLine.size() && tempLine.size()>0){ //removing symptom
			
			tempLine.erase(tempLine.begin() + abs(nav)-1 ); //using negative value to remove symptom
						
		}
		else if(nav==0 && tempLine.size()==0){ //not yet select any symptom
			system("CLS"); cout << ">>> No symptom selected yet"; sleep(2); done=false;
		}
		else if(nav<0 && abs(nav)>tempLine.size()){ //removing symptom that is not in the list
			system("CLS"); cout << ">>> Nothing to remove at " << nav; sleep(2); done=false;
		}
		else{
			system("CLS"); cout << ">>> Nothing found : " << nav; sleep(2); done=false;
		}
	}

return tempLine;
	
}

void appointment::modify_symptom(vector<string> tempApp){
	
	vector<string> tempLine;
	
	ifstream readFile;
	string data, delimiter=",";
	string filename = "../data/appointment_symptom.txt";
	readFile.open(filename);
	int reserved_data=1; //app_ID in vector
	
	while(getline(readFile,data)){
		if(data.find(tempApp.at(0)) != string::npos){ //match app_id
			tempLine = separate(data,delimiter);
			break;
		}
	}
	readFile.close();
	
	if(tempLine.size()==reserved_data){
		system("CLS"); cout << ">>> No symptom found"; sleep(2);
	}
	
	int nav;
	bool dup=false, done=false;
	
	while(done==false){
		
		dup=false;
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "                  Edit Symptom                   " << endl;
		cout << "-------------------------------------------------" << endl;
		
		//app_ID,app_method,s1,s2,s3,...,n
		for(int i=reserved_data; i<tempLine.size(); i++){
			cout << left << "["
				 << setw(2) << i << "] " << display_symptom(stoi(tempLine.at(i))) << endl; 
		}
		
		cout << "-------------------------------------------------" << endl;
		
			display_symptom(0);
		
		if(tempLine.size()>reserved_data) cout << "\nTo remove any symptom use negative value [-n]remove";
		
		cout << "\nChoose [0]Done : ";
		cin >> nav;
		
		if(nav==0 && tempLine.size()>reserved_data){
			done=true;
		}
		else if(nav>0 && nav<=13){ //good attempt (total only 13 symptom)
			
			for(int i=reserved_data; i<tempLine.size(); i++){
				if(nav==stoi(tempLine.at(i))){ //check duplication
					dup=true; break;
				}
			}
				
			if(dup==false) tempLine.push_back(to_string(nav));
			
		}
		else if(nav<0 && (abs(nav)-1)<=tempLine.size()-reserved_data && tempLine.size()>reserved_data){ //removing symptom
			
			tempLine.erase(tempLine.begin() + abs(nav)-1+reserved_data ); //using negative value to remove symptom
						
		}
		else if(nav==0 && tempLine.size()==reserved_data){ //not yet select any symptom (2 because infront have app_id & method)
			system("CLS"); cout << ">>> No symptom selected yet"; sleep(2); done=false;
		}
		else if(nav<0 && abs(nav)>tempLine.size()-reserved_data){ //removing symptom that is not in the list
			system("CLS"); cout << ">>> Nothing to remove at " << nav; sleep(2); done=false;
		}
		else{
			system("CLS"); cout << ">>> Nothing found : " << nav; sleep(2); done=false;
		}
	}
	
	
	if(done==true){
		save_appointment("../data/appointment_symptom.txt",tempLine);
	}
	
}

bool appointment::appointment_clash(vector<string> check){
	
	//app_id,patient_IC,app_method,day,month,year,time,priority,app_status,med_ID
	//true : clashed
	//false: no clash
	
	//read appointment file
	//find patient_IC
	//Conmpare app_method
	//Compare date (if same reject)
	
	string filename = "../data/appointment.txt";
	ifstream readFile;
	
	readFile.open(filename);
	
	if(readFile.fail()){
		system("CLS"); cout << ">>> File not found: " << filename; sleep(2);
	}
	else{
		
		vector<string> tempLine;
		string data;
		string delimiter= ",";
		size_t pos = 0;
		
		while(getline(readFile,data,'\n')){
			
			if(data.length()>0){ //check if only have data
				pos = 0;
				while ((pos = data.find(delimiter)) != string::npos) { //put data into vector using delimeter
					
					tempLine.push_back(data.substr(0, pos));
					data.erase(0, pos + delimiter.length());
					
			    }
				tempLine.push_back(data.substr(0, pos)); //the last data from the line
			
				
				//check if any date clashed (patientIC & date(DD,MMM,YYYY))
				if(	check.at(1)==tempLine.at(1) && check.at(3)==tempLine.at(3) &&
					check.at(4)==tempLine.at(4) && check.at(5)==tempLine.at(5)){
						
						system("CLS");
						cout << ">>> Date: " << check.at(3) << "-" << display_month(stoi(check.at(4))) << "-" << check.at(5)
						<< " already have an appointment\n\n";
						system("PAUSE");
						tempLine.clear();
						return true;
				}
				tempLine.clear();
			}
			
		}
		return false;
	}
	
}

void appointment::edit_appointment(string patientID){
	
	//get patient ID
	//check file for patient ID & app_status=1(pending)
		//only the unrated appointment can be edited
	//ask user to select which appointment to edit
	//prompt menu to edit
	//save detail after edit
	
	vector<vector<string>> tempApp2D;
	int role=2; //2=patient
	
	start_edit:
		
	tempApp2D.clear();
	
	tempApp2D = search_appointment(patientID,1); //patient pending appointment
	
	//print appointment ID that can edit
	system("CLS");
	cout << "Only Pending Appointment can be edited" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "                Edit Appointment                 " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << left << "No. " << setw(20) << "ID" << setw(20) << "Method" << setw(20) << "Date" << "Time" << endl;
	
	int i=1;
	for(vector<string> temp : tempApp2D){
		cout << "[" << i++ << "] ";
		preview_appointment(temp, role);
		
	}
	cout << "-------------------------------------------------" << endl;
	
	int choose;
	cout << "Choose [0]Back : "; cin >> choose;
	
	if(choose==0){
		return;
	}
	else if(choose<0 || choose>tempApp2D.size()){
		goto start_edit;
	}
	else{
		
		start_edit2:
			
		vector<string> temp1D = tempApp2D[choose-1];
		
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "                Edit Appointment                 " << endl;
		cout << "-------------------------------------------------" << endl;
		
		fullview_appointment(temp1D);
		
		cout << "-------------------------------------------------" << endl;
		
		int edit;
		cout << "\nChoose to edit [0]Back : "; cin >> edit;
		
		switch(edit){
			case 0:{
				goto start_edit;
			}
			case 1:{ //edit date
				
				start_new_date:
				
				vector<string> date;
				int input;
				
				//app_id,patient_IC,app_method,day,month,year
				date.push_back(temp1D.at(0));
				date.push_back(temp1D.at(1));
				date.push_back(temp1D.at(2));
				
				
				char ch;
				int day,month,year;
				string inputdate;
		
				system("CLS");
				cout << "-------------------------------------------------" << endl;
				cout << "                     New Date                    " << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Previous Date                 : " << temp1D.at(3) << "-" << display_month(stoi(temp1D.at(4))) << "-" << temp1D.at(5) << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "New Date [dd/mm/yyyy] [0]Back : "; getline(cin >> ws, inputdate);
				
				if(inputdate=="0"){
					goto start_edit2;
				}
				else if(separate(inputdate,"/").size()!=3){
					system("CLS"); cout << ">>> Invalid date"; sleep(2);
					goto start_new_date;
				}
				else{
					day=stoi(separate(inputdate,"/").at(0));
					month=stoi(separate(inputdate,"/").at(1));
					year=stoi(separate(inputdate,"/").at(2));
				}
				
				if( date_is_valid(day,month,year)==false ||
					date_smaller_than_today(day,month,year)==true){
					system("CLS");
					cout << "Your date might be: \n";
					cout << ">>> invalid\n>>> smaller than today\n\n";
					system("PAUSE");
					goto start_new_date;
				}
				
				date.push_back(to_string(day));
				date.push_back(to_string(month));
				date.push_back(to_string(year));
				
				
				if(appointment_clash(date)==true){
					date.clear();
					goto start_new_date;
				}
				else{ //data is valid
					
					system("CLS");
					cout << "-------------------------------------------------" << endl;
					cout << "                     New Date                    " << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "Previous Date : " << temp1D.at(3) << "-" << display_month(stoi(temp1D.at(4))) << "-" << temp1D.at(5) << endl;
					cout << "New Date      : " << date.at(3) << "-" << display_month(stoi(date.at(4))) << "-" << date.at(5) << endl;
					cout << "-------------------------------------------------" << endl;
					system("PAUSE");
					
					//push in the rest of the unmodify data
					date.push_back(temp1D.at(6));
					date.push_back(temp1D.at(7));
					date.push_back(temp1D.at(8));
					
					string filename ="../data/appointment.txt";
					save_appointment(filename, date);
				
				}
				
				break;
			}
			case 2:{ //edit time
				
				vector<string> time;
				int input;
				
				start_edit_time:
				
				//app_ID,patient_IC,app_method,day,month,year,time,priority,app_status,ms_ID
				for(int i=0; i<6; i++){
					time.push_back(temp1D.at(i));
				}
				
				system("CLS");
				cout << "-------------------------------------------------" << endl;
				cout << "                     New Time                    " << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Previous Time : " << display_hour(stoi(temp1D.at(6))) << endl;
				cout << "-------------------------------------------------" << endl;
				display_hour(0);
				cout << "New Time      : "; cin >> input;
				
				if(input<=0 || input>11){
					time.clear(); goto start_edit_time;
				}
				else{
					time.push_back(to_string(input));
					time.push_back(temp1D.at(7));
					time.push_back(temp1D.at(8));
					
					string filename ="../data/appointment.txt";
					save_appointment(filename, time);
				}
				
				break;
			}
			case 3:{ //edit symptom
				
				modify_symptom(temp1D);
				
				break;
			}
			default:{
				break;
			}
		}
		goto start_edit;
		
		
	}
	
}

void appointment::preview_appointment(vector<string> tempAppLine, int role){
	
	//previewing appointment
	//PATIENT : app_id,app_method,date,time
	//DOCTOR  : patient_name,app_method,date,time
	
	if(u2.search_user(tempAppLine.at(1))==false){ //getting patient data
		system("CLS"); cout << ">>> Patient detail not found"; sleep(2);
		return;
	}
	
	switch(role){
		case 2:{ //PATIENT
			cout << left 
				 << setw(20) << tempAppLine.at(0)
				 << setw(20) << display_appointment_method(stoi(tempAppLine.at(2)));
			cout << left << tempAppLine.at(3) << "-" << display_month(stoi(tempAppLine.at(4))) << "-" << tempAppLine.at(5) << "\t\t";
			cout << display_hour(stoi(tempAppLine.at(6))) << endl;
			break;
		}
		case 3:{ //DOCTOR
			cout << left
				 << setw(20) << u2.get_userName()
				 << setw(20) << display_appointment_method(stoi(tempAppLine.at(2)));
			cout << left << tempAppLine.at(3) << "-" << display_month(stoi(tempAppLine.at(4))) << "-" << tempAppLine.at(5) << "\t\t";
			cout << display_hour(stoi(tempAppLine.at(6))) << endl;
			break;
		}
	}
	
}

void appointment::fullview_appointment(vector<string> tempAppLine){
	
	//verification,role,IC,name,age,gender,race,street,city,phone,email,password
	//app_ID(0),patient_IC(1),app_method,day,month,year,time,priority,app_status,ms_ID
	//app_ID,s1,s2,s3,...,sN
	vector<string> tempSymptom;
	
	if(u2.search_user(tempAppLine.at(1))==false){
		system("CLS"); cout << ">>> Patient detail not found"; sleep(2);
		return;
	}
	
	if(stoi(tempAppLine.at(2))==1){ //online (get symptom)
		tempSymptom = associated_symptom(tempAppLine.at(0));
		if(tempSymptom.size()==0){
			system("CLS"); cout << ">>> Patient symptom not found"; sleep(2);
			return;
		}
	}
	
	cout << "-------------------------------------------------" << endl;
	cout << "                  Patient Detail                 " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "    IC            : " << u2.get_userID() << endl;
	cout << "    Name          : " << u2.get_userName() << endl;
	cout << "    Age           : " << u2.get_userAge() << endl;
	cout << "    Gender        : " << display_gender(u2.get_userGender()) << endl;
	cout << "    Race          : " << display_race(u2.get_userRace()) << endl;
	cout << "    Address       : " << u2.get_userStreet() << ", " << display_city(u2.get_userCity()) << endl;
	cout << "    Phone         : " << u2.get_userPhone() << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "                 Appointment Detail              " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "    App ID        : " << tempAppLine.at(0) << endl;
	cout << "    Patient IC    : " << tempAppLine.at(1) << endl;
	cout << "    Method        : " << display_appointment_method(stoi(tempAppLine.at(2))) << endl;
	cout << "[1] Date          : " << tempAppLine.at(3) << "-" << display_month(stoi(tempAppLine.at(4))) << "-" << tempAppLine.at(5) << endl;
	cout << "[2] Time          : " << display_hour(stoi(tempAppLine.at(6))) << endl;
	cout << "    Priority      : " << display_priority_type(stoi(tempAppLine.at(7))) << endl;
	cout << "    Status        : " << display_appointment_status(stoi(tempAppLine.at(8))) << endl;
	
	if(stoi(tempAppLine.at(2))==1){ //ONLINE CONSULTATION
		cout << "[3] Symptom       : ";
		for(int i=1; i<tempSymptom.size(); i++){ //0=app_id
			cout << display_symptom(stoi(tempSymptom.at(i))) << (i < tempSymptom.size()-1? ", " : "");
		}
		cout <<endl;
	}
	
	string data;
	ifstream readFile;
	
	//app_ID,patient_IC,app_method,day,month,year,time,priority,app_status,ms_ID
	
	if(stoi(tempAppLine.at(8))==2 && stoi(tempAppLine.at(7))!=4){ //approved & not emergency
		
		if(stoi(tempAppLine.at(2))==2){ //screening
			
			readFile.open("../data/appointment_screening.txt");
			//app_id,hos_id
			while(getline(readFile,data)){
			
				if(separate(data,",").at(0) == tempAppLine.at(0)){ //same app_id

					hos7.search_hospital(separate(data,",").at(1)); //search hospital detail using hos_id
					hos7.view_hospital_detail();
					break;
				}
			
			}
			readFile.close();
			
		}
		else{ //treatment/visitation
			
			//treatment & medication plan
			readFile.open("../data/appointment_treatment_medication.txt");
			while(getline(readFile,data)){
				
				if(separate(data,",").at(0) == tempAppLine.at(0)){ //same app_id
					cout << "-------------------------------------------------" << endl;
					cout << "Treatment :\n";
					cout << separate(data,",").at(1) << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "Medication Plan :\n";
					cout << separate(data,",").at(2) << endl;
					break;
				}
			}
			readFile.close();
			
			//visitation
			readFile.open("../data/visitation.txt");
			while(getline(readFile,data)){
				
				if(separate(data,",").at(0) == tempAppLine.at(0)){
					cout << "-------------------------------------------------" << endl;
					cout << "                Visitation Detail                " << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "ID      : " << separate(data,",").at(0) << endl;
					cout << "Type    : " << display_visitation_type(stoi(separate(data,",").at(1))) << endl;
					cout << "Date    : " << separate(data,",").at(2) << "-" << display_month(stoi(separate(data,",").at(3))) << "-" << separate(data,",").at(4) << endl;
					cout << "Time    : " << display_hour(stoi(separate(data,",").at(5))) << endl;
					cout << "Address : " << separate(data,",").at(6) << ", " << display_city(stoi(separate(data,",").at(7))) << endl;
					
					readFile.open("../data/transportation.txt");
					
					//trans_id,hos_ID,trans_type
					while(getline(readFile,data)){
						
						if(separate(data,",").at(0) == separate(data,",").at(8)){
							trans.fullview_trans_detail(separate(data,","));
							break;
						}
						
					}
					readFile.close();
					break;
				}
			}
		}
	}
	else if(stoi(tempAppLine.at(7))==4){ //EMERGENCY
		
		readFile.open("../data/appointment_emergency.txt");
		while(getline(readFile,data)){
		
			if(separate(data,",").at(0) == tempAppLine.at(0)){//same app_id
			
				hos7.search_hospital(separate(data,",").at(1));
				hos7.view_hospital_detail();
				break;
			}
		
		}
		readFile.close();
	
	}
}

vector<vector<string>> appointment::search_appointment(string ID, int status){
	
	//ID	: can be patient/medical staff ID
	//status: 1=Pending, 2=Approved, 3=Rejected
	
	vector<vector<string>> returnLine;
	vector<string> tempLine;
	string data;
	string delimiter= ",";
	size_t pos = 0;
	
	ifstream readFile;
	string filename = "../data/appointment.txt";
	readFile.open(filename);
	
	if(readFile.fail()){
		system("CLS"); cout << ">>> File not found: " << filename; sleep(2); return returnLine;
	}
	else if(file_is_empty(readFile)){
		system("CLS"); cout << ">>> File is empty"; sleep(2); return returnLine;
	}
	else{
		
		/* ------ read file ------ */
		while(getline(readFile,data,'\n')){
			
			pos = 0;
			tempLine.clear();
			
			while ((pos = data.find(delimiter)) != string::npos) { //put data into vector using delimeter
				
				tempLine.push_back(data.substr(0, pos));
				data.erase(0, pos + delimiter.length());
				
		    }
			tempLine.push_back(data.substr(0, pos)); //the last data from the line
			
			//match patient ID & app_status
			if(tempLine.at(1)==ID && stoi(tempLine.at(8))==status){
				
				returnLine.push_back(tempLine); //return appointment detail

			}
		}
	}
	readFile.close();
	return returnLine;
	
}

vector<string> appointment::search_appointment(string ID){
	
	//return appointment detail based on app_id
	
	ifstream readFile;
	string data, delimiter=",", filename="../data/appointment.txt";
	readFile.open(filename);
	
	vector<string> temp;
	
	if(readFile.fail()){
		system("CLS"); cout << ">>> File not found: " << filename << endl; sleep(2); return temp;
	}
	
	//app_ID,patient_IC,app_method,day,month,year,time,priority,app_status,ms_ID
	while(getline(readFile,data)){
		
		temp = separate(data,delimiter);
		
		if(temp.at(0) == ID)
			return temp;
		
	}
	readFile.close();
	temp.clear();
	
	system("CLS"); cout << ">>> Appointment ID Not Found: " << ID; sleep(2);

return temp;
	
}

vector<string> appointment::associated_symptom(string ID){
	
	//get app_id
	//search for selected symptom/treatment
	//return the list (app_id,app_method,...)
	
	ifstream readFile;
	string data, delimiter = ",", filename="../data/appointment_symptom.txt";
	readFile.open(filename);
	
	vector<string> line;
	
	if(readFile.fail()){
		system("CLS"); cout << ">>> File not found: " << filename; sleep(2); return line;
	}
	else{
		
		while(getline(readFile,data,'\n')){
			
			line = separate(data,delimiter);
			
			if(line.at(0)==ID){ //found
				return line;
			}
		}
		line.clear();
		
		system("CLS"); cout << ">>> No Symptom Found"; sleep(2); return line;
	}
	
}

void appointment::save_appointment(string filename, vector<string> tempLine){
	
	//app_ID,patient_IC,app_method,day,month,year,time,priority,app_status,ms_ID
	
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
		
		if(line2D[i][0]==tempLine.at(0)){ //same app_id
			
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

bool appointment::check_appointment_expired(){
	
	ifstream readFile;
	string filename = "../data/appointment.txt"; 
	readFile.open(filename);
	
	if(readFile.fail()){
		cout << ">>> File not found: " << filename << endl; sleep(2); return false;
	}
	
	vector<vector<string>> temp2D;
	string data, delimiter=",";
	
	while(getline(readFile,data)){
		
		temp2D.push_back(separate(data,delimiter));
		
	}
	readFile.close();
	
	if(temp2D.size()==0) return true;
	
	//app_ID,patient_IC,app_method,day,month,year,time,priority,app_status,ms_ID
	int i=0;
	for(vector<string> temp : temp2D){
		
		if(stoi(temp.at(8))==1){//if pending
			
			if(date_smaller_than_today(stoi(temp.at(3)),stoi(temp.at(4)),stoi(temp.at(5))) == true){ //day month year
				temp2D[i][8] = "4"; //become expired
			}
		}
		i++;
	}
	
	ofstream writeFile;
	writeFile.open(filename);
	
	i=0;
	for(vector<string> temp : temp2D){
		
		writeFile << join(temp,delimiter) << (i<temp2D.size()-1 ? "\n" : "");

		i++;
	}
	writeFile.close();
	temp2D.clear();
	
return true;	
}







