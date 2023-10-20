/*
	Implemedted by: Annastasha Chang See May (78855)
*/

#include <iostream>
#include <Windows.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
//#include <conio.h>
//#include <cstdlib>
//#include <iomanip>

#include "display.h"
#include "admin.h"
#include "patient.h"
#include "doctor.h"
#include "nurse.h"
#include "medical_assistant.h"
#include "specialist.h"
#include "appointment.h"
#include "hospital.h"

using namespace std;

user u;
admin ad;
patient p;
doctor doc;
nurse n;
medical_assistant ma;
specialist sp;
appointment app;

int main(int argc, char** argv) {
	
	start:
		
	if(app.check_appointment_expired()==true){
		
		int getRole=-1;
		
		switch(display_welcome()){
			case 1:{ //Login
			
				switch(u.choose_role()){
					case 0:{
						break;
					}
					case 1:{ //ADMIN
						if(ad.login()==true) ad.main_menu();
						break;
					}
					case 2:{ //PATIENT
						if(p.login()==true) p.main_menu();
						break;
					}
					case 3:{ //DOCTOR
						if(doc.login(3)==true) doc.main_menu();
						break;
					}
					case 4:{ //NURSE
						if(n.login(4)==true) n.main_menu();
						break;
					}
					case 5:{ //MEDICAL ASSISTANT
						if(ma.login(5)==true) ma.main_menu();
						break;
					}
					case 6:{ //SPECIALIST
						if(sp.login(6)==true) sp.main_menu();
						break;
					}
					default:{
						break;
					}
				}
				break;
			}
			case 2:{//signup
				u.userSignup();
				break;
			}
			default:{
				break;
			}
		}
		goto start;
	}
	else{
		system("CLS"); cout << ">>> Fail to fetch data"; sleep(2);
	}
	
	return 0;
}
