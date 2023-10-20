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
#include "transportation.h"

transportation::transportation()
{
}

transportation::~transportation()
{
}

bool transportation::search_transportation(string ID){
	
	//find based on treans_id
	//trans_id,hos_ID,trans_type
	
	string data, delimiter=",", filename="../data/transportation.txt";
	ifstream readFile;
	readFile.open(filename);
	
	if(readFile.fail()){
		system("CLS"); cout << ">>> File not found: " << filename << endl; sleep(2); return false;
	}
	else{
		while(getline(readFile,data)){
			
			if(separate(data,delimiter).at(0) == ID){ //match transportation ID
			
				this->trans_id = separate(data,delimiter).at(0);
				this->trans_hos_ID = separate(data,delimiter).at(1);
				this->trans_type = stoi(separate(data,delimiter).at(2));
				
				readFile.close();
				return true;
			}
			
		}
		readFile.close();
		system("CLS"); cout << ">>> Transportation ID Not Found: " << ID; sleep(2); 
	}
	return false;
	
}

vector<vector<string>> transportation::search_transportation(string ID, int type){
	
	//get trans detail based on hos_id and transport type
	
	//Type
		//1=bus
		//2=boat
		//3=aircraft (flying doctor only)
		
	//trans_id,hos_ID,trans_type
	
	vector<vector<string>> temp2D;
	
	string data, delimiter=",", filename="../data/transportation.txt";
	ifstream readFile;
	
	readFile.open(filename);
	if(readFile.fail()){
		system("CLS"); cout << ">>> File not found: " << filename << endl; sleep(2); return temp2D;
	}
	else{

		while(getline(readFile,data)){
				
			if(separate(data,delimiter).at(1) == ID && stoi(separate(data,delimiter).at(2)) == type){ //same hos id & type
				temp2D.push_back(separate(data,delimiter));
			}
		}
	}
	readFile.close();
	
	if(temp2D.size()==0){
		system("CLS"); cout << ">>> No Transportation found"; sleep(2);
	}
	return temp2D;
	
}

void transportation::fullview_trans_detail(vector<string> temp){
	
	//get trans detail
	//trans_id,hos_ID,trans_type
	
	cout << "-------------------------------------------------" << endl;
	cout << "               Transportation Detail             " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ID      : " << temp.at(0) << endl;
	cout << "Type    : " << display_trans(stoi(temp.at(2))) << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "          Transportation Located Hospital        " << endl;
	cout << "-------------------------------------------------" << endl;
	hos4.search_hospital(temp.at(1)); //search by hos_id
	
	cout << "ID      : " << hos4.get_hosID() << endl;
	cout << "Name    : " << hos4.get_hosName() << endl;
	cout << "Address : " << hos4.get_hosStreet() << ", " << display_city(hos4.get_hosCity()) << endl;
	cout << "Phone   : " << hos4.get_hosPhone() << endl;
	cout << "-------------------------------------------------" << endl;
	
}

bool transportation::trans_schedule_clash(string ID,int day,int month,int year){
	
	vector<string> temp;
	
	string data,delimiter=",";
	ifstream readFile;
	readFile.open("../data/visitation.txt");
	//v_id,v_type,v_day,v_month,v_year,v_time,v_street,v_city,v_trans_id
	while(getline(readFile,data)){
		
		temp = separate(data,delimiter);
		
		if(temp.at(8) == ID && date_smaller_than_today(stoi(temp.at(2)),stoi(temp.at(3)),stoi(temp.at(4)))==false){ //check trans_id & date
			
			if(stoi(temp.at(1))==1){ //ONE-TIME
				if(stoi(temp.at(2))==day && stoi(temp.at(3))==month && stoi(temp.at(4))==year){
					return true;
				}
			}
			else{ //ROUTINE
				if(stoi(temp.at(2))==day){
					return true;
				}
			}
			
		}
		
	}
	temp.clear();
	readFile.close();
	
	return false;
	
}

int transportation::get_transType(){
	return this->trans_type;
}




