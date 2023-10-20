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

#include "medical_staff.h"
#include "display.h"


medical_staff::medical_staff()
{
}

medical_staff::~medical_staff()
{
}

bool medical_staff::login(int role){
	
	string inputID, inputPWD;
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                      Login                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role     : " << display_role(role) << endl;
	cout << "ID       : "; getline (cin >> ws, inputID); 
	cout << "Password : "; getline (cin >> ws, inputPWD);
	
	if(verify_credential(role, inputID, inputPWD)==true){
		
		if(hos.get_medical_staff_hos(inputID) == false){

			return false;
		}
		
		return true;//Logged in
	}
	else{
		return false;
	}
}

void medical_staff::view_upcoming_schedule(){
	
	//get this->userID
	//check in appointment & visitation
	//sort by date (LAZY)
	
	int doctorRole=3;
	
	string data,delimiter=",",filename;
	ifstream readFile;
	
	vector<vector<string>> tempAppList, tempVisitList;
	
	
	//app_ID,patient_IC,app_method,day(3),month,year,time,priority,app_status,ms_ID
	//v_id,v_type,v_day(2),v_month,v_year,v_time,v_street,v_city,v_trans_id
	
	
	if(this->userRole==doctorRole){ //DOCTOR
		
		filename="../data/appointment.txt";
		readFile.open(filename);
		while(getline(readFile,data)){
			
			//app_status=approve
			//priority is not emergency
			//date is larger than today
			//same userID as ms_ID
			if(	stoi(separate(data,delimiter).at(8))==2 &&
				stoi(separate(data,delimiter).at(7))!=4 &&
				date_smaller_than_today(stoi(separate(data,delimiter).at(3)),stoi(separate(data,delimiter).at(4)),stoi(separate(data,delimiter).at(5)))==false &&
				separate(data,delimiter).at(9)==this->userID){
				
				tempAppList.push_back(separate(data,delimiter)); //get appointment detail

			}
			
		}
		readFile.close();
		
	}
		
	vector<string> tempV1D, temp;
	
	filename="../data/visitation_medical_staff.txt";
	readFile.open(filename);
	//v_id,docID,msID_1,msID_2,msID_3,...,n
	while(getline(readFile,data)){
		
		temp = separate(data,delimiter);
		
		for(int i=1; i<temp.size(); i++){ //seeking for same msID (i=1 becuase skip v_id)
			
			if(temp.at(i)==this->userID){ //if same msID
				
				tempV1D.push_back(temp.at(0)); //get the v_id
				
			}
		}
	}
	readFile.close();
	
	
	filename="../data/visitation.txt";
	readFile.open(filename);
	//v_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	while(getline(readFile,data)){
		
		for(int i=0; i<tempV1D.size(); i++){
			
			if(separate(data,delimiter).at(0)==tempV1D.at(i)){ //same v_id
				
				tempVisitList.push_back(separate(data,delimiter)); //get visitation detail
			}
		}
	}
	readFile.close();
	
	
	if(tempAppList.size()==0 && tempVisitList.size()==0){
		system("CLS"); cout << ">>> No upcoming schedule"; sleep(2);
		return;
	}
	
	
	int nav, count, choose;
	
	do{
		count=1;
		system("CLS");
		cout << "------------------------------------------------------------------------" << endl;
		cout << "                           Upcoming Schedule                            " << endl;
		if(tempAppList.size()>0){
			
			cout << "========================================================================" << endl;
			cout << ">>> Appointment\n\n";
			cout << left << "No. " << setw(20) << "Name" << setw(20) << "Method" << setw(20) << "Date" << "Time" << endl;
			cout << "========================================================================" << endl;
			
			for(vector<string> temp : tempAppList){
				
				cout << "[" << count++ << "] ";
				
				app5.preview_appointment(temp,this->userRole);
				
			}
		}
		
		if(tempVisitList.size()>0){
			cout << endl;
			cout << "========================================================================" << endl;
			cout << ">>> Visitation\n\n";
			cout << left << "No.  " << setw(10) << "Type" << setw(17) << "Date" << setw(15) << "City" << "Transport ID" << endl;
			cout << "========================================================================" << endl;
			
			for(vector<string> temp : tempVisitList){
				
				cout << left << "[" 
					 << setw(2) << count++ << "] ";
				
				v2.preview_visitation(temp);
				
			}
		}
		
		cout << "------------------------------------------------------------------------" << endl;
		cout << "\nChoose [0]Back : "; cin >> choose;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
		
		if(choose==0){
			return;
		}
		else if(this->userRole==doctorRole && choose>0 && choose<=tempAppList.size()){ //selected appointment list (Doctor only)
			//view appointment detail
			system("CLS"); app5.fullview_appointment(tempAppList[choose-1]);
		}
		else if(this->userRole==doctorRole && choose>tempAppList.size() && choose<=tempAppList.size()+tempVisitList.size()){ //selected visitation list
			//view visitation detail
			system("CLS"); v2.fullview_visitation(tempVisitList[(choose - tempAppList.size())-1]);
			
			vector<string> tempMS;
			
			readFile.open("../data/visitation_medical_staff.txt");
			// v_id,docID,msID_1,msID_2,msID_3,...,n
			while(getline(readFile,data)){
				
				if(separate(data,",").at(0) == tempVisitList[(choose - tempAppList.size())-1][0]){ //match v_id
					tempMS = separate(data,delimiter);
				}		
				
			}
			readFile.close();
			
			cout << "-------------------------------------------------" << endl;
			cout << "              Assign Medical Staff               " << endl;
			cout << "-------------------------------------------------" << endl;
			count=1;
			readFile.open("../data/userData.txt");
			while(getline(readFile,data)){
				
				for(int k=1; k<tempMS.size(); k++){
					
					if(separate(data,delimiter).at(2)==tempMS.at(k)){
						
						cout << left << "[" 
							 << setw(2) << count++ << "] " 
							 << setw(20) << separate(data,delimiter).at(2)
							 << separate(data,delimiter).at(3) << endl;
					}
				}
			}
		}
		else if(this->userRole!=doctorRole && choose>0 && choose<=tempVisitList.size()){
			//OTHER MEDICAL STAFF view visitation detail
			system("CLS"); v2.fullview_visitation(tempVisitList[choose-1]);
		}
		else{
			choose=-1;
		}
		cout << "\n------------------------------------------------------------------------" << endl;
		system("PAUSE");
		
	}while(choose!=0);
	
}







