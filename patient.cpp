#include <iostream>
#include <Windows.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
//#include <conio.h>
//#include <cstdlib>

#include "display.h"
#include "patient.h"

patient::patient(){
}

patient::~patient(){
}

bool patient::login(){
	
	string inputID, inputPWD;
	int role=2;
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                      Login                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role     : " << display_role(2) <<  endl;
	cout << "ID       : "; getline (cin >> ws, inputID); 
	cout << "Password : "; getline (cin >> ws, inputPWD);
	
	if(verify_credential(role, inputID, inputPWD)==true){
		return true;//Logged in
	}
	
return false;
}

void patient::main_menu(){
	
	int nav;
	
	start_patient:
		
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                Patient Main Menu                " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "[1] Manage Appointment\n"; //view & add & update & cancle
	cout << "[2] Update Health Condition\n";
	cout << "[3] My Profile\n";
	
	cout << "\nChoose [0]Logout: "; cin >> nav;
	
	switch(nav){
		case 0:{
			system("CLS");
			cout << "Confirm to logout? [0]No [1]Yes: ";
			cin >> nav;
			if(nav==1) return;
			break;
		}
		case 1:{
			manage_appointment(); 
			break;
		}
		case 2:{
			update_health_condition();
			break;
		}
		case 3:{
			my_profile();
			view_health_condition();
			system("PAUSE");
			break;
		}
		default:{
			break;
		}
	}
	goto start_patient;
}

void patient::manage_appointment(){
	
	int nav;
	
	start_manage_appoinment:
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                Manage Appointment               " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "[1] Add New Appointment\n";
	cout << "[2] Edit Appointment\n";	//only pending appointment
	cout << "[3] View Appoinment\n";
	cout << "\nChoose [0]Back : ";
	cin >> nav;
	
	switch(nav){
		case 0:{
			return;
		}
		case 1:{ //add new appointment
			app2.add_appointment(this->userID);
			break;
		}
		case 2:{ //edit appointment
			app2.edit_appointment(this->userID);
			break;
		}
		case 3:{ //view appointment
				
				start_view:
				int i, nav;
				
				system("CLS");
				cout << "-------------------------------------------------" << endl;
				cout << "                 View Appointment                " << endl;
				cout << "-------------------------------------------------" << endl;
				display_appointment_status(0);
				cout << "Choose [0]Back : "; cin >> nav;
					
				if(nav==0){
					return;
				}
				else if(nav<0|| nav>4){
					goto start_view;
				}
					
				vector<vector<string>> vec2D = app2.search_appointment(this->userID,nav);
				
				if(vec2D.size()==0){
					system("CLS"); cout << ">>> No appointment found"; sleep(2); goto start_view;
				}
				else{
					
					start_preview:
						
					system("CLS");
					cout << "-------------------------------------------------" << endl;
					cout << "               Appointment Preview               " << endl;
					cout << "-------------------------------------------------" << endl;
					
					cout << left << "No. " << setw(20) << "ID" << setw(20) << "Method" << setw(20) << "Date" << "Time" << endl;
					
					i=1;
					for(vector<string> tempVec : vec2D){
						cout << "[" << i++ << "] ";
						app2.preview_appointment(tempVec,this->userRole);
						
					}
					
					
					cout << "-------------------------------------------------" << endl;
					cout << "Choose to see full detail [0]Back : ";
					cin >> nav;
					
					if(nav==0){
						goto start_view;
					}
					else if(nav<0 || nav>vec2D.size()){
						goto start_preview;
					}
					
					i=0;
					for(vector<string> tempVec : vec2D){
						
						if(i++==nav-1){
							system("CLS");
							app2.fullview_appointment(tempVec);
						}
					}
					cout << "-------------------------------------------------" << endl;
				}
				
				system("PAUSE");
			
			goto start_preview;
		}
		default:{
			break;
		}
	}
	goto start_manage_appoinment;
	
}

void patient::update_health_condition(){
	
	int choose, reserved_data=1; //1=userID
	vector<string> tempHC;
	bool done, dup;
	
	string data,delimiter=",",filename;
	ifstream readFile;
	ofstream writeFile;
	
	
	filename="../data/patient_health_condition.txt";
	readFile.open(filename);
	//patient_id,hc1,hc2,hc3,...,n
	while(getline(readFile,data)){
		
		if(separate(data,delimiter).at(0)==this->userID){
			
			tempHC = separate(data,delimiter);
			break;
		}
		
	}	
	readFile.close();
	
	if(tempHC.size()==0) tempHC.push_back(this->userID);
	
	
	do{
		done=dup=false;
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "             Update Health Condition             " << endl;
		cout << "-------------------------------------------------" << endl;
		
		if(tempHC.size()>reserved_data){
			for(int i=reserved_data; i<tempHC.size(); i++){
				cout << left << "["
					 << setw(2) << i << "] " << display_hc_type(stoi(tempHC.at(i))) << endl; 
			}
			cout << "-------------------------------------------------" << endl;
		}
		
		display_hc_type(0);
		
		if(tempHC.size()>reserved_data){
			cout << "\nTo remove any health condition use negative value [-n]remove";
			cout << "\nChoose [0]Done : ";
		}
		else{
			cout << "\nChoose [0]Back : ";
		}
		
		cin >> choose;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
		if(choose==0 && tempHC.size()==reserved_data){
			return;
		}
		else if(choose==0 && tempHC.size()>reserved_data){
			done=true;
		}
		else if(choose>0 && choose<=5){ //good attempt
			
			for(int i=reserved_data; i<tempHC.size(); i++){
				if(choose==stoi(tempHC.at(i))){ //duplication
					dup=true; break;
				}
			}
				
			if(dup==false) tempHC.push_back(to_string(choose)); //unique
			
		}
		else if(choose<0 && (abs(choose)-1)<=tempHC.size()-reserved_data && tempHC.size()>reserved_data){ //removing hc
			
			tempHC.erase(tempHC.begin() + abs(choose)-1+reserved_data); //using negative value to remove hc
						
		}
		else if(choose<0 && abs(choose)>tempHC.size()-reserved_data){ //removing hc that is not in the list
			system("CLS"); cout << ">>> Nothing to remove at " << choose; sleep(2);
		}
		else{
			system("CLS"); cout << ">>> Nothing found : " << choose; sleep(2);
		}
		
	}while(done==false);
	
	//save data
	
	vector<vector<string>> tempHC2D;
	
	readFile.open(filename);
	while(getline(readFile,data)){
		
		tempHC2D.push_back(separate(data,delimiter));
		
	}
	readFile.close();
	
	
	done=false;
	for(int i=0; i<tempHC2D.size(); i++){
		
		if(tempHC2D[i][0]==tempHC.at(0)){ // match userID
		
			tempHC2D[i] = tempHC;
			done=true; break;
		}
		
	}
	
	if(done==false) tempHC2D.push_back(tempHC);
	
	
	int i=0;
	writeFile.open(filename);
	for(vector<string> temp : tempHC2D){
		
		writeFile << join(temp,delimiter) << (i++<tempHC2D.size()-1 ? "\n" : "");
		
	}
	readFile.close();
	
	system("CLS"); cout << ">>> Changes are updated successfully"; sleep(2);
	
}

void patient::view_health_condition(){
	
	string data,delimiter=",",filename;
	ifstream readFile;
	int reserved_data=1; //1=patient_ID
	
	vector<string> tempHC;
	
	filename="../data/patient_health_condition.txt";
	readFile.open(filename);
	//patient_id,hc1,hc2,hc3,...,n
	while(getline(readFile,data)){
		
		if(separate(data,delimiter).at(0)==this->userID){
			
			tempHC = separate(data,delimiter);
			break;
		}
		
	}	
	readFile.close();
	
	
	if(tempHC.size()>reserved_data){
		cout << "-------------------------------------------------" << endl;
		cout << "                 Health Condition                " << endl;
		cout << "-------------------------------------------------" << endl;
		for(int i=reserved_data; i<tempHC.size(); i++){
			cout << left << "["
				 << setw(2) << i << "] " << display_hc_type(stoi(tempHC.at(i))) << endl; 
		}
		cout << "-------------------------------------------------" << endl;
	}
	
}


