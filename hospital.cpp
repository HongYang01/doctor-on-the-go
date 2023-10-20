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
#include "hospital.h"

bool hospital::get_medical_staff_hos(string msID){
	
	bool flag=false;
	
	ifstream readFile;
	string data, delimiter=",", filename = "../data/medical_staff_hospital.txt";
	readFile.open(filename);
	
	string tempHosID="";
	//ms_id,ms_type,hos_id
	while(getline(readFile,data)){
		
		if(separate(data,delimiter).at(0) == msID){ //match msID
			tempHosID = separate(data,delimiter).at(2); //get hos_id
			flag=true;
			break;
		}
	}
	readFile.close();
	
	if(flag==true){
		
		flag=false;
		filename="../data/hospital.txt";
		readFile.open(filename);
		
		//hos_id,hos_name,hos_street,hos_city,hos_phone
		while(getline(readFile,data)){
			
			if(separate(data,delimiter).at(0) == tempHosID){ //found hos_id
				
				this->hos_id = separate(data,delimiter).at(0);
				this->hos_name = separate(data,delimiter).at(1);
				this->hos_street = separate(data,delimiter).at(2);
				this->hos_city = stoi(separate(data,delimiter).at(3));
				this->hos_phone = separate(data,delimiter).at(4);

				readFile.close();
				return true;
			}
		}
		readFile.close();
	}
		
	return false;

}

void hospital::view_hospital_detail(){

	//displaying associated detail
	cout << "-------------------------------------------------" << endl;
	cout << "               Associated Hospital               " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ID          : " << this->hos_id << endl;
	cout << "Name        : " << this->hos_name << endl;
	cout << "Address     : " << this->hos_street << ", " << display_city(this->hos_city) << endl;
	cout << "Phone       : " << this->hos_phone << endl;
	cout << "-------------------------------------------------" << endl;
	
}

bool hospital::search_hospital(string ID){
	
	//get hos_id
	//hos_id,hos_name,hos_street,hos_city,hos_phone
	
	string data, delimiter=",", filename="../data/hospital.txt";
	ifstream readFile;
	readFile.open(filename);
	
	if(readFile.fail()){
		system("CLS"); cout << "File not found: " << filename; sleep(2); return false;
	}
	else{
		
		while(getline(readFile,data)){
			
			if(separate(data,delimiter).at(0) == ID){ //same hos_id
				
				this->hos_id = separate(data,delimiter).at(0);
				this->hos_name = separate(data,delimiter).at(1);
				this->hos_street = separate(data,delimiter).at(2);
				this->hos_city = stoi(separate(data,delimiter).at(3));
				this->hos_phone= separate(data,delimiter).at(4);
				
				readFile.close();
				return true;
			}
			
		}
		
	}
	
return false;	
}

vector<vector<string>> hospital::search_hospital(int city){

	//hos_id,hos_name,hos_street,hos_city,hos_phone
	
	ifstream readFile;
	readFile.open("../data/hospital.txt");
	string data, delimiter=",";
	
	vector<vector<string>> temp2D;

	while(getline(readFile,data)){
		
		if(stoi(separate(data,delimiter).at(3))==city){ //same city
			temp2D.push_back(separate(data,delimiter));
		}
	}
	readFile.close();
	
return temp2D;
}

string hospital::get_hosID(){
	return this->hos_id;
}

string hospital::get_hosName(){
	return this->hos_name;
}

string hospital::get_hosStreet(){
	return this->hos_street;
}

int hospital::get_hosCity(){
	return this->hos_city;	
}

string hospital::get_hosPhone(){
	return this->hos_phone;
}




