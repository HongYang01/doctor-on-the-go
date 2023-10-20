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
#include "admin.h"

using namespace std;

admin::admin(){
}

admin::~admin(){
}

void admin::main_menu(){
	
	int nav;
	
	start_admin:
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                 Admin Main Menu                 " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "[1] Verify New User\n";
	cout << "[2] My Profile\n";
	
	cout << "\nChoose [0]Logout: "; cin >> nav;
	
	switch(nav){
		case 0:{
			system("CLS");
			cout << "Confirm to logout? [0]No [1]Yes: ";
			cin >> nav;
			if(nav==1) return;
			goto start_admin;
		}
		case 1:{
			verify_new_user();
			goto start_admin;
		}
		case 2:{
			my_profile(); system("PAUSE");
			goto start_admin;
		}
		default:{
			goto start_admin;
		}
	}
	
}

void admin::verify_new_user(){

	ifstream readFile;
	string data, delimiter=",";
	
	
start_verify:
	
	bool is_medical_staff=false;
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                 Verify New User                 " << endl;
	cout << "-------------------------------------------------" << endl;
	
	readFile.open("../data/userData.txt");
	
	if(readFile.fail()){
		system("CLS"); cout << ">>> File not found: " << "../data/userData.txt" << endl; sleep(2); return;
	}
	
	vector<vector<string>> temp2D;
	//verification(0),role,IC,name,age,gender,race,street,city,phone,email,password
	while(getline(readFile,data)){
		temp2D.push_back(separate(data,delimiter));
	}
	readFile.close();
	
start_verify2:
	
	int i=1, nav, choose;
	vector<int> which;
	
	do{
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "                 Verify New User                 " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << left
			 << setw(5) << "No."
			 << setw(15) << "IC"
			 << setw(25) << "Name"
			 << "Role" << endl;
		cout << "-------------------------------------------------" << endl;
		
		int count=1;
		i=0;
		for(vector<string> temp : temp2D){
			
			if(temp.at(0) == "0"){ //0=unverify
				cout << left << "[" 
					 << setw(2) << count++ << "] "
				 	 << setw(15) << temp.at(2)
				 	 << setw(25) << temp.at(3)
				 	 << display_role(stoi(temp.at(1))) << endl;
				which.push_back(i); //get the unverify
			}
		i++;	
		}
		
			if(which.size()==0){
				system("CLS"); cout << ">>> No new user"; sleep(2); return;
			}
		
		cout << "\nChoose [0]Back : "; cin >> choose;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
		if(choose==0) return;
		
	}while(choose<0 || choose>temp2D.size());
	
	
	//verification,role,IC,name,age,gender,race,street,city,phone,email,password
	system("CLS");
	if(u5.search_user(temp2D[which.at(choose-1)][2])==true){ //find user based on IC
		u5.my_profile();
	}
	else{
		system("CLS"); cout << ">>> New User not found"; sleep(2); goto start_verify2;
	}

	
	int hosLine=0;
	vector<vector<string>> tempHospital2D;
	
	if(stoi(temp2D[which.at(choose-1)][1])>=3 && stoi(temp2D[which.at(choose-1)][1])<=6){ //MEDICAL STAFF
		
		is_medical_staff=true;
		
		readFile.open("../data/medical_staff_hospital.txt");
		
		while(getline(readFile,data)){
			tempHospital2D.push_back(separate(data,delimiter));
		}
		readFile.close();
		
		// ms_id,ms_type,hos_id
		for(vector<string> temp : tempHospital2D){
			
			if(temp.at(0) == temp2D[which.at(choose-1)][2]){ //same ms_id
				hos2.search_hospital(separate(data,delimiter).at(2));
				hos2.view_hospital_detail();
				break;
			}
			hosLine++;
		}
	}
	
	cout << "-------------------------------------------------" << endl;
	cout << "Choose [0]Back [1]Approve [2]Reject : "; cin >> nav;
	cin.clear(); cin.ignore(INT_MAX,'\n');
	
	if(nav==1){ //APPROVE
		temp2D[which.at(choose-1)][0] = "1";
	}
	else if(nav==2){ //REJECT
		
		temp2D.erase(temp2D.begin() + which.at(choose-1));
		
		//verification,role,IC,name,age,gender,race,street,city,phone,email,password
		if(is_medical_staff==true){ //is medical staff
			tempHospital2D.erase(tempHospital2D.begin() + hosLine);
		}
		
	}
	else{
		goto start_verify2;
	}
	
	ofstream writeFile;
	
	writeFile.open("../data/userData.txt");
	i=0;
	for(vector<string> temp : temp2D){
		writeFile << join(temp,delimiter) << (i++<temp2D.size()-1 ? "\n" : "");
	}
	writeFile.close();
	
	
	if(is_medical_staff==true){
		
		writeFile.open("../data/medical_staff_hospital.txt");
		i=0;
		for(vector<string> temp : tempHospital2D){
			writeFile << join(temp,delimiter) << (i++<tempHospital2D.size()-1 ? "\n" : "");
		}
		writeFile.close();
		
	}
	
	
	if(nav==1){ //APPROVE
		system("CLS"); cout << ">>> user is verified"; sleep(2); goto start_verify;
	}
	else if(nav==2){ //REJECT
		system("CLS"); cout << ">>> User is rejected"; sleep(2); goto start_verify;
	}
	
}

bool admin::login(){
	
	string inputID, inputPWD;
	int role=1;
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                      Login                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role     : " << display_role(1) << endl; 
	cout << "ID       : "; getline (cin >> ws, inputID); 
	cout << "Password : "; getline (cin >> ws, inputPWD);
	
	if(verify_credential(role, inputID, inputPWD)==true){
		return true;//Logged in
	}
	
return false;	
}

