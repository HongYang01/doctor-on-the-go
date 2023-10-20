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
#include "user.h"

using namespace std;

user::user(){
	userID=userPwd=userName=userPhone=userEmail=userStreet="none";
	userAge=userRace=userCity=-1;
	userVerify=0;//not verified
}

user::~user(){
	
}

void user::userSignup(){
	
	system("CLS");
	
	this->userVerify=0; //not verify
	
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	display_role(-1);
	cout << "Role   [0]Back : ";	cin >> this->userRole;
	
	if(this->userRole==0) return;
	
	this->userRole++; //without admin in the list
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "IC          : ";	getline(cin >> ws, this->userID);
	
	if(this->userID.length()!=12){
		system("CLS"); cout << ">>> Wrong IC format"; sleep(2);
		return;
	}
	
	ifstream readFile;
	string data, filename="../data/userData.txt";
	readFile.open(filename);
	//verification,role,IC,name,age,gender,race,street,city,phone,email,password
	while(getline(readFile,data)){
		
		if(separate(data,",").at(2) == this->userID){
			system("CLS"); cout << ">>> Duplicate User Found"; sleep(2);
			return;
		}
	}
	readFile.close();
	
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Name        : ";	getline(cin >> ws, this->userName);
	
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Age         : "; cin >> this->userAge;
	
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "-------------------------------------------------" << endl;
	display_gender(0);
	cout << "Gender      : "; cin >> this->userGender;
	
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "Gender      : " << display_gender(this->userGender) << endl;
	cout << "-------------------------------------------------" << endl;
	display_race(0);
	cout << "Race        : ";	cin >> this->userRace;
	
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "Gender      : " << display_gender(this->userGender) << endl;
	cout << "Race        : " << display_race(this->userRace) << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Street Name : ";	getline(cin >> ws, this->userStreet);
	
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "Gender      : " << display_gender(this->userGender) << endl;
	cout << "Race        : " << display_race(this->userRace) << endl;
	cout << "Address     : " << this->userStreet << endl;
	cout << "-------------------------------------------------" << endl;
	display_city(0);
	cout << "City        : "; cin >> this->userCity;


	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "Gender      : " << display_gender(this->userGender) << endl;
	cout << "Race        : " << display_race(this->userRace) << endl;
	cout << "Address     : " << this->userStreet << ", " << display_city(this->userCity) << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Phone       : "; getline(cin >> ws, this->userPhone);


	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "Gender      : " << display_gender(this->userGender) << endl;
	cout << "Race        : " << display_race(this->userRace) << endl;
	cout << "Address     : " << this->userStreet << ", " << display_city(this->userCity) << endl;
	cout << "Phone       : " << this->userPhone << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Email       : "; getline(cin >> ws, this->userEmail);

	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "Gender      : " << display_gender(this->userGender) << endl;
	cout << "Race        : " << display_race(this->userRace) << endl;
	cout << "Address     : " << this->userStreet << ", " << display_city(this->userCity) << endl;
	cout << "Phone       : " << this->userPhone << endl;
	cout << "Email       : " << this->userEmail << endl;
	cout << "-------------------------------------------------" << endl;	
	//for medical staff only
	//choose hospital
	vector<vector<string>> tempFac2D;
	string delimiter=",";
	int fac;
	
	if(this->userRole>=3 && this->userRole<=6){
		
		ifstream readFile;
		string filename="../data/hospital.txt";
		readFile.open(filename);
		
		if(readFile.fail()){
			system("CLS"); cout << ">>> File not found: " << filename; sleep(2); return;
		}
		else if(file_is_empty(readFile)){
			system("CLS"); cout << ">>> File is empty"; sleep(2); return;
		}
		else{
			cout << "-------------------------------------------------" << endl;
			cout << "               Associated Hospital               " << endl;
			cout << "-------------------------------------------------" << endl;
			cout << left
				 << "No.  "
				 << setw(5) << "ID"
				 << setw(25) << "Name"
				 << "City"
				 << endl;
			
			//hos_id,hos_name,hos_street,hos_city,hos_phone
			int i=1;
			while(getline(readFile,data,'\n')){
				
				tempFac2D.push_back(separate(data,delimiter));
				
				cout << left << "[" 
					 << setw(2) << i++ << "] "
					 << setw(5) << separate(data,delimiter).at(0)
					 << setw(25) << separate(data,delimiter).at(1)
					 << display_city(stoi(separate(data,delimiter).at(3))) << endl;
			}
			
		}
		cout << "-------------------------------------------------" << endl;
		cout << "Choose associated hospital : "; cin >> fac;
		
	}
	
	create_pwd:
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                     Signup                      " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "Gender      : " << display_gender(this->userGender) << endl;
	cout << "Race        : " << display_race(this->userRace) << endl;
	cout << "Address     : " << this->userStreet << ", " << display_city(this->userCity) << endl;
	cout << "Phone       : " << this->userPhone << endl;
	cout << "Email       : " << this->userEmail << endl;
	
	if(this->userRole>=3 && this->userRole<=6){
		cout << "-------------------------------------------------" << endl;
		cout << "                 Hospital Detail                 " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "ID          : " << tempFac2D[fac-1][0] << endl;
		cout << "Name        : " << tempFac2D[fac-1][1] << endl;
		cout << "Address     : " << tempFac2D[fac-1][2] << "," << display_city(stoi(tempFac2D[fac-1][3])) << endl;
		cout << "Phone       : " << tempFac2D[fac-1][4] << endl;
	}
	
	string tempStr1="", tempStr2="";
	cout << "-------------------------------------------------" << endl;
	cout << "                 Create Password                 " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "NEW Password     : "; getline(cin >> ws, tempStr1);
	cout << "Confirm Password : "; getline(cin >> ws, tempStr2);
	
	if(tempStr1!=tempStr2){
		cout << "\n>>> Password does not match"; sleep(2);
		goto create_pwd;
	}
	else{
		this->userPwd=tempStr1;
		
		ofstream writeFile;
		string filename = "../data/userData.txt";
		writeFile.open(filename,ios_base::app);
		
		if(!writeFile.is_open()){
			system("CLS"); cout << ">>> Failed to register user"; sleep(2); return;
		}
		
		writeFile 	<< endl
					<< this->userVerify << ","
					<< this->userRole << ","
					<< this->userID << ","
					<< this->userName << ","
					<< this->userAge << ","
					<< this->userGender << ","
					<< this->userRace << ","
					<< this->userStreet << ","
					<< this->userCity << ","
					<< this->userPhone << ","
					<< this->userEmail << ","
					<< this->userPwd;
		
		writeFile.close();
		
		
		vector<vector<string>> tempMSHos;
		
		if(this->userRole>=3 && this->userRole<=6){
			
			readFile.open("../data/medical_staff_hospital.txt");
			while(getline(readFile,data)){
				
				tempMSHos.push_back(separate(data,","));
				
			}
			readFile.close();
			
			writeFile.open("../data/medical_staff_hospital.txt");
			
			for(vector<string> temp : tempMSHos){ //rewrite everything
				
				writeFile << join(temp,",") << endl;
				
			}
			//ms_id,ms_type,hos_id (add new data in)
			writeFile << this->userID << "," << this->userRole << "," << tempFac2D[fac-1][0];
			
			writeFile.close();
			
		}
			
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "           Account is under verification         " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Try logging in later...\n";
		system("PAUSE");
	}
		
}

int user::choose_role(){
	
	int nav;
	
	system("CLS");
	cout << "-------------------------------------------------" << endl;
	cout << "                   Choose Role                   " << endl;
	cout << "-------------------------------------------------" << endl;
	display_role(0);
	cout << "Choose [0]Back : ";	cin >> nav;
	
return nav;
}

bool user::verify_credential(int role, string ID, string PWD){
	
	//get role, ID and password
	//check in file
	
	ifstream readFile;
	string filename="../data/userData.txt";
	readFile.open(filename);
	
	if(readFile.fail()){
		cout << ">>> File not found: " << filename << endl; sleep(2); return false;
	}
	else if(file_is_empty(readFile)){ //empty
		
		system("CLS"); cout << "File is empty"; sleep(2); return false;
	}
	else{
		system("CLS");	
		
		vector<string> line;
		string data;
		string delimiter= ",";
		size_t pos = 0;
		while(getline(readFile,data,'\n')){
			
			pos = 0;
			
			while ((pos = data.find(delimiter)) != string::npos) { //put data into vector using delimeter
				
				line.push_back(data.substr(0, pos));
				data.erase(0, pos + delimiter.length());
				
		    }
			line.push_back(data.substr(0, pos)); //the last data from the line
			
			//verification,role(1),IC(2),name,age,gender,race,street,city,phone,email,password
			if(stoi(line.at(1))==role && stoi(line.at(0))==1 && line.at(2)==ID && line.at(11)==PWD){
				
				this->userVerify = stoi(line.at(0));
				this->userRole = stoi(line.at(1));
				this->userID = line.at(2);
				this->userName = line.at(3);
				this->userAge = stoi(line.at(4));
				this->userGender = stoi(line.at(5));
				this->userRace = stoi(line.at(6));
				this->userStreet = line.at(7);
				this->userCity = stoi(line.at(8));
				this->userPhone = line.at(9);
				this->userEmail = line.at(10);
				this->userPwd = line.at(11);
				cout << ">>> Login Successfully"; sleep(2); return true;
			}
			else if(stoi(line.at(1))==role && stoi(line.at(0))==0 && line.at(2)==ID && line.at(11)==PWD){
				cout << ">>> Your account is under verification"; sleep(2); return false;
			}
			data.clear();
			line.clear();
		}
		readFile.close();
		cout << ">>> Wrong credentials..."; sleep(2); return false; 
	}
return false;
}

void user::my_profile(){
	
	system("CLS");	
	cout << "-------------------------------------------------" << endl;
	cout << "                   User Profile                  " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Role        : " << display_role(this->userRole) << endl;
	cout << "IC          : " << this->userID << endl;
	cout << "Name        : " << this->userName << endl;
	cout << "Age         : " << this->userAge << endl;
	cout << "Gender      : " << display_gender(this->userGender) << endl;
	cout << "Race        : " << display_race(this->userRace) << endl;
	cout << "Address     : " << this->userStreet << ", " << display_city(this->userCity) << endl;
	cout << "Phone       : " << this->userPhone << endl;
	cout << "Email       : " << this->userEmail << endl;
	cout << "-------------------------------------------------" << endl;

}

bool user::search_user(string ID){
	
	ifstream readFile;
	string data, delimiter=",", filename="../data/userData.txt";
	readFile.open(filename);
	
	vector<string> temp;
	
	if(readFile.fail()){
		system("CLS"); cout << "File not found: " << filename; sleep(2); return false;
	}
	
	//verification,role,IC,name,age,gender,race,street,city,phone,email,password
	while(getline(readFile,data)){
		
		temp = separate(data,delimiter);
		
		if(temp.at(2) == ID){
			this->userVerify = stoi(temp.at(0));
			this->userRole = stoi(temp.at(1));
			this->userID = temp.at(2);
			this->userName = temp.at(3);
			this->userAge = stoi(temp.at(4));
			this->userGender = stoi(temp.at(5));
			this->userRace = stoi(temp.at(6));
			this->userStreet = temp.at(7);
			this->userCity = stoi(temp.at(8));
			this->userPhone = temp.at(9);
			this->userEmail = temp.at(10);
			this->userPwd = temp.at(11);
			readFile.close();
			return true;
		}
	}
	readFile.close();

return false;
}

int user::get_userRole(){
	return this->userRole;
}

string user::get_userID(){
	return this->userID;
}

string user::get_userName(){
	return this->userName;
}

int user::get_userAge(){
	return this->userAge;
}

int user::get_userGender(){
	return this->userGender;
}

int user::get_userRace(){
	return this->userRace;
}

string user::get_userStreet(){
	return this->userStreet;
}

int user::get_userCity(){
	return this->userCity;	
}

string user::get_userPhone(){
	return this->userPhone;
}
