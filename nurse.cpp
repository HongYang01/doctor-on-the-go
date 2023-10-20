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

#include "nurse.h"


nurse::nurse()
{
}

nurse::~nurse()
{
}

void nurse::main_menu(){
	
	int nav;
	
	start_nurse:
	
	do{
		system("CLS");
		cout << "-------------------------------------------------" << endl;
		cout << "                 Nurse Main Menu                 " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "[1] View Upcoming Schedule" << endl;
		cout << "[2] My Profile" << endl;
		cout << "\nChoose [0]Logout : "; cin >> nav;
		cin.clear(); cin.ignore(INT_MAX,'\n');
		
	}while(nav<0 || nav>2);
	
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
			my_profile();
			system("PAUSE");
			break;
		}
		default:{
			break;
		}
	}
	goto start_nurse;
	
}












