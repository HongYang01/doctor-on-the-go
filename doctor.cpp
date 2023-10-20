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
#include "doctor.h"
#include "appointment.h"
#include "transportation.h"

doctor::doctor(){
}

doctor::~doctor(){
}

void doctor::main_menu(){
	
	int nav;
	
	start_doctor:
	
	do{
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "                Doctor Main Menu                 " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "[1] View Upcoming Schedule" << endl;
		cout << "[2] Add Routine Visitation" << endl;
		cout << "[3] Approve Pending Appointment" << endl;
		cout << "[4] Monitor Patient Health Status" << endl;
		cout << "[5] View Summary" << endl;
		cout << "[6] My Profile" << endl;
		cout << "\nChoose [0]Logout : "; cin >> nav;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
	}while(nav<0 || nav>6);
	
	switch(nav){
		case 0:{
			system("CLS");
			cout << "Confirm to logout? [0]No [1]Yes: ";
			cin >> nav;
			cin.clear(); cin.ignore(INT_MAX,'\n');
			if(nav==1) return;
			break;
		}
		case 1:{
			view_upcoming_schedule();
			break;
		}
		case 2:{
			
			do{
				system("CLS");
				cout << "-------------------------------------------------" << endl;
				cout << "             Add Routine Visitation              " << endl;
				cout << "-------------------------------------------------" << endl;
				cout << ">>> Sure to add routine visitation? [1]Yes [0]No : "; cin >> nav;
				cin.clear(); cin.ignore(INT_MAX,'\n');
			}while(nav<0 || nav>1);
			
			if(nav==1) 	v.add_visitation(app3.create_id(),this->userID,2);
			
			break;
		}
		case 3:{ //approve appointment
			approve_appointment();
			break;
		}
		case 4:{ //monitor patient health status
			monitor_patient_health_status();
			break;
		}
		case 5:{ //view system summary
			view_summary();
			break;
		}
		case 6:{ //view profile
			my_profile();
			hos.view_hospital_detail();
			system("PAUSE");
			break;
		}
		default:{
			break;
		}
	}
	goto start_doctor;
	
	
}

void doctor::approve_appointment(){
	
	//get patient pending appointment
	//approve/reject appointment
	
start_approve:
	
	vector<string> line1D;
	ifstream readFile;
	string data, filename;
	string delimiter=",";
	size_t pos=0;
	
	
	//app_ID,patient_IC,app_method,day,month,year,time,priority,app_status,med_ID
	filename = "../data/appointment.txt";
	readFile.open(filename);
	
	vector<vector<string>> appLine2D;
	while(getline(readFile,data,'\n')){
		
		pos = 0; line1D.clear();
		
		line1D = separate(data,",");
		
		if(stoi(line1D.at(8))==1){ // all pending appointment
			appLine2D.push_back(line1D);
		}
	}
	readFile.close();
	
	if(appLine2D.size()==0){
		system("CLS"); cout << ">>> No pending appointment found"; sleep(3); return;
	}
	
	
	//verification,role,IC,name,age,gender,race,street,city,phone,email,password
	filename = "../data/userData.txt";
	
	vector<vector<string>> matchAppLine2D, matchPatientLine2D;
	for(vector<string> tempLine1D : appLine2D){ //loop appLine2D
		
		readFile.open(filename); //must reopen file
		
		while(getline(readFile,data,'\n')){
		
			if(data.find(tempLine1D.at(1)) != string::npos){ //found patient ID
				
				pos = 0;
				line1D.clear();
				
				line1D = separate(data,",");
				
				matchAppLine2D.push_back(tempLine1D);
				matchPatientLine2D.push_back(line1D);
					
			}
		}
		readFile.close();
	}
	
	if(matchAppLine2D.size()==0 || matchPatientLine2D.size()==0){
		system("CLS"); cout << ">>> No appointment found"; sleep(3); return;
	}
	
start_choose:
		
	string str;
	int i=1, choose=0, nav;
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "               Approve Appointment               " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << left << "No. " << setw(20) << "Name" << setw(20) << "Method" << setw(20) << "Date" << "Time" << endl;
	cout << "-------------------------------------------------" << endl;
	for(vector<string> tempLine1D : matchAppLine2D){
		
		cout << "[" << i++ << "] ";
		
		app3.preview_appointment(tempLine1D,this->userRole);
		
	}
	cout << "-------------------------------------------------" << endl;
	cout << "Size: " << matchAppLine2D.size() << "\n";
	cout << "\nChoose [0]Back : ";
	cin >> choose;
	
	if(choose==0){
		return;
	}
	
	if(choose<0 || choose>matchAppLine2D.size()){
		goto start_choose;
	}
	else{
		
		//check if clash with other schedule (1=check exact date)
			cout << "pass 1\n";
			cout << v.visitation_clash(this->userID,1,stoi(matchAppLine2D[choose-1][3]),stoi(matchAppLine2D[choose-1][4]),stoi(matchAppLine2D[choose-1][5])) << endl;
			cout << "pass 2\n";
		if(v.visitation_clash(this->userID,1,stoi(matchAppLine2D[choose-1][3]),stoi(matchAppLine2D[choose-1][4]),stoi(matchAppLine2D[choose-1][5]))==true){
			system("CLS");
			cout << ">>> Date : " << stoi(matchAppLine2D[choose-1][3]) << "-" << display_month(stoi(matchAppLine2D[choose-1][4])) << "-" << stoi(matchAppLine2D[choose-1][5]) << endl;
			cout << ">>> It clashed with another schedule, change another appointment\n\n";
			system("PAUSE");
			goto start_choose;
		}
		
		
		start_approve2:
		
		vector<string> holdApp;
		vector<string> holdPatient;
		
		i=0;
		for(vector<string> temp : matchAppLine2D){
			if(i++==choose-1){
				holdApp = temp;
				break;
			}
		}
		i=0;
		for(vector<string> temp : matchPatientLine2D){
			if(i++==choose-1){
				holdPatient = temp;
				break;
			}
		}
		
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "               Approve Appointment               " << endl;
		cout << "-------------------------------------------------" << endl;
		app3.fullview_appointment(holdApp); //full view
		cout << "\n-------------------------------------------------" << endl;
		cout << "\n[0]Back [1]Approve [2]Reject: "; cin >> nav;
		
		if(nav==0){
			goto start_choose;
		}
		else if(nav<0 || nav>2){
			goto start_approve2;
		}
		else if(nav==2){ //REJECT
			
			cout << "\nSure to reject this appointment? [1]Yes [0]No : ";
			cin >> nav;
			
			if(nav==1){
				holdApp.at(8)="3"; 		 	//rejected
				holdApp.at(9)=this->userID; //rejected by who
				app3.save_appointment("../data/appointment.txt",holdApp);
				return;
			}
			else{
				goto start_approve2;
			}
		}
		else if(nav==1 && stoi(holdApp.at(2))==2){ //APPROVE offline screening
			
			cout << "\nSure to approve this appointment? [1]Yes [0]No : ";
			cin >> nav;
			
			if(nav!=1) goto start_approve2;
			
			vector<vector<string>> tempHos2D;
			vector<string> healthScreening;
			
			do{ //asign to nearby hospital
				system("CLS");
				cout << "-------------------------------------------------" << endl;
				cout << "           Health Screening Appointment          " << endl;
				cout << "-------------------------------------------------" << endl;
				app3.fullview_appointment(holdApp);
				cout << "-------------------------------------------------" << endl;
				
				tempHos2D = hos.search_hospital(stoi(holdPatient.at(8)));
				
				cout << left << "No. " << setw(20) << "Name" << endl;
				
				i=1;
				for(vector<string> temp : tempHos2D){
					cout << "[" << i++ << "] ";
					cout << left << setw(20) << temp.at(1) << endl;
				}
			
				cout << "\nChoose nearby hospital for patient : "; cin >> nav;
				
			}while(nav<=0 || nav>tempHos2D.size());
			
			healthScreening.push_back(holdApp.at(0)); //app_id
			healthScreening.push_back(tempHos2D[nav-1][0]); //hospitalID
			
			holdApp.at(8)="2"; 		 	//approved
			holdApp.at(9)=this->userID; //approved by who
			
			system("CLS");
			cout << "-------------------------------------------------" << endl;
			cout << "           Health Screening Appointment          " << endl;
			cout << "-------------------------------------------------" << endl;
			app3.fullview_appointment(holdApp);
			cout << "-------------------------------------------------" << endl;
			cout << "               Associated Hospital               " << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "ID      : " << tempHos2D[nav-1][0] << endl;
			cout << "Name    : " << tempHos2D[nav-1][1] << endl;
			cout << "Address : " << tempHos2D[nav-1][2] << ", " << display_city(stoi(tempHos2D[nav-1][3])) << endl;
			cout << "Phone   : " << tempHos2D[nav-1][4] << endl;
			cout << "-------------------------------------------------" << endl;
			system("PAUSE");
			
			app3.save_appointment("../data/appointment.txt",holdApp);
			app3.save_appointment("../data/appointment_screening.txt",healthScreening);
			
		
		}
		else if(nav==1 && stoi(holdApp.at(2))==1){ //APPROVE online consultation
			
			cout << "\nSure to approve this appointment? [1]Yes [0]No : ";
			cin >> nav;
			
			if(nav!=1) goto start_approve2;
			
			holdApp.at(8)="2"; 		 	//aprroved
			holdApp.at(9)=this->userID; //aprroved by who
			
			do{
				system("CLS");
				cout << "-------------------------------------------------" << endl;
				cout << "               Approve Appointment               " << endl;
				cout << "-------------------------------------------------" << endl;
				app3.fullview_appointment(holdApp);
				cout << "-------------------------------------------------" << endl;
				display_priority_type(0);
				cout << "\nChoose Priority : "; cin >> nav;
			}while(nav<=1 || nav>4); //cannot UNRATED/>4
			
			holdApp.at(7) = to_string(nav);
			
			
			if(holdApp.at(7)=="4"){ //EMERGENCY
				
				vector<vector<string>> tempHos2D;
				vector<string> emergency;
				
				do{
					system("CLS");
					cout << "-------------------------------------------------" << endl;
					cout << "              Emergency Appointment              " << endl;
					cout << "-------------------------------------------------" << endl;
					app3.fullview_appointment(holdApp);
					cout << "-------------------------------------------------" << endl;
					
					tempHos2D = hos.search_hospital(stoi(holdPatient.at(8))); //search hospital based on city
					
					cout << left << "No. " << setw(20) << "Name" << endl;
					
					i=1;
					for(vector<string> temp : tempHos2D){
						cout << "[" << i++ << "] ";
						cout << left << setw(20) << temp.at(1) << endl;
					}
				
					cout << "\nChoose nearby hospital for patient : "; cin >> nav;
					
				}while(nav<=0 || nav>tempHos2D.size());
				
				emergency.push_back(holdApp.at(0)); //app_id
				emergency.push_back(tempHos2D[nav-1][0]); //hospitalID
				
				system("CLS");
				cout << ">>> Emergency transportation is assigned to patient"; sleep(2);
				app3.save_appointment("../data/appointment.txt",holdApp);
				app3.save_appointment("../data/appointment_emergency.txt",emergency);
				goto start_approve;
				
			}
			else if(holdApp.at(7)=="2" || holdApp.at(7)=="3"){ //LOW or MODERATE
				
				bool flag;
				do{
					flag=false;
					system("CLS");
					cout << "-------------------------------------------------" << endl;
					cout << "             Low/Moderate Appointment            " << endl;
					cout << "-------------------------------------------------" << endl;
					app3.fullview_appointment(holdApp);
					cout << "-------------------------------------------------" << endl;
					cout << "[1] Manage Treatment & Medication Plan" << endl;
					cout << "[2] Schedule ONE-TIME visitation" << endl;
					
					cout << "\nChoose : "; cin >> nav;
					cin.clear(); cin.ignore(INT_MAX,'\n');
					
					if(nav==2 && stoi(holdPatient.at(8))!=hos.get_hosCity()){ //check if same city with doc hospital
						system("CLS");
						cout << ">>> Different city are not allowed for visitation: " 
							 << endl << ">>> Patient      : " << display_city(stoi(holdPatient.at(8)))
							 << endl << ">>> Your Hospital: " << display_city(hos.get_hosCity())
							 << "\n\n";
						system("PAUSE"); nav=-1;
					}
					
					if(nav==1 || nav==2){
						if(nav==1){ //manage treatment & medication plan
							if(add_treatment_medication_plan(holdApp.at(0))==true){
								flag=true;
							}
						}
						else if(nav==2){ //arrange ONE-TIME visitation
							if(v.add_visitation(holdApp.at(0),this->userID,1)==true){//1=ONETIME
								flag=true;
							}
						}
					}
					else{
						flag=false;
					}
					
				}while(flag==false);
				
				app3.save_appointment("../data/appointment.txt",holdApp);
				goto start_approve;
			}
			else{
				goto start_approve2;
			}
		} //approve online consultation
	}
	
}

bool doctor::add_treatment_medication_plan(string ID){
	
	//get app_id
	//app_id, treatment_detail, medication_detail
	
	string treatment, medication;
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "         Add Treatment & Medication Plan         " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Treatment : \n";
	getline(cin >> ws, treatment);
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "         Add Treatment & Medication Plan         " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Treatment : \n";
	cout << treatment;
	cout << "\n\n-------------------------------------------------" << endl;
	cout << "Medication Plan : \n";
	getline(cin >> ws, medication);
	
	
	int nav;
	bool flag;
	
	do{
		flag==false;
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "         Add Treatment & Medication Plan         " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Treatment : \n";
		cout << treatment;
		cout << "\n\n-------------------------------------------------" << endl;
		cout << "Medication Plan : \n";
		cout << medication;
		cout << "\n-------------------------------------------------" << endl << endl;
		
		cout << "\nSave Treatment & Medication Plan? [1]Yes [0]No : "; cin >> nav;
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
			cout << "Cancel Treatment & Medication Plan? [1]Yes [0]No : "; cin >> nav;
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
	
	string delimiter=",", filename="../data/appointment_treatment_medication.txt";
	ofstream writeFile;
	writeFile.open(filename, std::ios_base::app);
	
	if(!writeFile.is_open()){
		system("CLS"); cout << "Fail not found: " << filename; sleep(2); return false;
	}
	else{
		
		writeFile << endl
				  << ID << ","
				  << treatment << ","
				  << medication;
				  
	}
	writeFile.close();
	
	system("CLS"); cout << ">>> Saved treatment & medication plan"; sleep(2);
	
	return true;
}

void doctor::monitor_patient_health_status(){
	
	string patient_id;
	float temperature;
	int day, month, year, blood_pressure, pulse;
	
	int patientRole = 2;
	
	string data, delimiter=",",filename;
	ifstream readFile;
	ofstream writeFile;
	
start_monitor:
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "          Monitor Patient Health Status          " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Patient ID    [0]Back : "; getline(cin >> ws, patient_id);
	
	if(patient_id=="0"){
		return;
	}	
	else if(u4.search_user(patient_id)==false || u4.get_userRole()!=patientRole){ //cheeck if patient ID exist & is a patient
		system("CLS"); cout << "Patient ID not found: " << patient_id << endl << endl; system("PAUSE");
		goto start_monitor;
	}

start_monitor2:

	//search for patient health condition history
	vector<vector<string>> tempHS2d;
	//hs_patient_id,hs_day,hs_month,hs_year,hs_blood_pressure,hs_pulse,hs_temperature
	readFile.open("../data/patient_health_status.txt");
	while(getline(readFile,data)){
		
		if(separate(data,delimiter).at(0) == patient_id){ //found patient health status (if not will may create new later)
			
			tempHS2d.push_back(separate(data,delimiter));
			
		}
		
	}
	readFile.close();
	

	int nav;
	do{
		system("CLS");
		u4.my_profile();
		cout << "-------------------------------------------------" << endl;
		cout << "          Monitor Patient Health Status          " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "[1] Add new health status\n";
		cout << "[2] View Medical History\n";
		
		cout << "\nChoose [0]Back : "; cin >> nav;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
	}while(nav<0 || nav>2);
		
		
		switch(nav){
			case 0:{
				goto start_monitor;
			}
			case 1:{ //add new
				
				vector<string> tempHC;
				
				time_t now = time(0);
				tm *get = localtime(&now);
				
				tempHC.push_back(patient_id);
				tempHC.push_back(to_string(get->tm_mday));
				tempHC.push_back(to_string(get->tm_mon+1));
				tempHC.push_back(to_string(get->tm_year+1900));
				
				system("CLS");
				u4.my_profile();
				cout << "-------------------------------------------------" << endl;
				cout << "          Monitor Patient Health Status          " << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Date                  : " << tempHC.at(1) << "-" << display_month(stoi(tempHC.at(2))) << "-" << tempHC.at(3) << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Blood Pressure (mg/H) : "; cin >> blood_pressure;
				tempHC.push_back(to_string(blood_pressure));
				
				system("CLS");
				u4.my_profile();
				cout << "-------------------------------------------------" << endl;
				cout << "          Monitor Patient Health Status          " << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Date                  : " << tempHC.at(1) << "-" << display_month(stoi(tempHC.at(2))) << "-" << tempHC.at(3) << endl;
				cout << "Blood Pressure (mg/H) : " << tempHC.at(4) << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Pulse (bpm)           : "; cin >> pulse;
				tempHC.push_back(to_string(pulse));
				
				system("CLS");
				u4.my_profile();
				cout << "-------------------------------------------------" << endl;
				cout << "          Monitor Patient Health Status          " << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Date                  : " << tempHC.at(1) << "-" << display_month(stoi(tempHC.at(2))) << "-" << tempHC.at(3) << endl;
				cout << "Blood Pressure (mg/H) : " << tempHC.at(4) << endl;
				cout << "Pulse (bpm)           : " << tempHC.at(5) << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Temperature (celcius) : "; cin >> temperature;
				tempHC.push_back(to_string(temperature));
				
				system("CLS");
				u4.my_profile();
				cout << "-------------------------------------------------" << endl;
				cout << "          Monitor Patient Health Status          " << endl;
				cout << "-------------------------------------------------" << endl;
				cout << "Date                  : " << tempHC.at(1) << "-" << display_month(stoi(tempHC.at(2))) << "-" << tempHC.at(3) << endl;
				cout << "Blood Pressure (mg/H) : " << tempHC.at(4) << endl;
				cout << "Pulse (bpm)           : " << tempHC.at(5) << endl;
				cout << "Temperature (celcius) : " << fixed << setprecision(2) << stof(tempHC.at(6)) << endl;
				cout << "-------------------------------------------------" << endl;
				system("PAUSE");
				
				writeFile.open("../data/patient_health_status.txt");
				tempHS2d.push_back(tempHC);
				
				int i=0;
				for(vector<string> temp : tempHS2d){
					
					writeFile << join(temp,delimiter) << (i<tempHS2d.size()-1 ? "\n" : "");
					i++;
					
				}
				writeFile.close();

				system("CLS"); cout << ">>> Changes are updated successfully"; sleep(2);
				
				break;
			} 
			case 2:{ //view history
				
				view_history:
				
				if(tempHS2d.size()>0){
					
					do{
						system("CLS");
						u4.my_profile();
						cout << "-------------------------------------------------" << endl;
						cout << "             Patient Medical History             " << endl;
						cout << "-------------------------------------------------" << endl;
						int i=1;
						cout << left << setw(5) << "No." << "Date" << endl;
						for(vector<string> temp : tempHS2d){
							
							cout<< left << "[" 
								<< setw(2) << i++ << "] "
								<< temp.at(1) << "-" << display_month(stoi(temp.at(2))) << "-" <<  temp.at(3) << endl;
							
						}
						
						cout << "\nChoose to see detail [0]Back : "; cin >> nav;
						cin.clear(); cin.ignore(INT_MAX,'\n');
						
						if(nav==0) goto start_monitor2;
					}while(nav<0 || nav>tempHS2d.size());
					
					system("CLS");
					u4.my_profile();
					cout << "-------------------------------------------------" << endl;
					cout << "             Patient Medical History             " << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "Date                  : " << tempHS2d[nav-1][1] << "-" << display_month(stoi(tempHS2d[nav-1][2])) << "-" << tempHS2d[nav-1][3] << endl;
					cout << "Blood Pressure (mg/H) : " << tempHS2d[nav-1][4] << endl;
					cout << "Pulse (bpm)           : " << tempHS2d[nav-1][5] << endl;
					cout << "Temperature (celcius) : " << fixed << setprecision(2) << stof(tempHS2d[nav-1][6]) << endl;
					cout << "-------------------------------------------------" << endl;
					system("PAUSE");
					goto view_history;
				}
				else{
					system("CLS"); cout << "No medical history found"; sleep(2);
				}
				
				break;
			}
		}
		goto start_monitor2;
		
		
	
	
	
	
}

void doctor::view_summary(){
	
	string data, delimiter=",", filename;
	ifstream readFile;
	ofstream writeFile;
	int nav;
	int no_city=6;
	int no_race=6;
	int aircraft=3;
	int patient_role=2;
	
start_summary:	
	
	do{
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "                  View Summary                   " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "[1] View Patient By City\n"; //by city
		cout << "[2] View Patient By Race\n"; //by race
		cout << "[3] View All Upcoming Flying Doctor Schedule\n";
		cout << "[4] Your Consultation & Visitation Count\n"; //total consultation & visitation & routine
		cout << "\nChoose [0]Back : "; cin >> nav;
		cin.clear(); cin.ignore(INT_MAX,'\n');
	}while(nav<0 || nav>4);
	
	switch(nav){
		case 0:{
			return;
		}
		case 1:{ //city
			
			system("CLS");
			cout << "-------------------------------------------------" << endl;
			cout << "              View Patient By City               " << endl;
			cout << "-------------------------------------------------" << endl;
			
			int count, total=0;
			for(int i=1; i<=no_city; i++){
				
				count=0;
				
				readFile.open("../data/userData.txt");
				//verification,role,IC,name,age,gender,race,street,city,phone,email,password
				while(getline(readFile,data)){
					
					if(stoi(separate(data,delimiter).at(1))==patient_role && stoi(separate(data,delimiter).at(8))==i){ //patient & city
						
						total++;
						count++;
					}
				}
				readFile.close();
				
				cout << left << ">>> " << setw(15) << display_city(i) <<": " << count << endl;
				
			}
			cout << "-------------------------------------------------" << endl;
			cout << "Total Patient : " << total << endl << endl;
			system("PAUSE");
			
			break;
		}
		case 2:{ //race
			
			system("CLS");
			cout << "-------------------------------------------------" << endl;
			cout << "              View Patient By Race               " << endl;
			cout << "-------------------------------------------------" << endl;
			int count, total=0;
			for(int i=1; i<=no_race; i++){
				
				count=0;
				
				readFile.open("../data/userData.txt");
				//verification,role,IC,name,age,gender,race,street,city,phone,email,password
				while(getline(readFile,data)){
					
					if(stoi(separate(data,delimiter).at(1))==patient_role && stoi(separate(data,delimiter).at(6))==i){ //patient & race
						
						total++;
						count++;
					}
				}
				readFile.close();
				
				cout << left << ">>> " << setw(15) << display_race(i) <<": " << count << endl;
				
			}
			cout << "-------------------------------------------------" << endl;
			cout << "Total Patient : " << total << endl << endl;
			system("PAUSE");
			
			break;
		}
		case 3:{ //flying doctor
			
			system("CLS");
			cout << "-------------------------------------------------" << endl;
			cout << "       All Upcoming Flying Doctor Schedule       " << endl;
			cout << "-------------------------------------------------" << endl;
			cout << left << setw(5) << "No." << setw(15) << "City" << setw(20) << "Date" << "Time" << endl;
			cout << "-------------------------------------------------" << endl;
			int total=0;
			readFile.open("../data/visitation.txt");
			// v_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
			
			
			while(getline(readFile,data)){
				
				trans2.search_transportation(separate(data,delimiter).at(8));
				
				//type is aircraft
				if(trans2.get_transType()==aircraft){
					
					//date is larger than today
					if(date_smaller_than_today(stoi(separate(data,delimiter).at(2)),stoi(separate(data,delimiter).at(3)),stoi(separate(data,delimiter).at(4)))==false){
						
						if(stoi(separate(data,delimiter).at(5))<5){ //morning
							
							cout<< left << "[" 
							 	<< setw(2) << total+1 << "] "
							 	<< setw(15) << display_city(stoi(separate(data,delimiter).at(7)))
							 	<< separate(data,delimiter).at(2) << "-" << display_month(stoi(separate(data,delimiter).at(3))) << "-" << separate(data,delimiter).at(4) << "  \t";
							cout<< "Morning" << endl;
						}
						else{ //afternoon
							
							cout<< left << "[" 
							 	<< setw(2) << total+1 << "] "
							 	<< setw(15) << display_city(stoi(separate(data,delimiter).at(7)))
							 	<< separate(data,delimiter).at(2) << "-" << display_month(stoi(separate(data,delimiter).at(3))) << "-" << separate(data,delimiter).at(4) << "  \t";
							cout<< "Afternoon" << endl;
							
						}
						
						total++;
						
					}
				}
			}
			readFile.close();
			cout << "-------------------------------------------------" << endl;
			cout << "Total Flying Doctor Schedule : " << total << endl << endl;
			system("PAUSE");
			
			break;
		}
		case 4:{ //Your Consultation & Visitation Count
			
			system("CLS");
			cout << "-------------------------------------------------" << endl;
			cout << "      Your Consultation & Visitation Count       " << endl;
			cout << "-------------------------------------------------" << endl;
			
			int total=0;
			readFile.open("../data/appointment.txt");
			while(getline(readFile,data)){
				
				//same userID as ms_ID
				if(separate(data,delimiter).at(9)==this->userID){
					total++;
				}
				
			}
			readFile.close();
			cout << "Total Consultation : "<< total << endl;
			
			vector<string> temp; total=0;
			
			readFile.open("../data/visitation_medical_staff.txt");
			while(getline(readFile,data)){
				
				temp = separate(data,delimiter);
				
				//v_id,docID,msID_1,msID_2,msID_3,...,n
				for(int i=1; i<temp.size(); i++){
					
					if(temp.at(i)==this->userID){
						total++;
						break;
					}
				}
			}
			readFile.close();
			cout << "Total Visitation   : "<< total << endl << endl;
			system("PAUSE");
			break;
		}
		default:{
			break;
		}
	}
	goto start_summary;
	
	
	
}

