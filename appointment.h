/*
	Implemedted by: Lim Hong Yang (79880)
*/

#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "user.h"
#include "hospital.h"
#include "transportation.h"
#include <string>

using namespace std;

class appointment
{
	protected:
		string app_id; //datetime created
		int app_method, app_day, app_month, app_year, app_time, app_priority;
		int app_status; //1=pending, 2=approved, 3=rejected
		
		string ms_ID="0"; // default 0 for add new appointment purpose
		user u2;
		transportation trans;
		hospital hos7;
		
	public:
		appointment();
		~appointment();
		
		//ALL USER
			//create appointment ID based on current datetime (unique)
			string create_id();
			//check if appointment clashes
			bool appointment_clash(vector<string>);
			//serach appointment based on patientID & app_status
			vector<vector<string>> search_appointment(string,int);
			//search appointment based on app_id
			vector<string> search_appointment(string ID);
			//get the symptom/treatment based on app_id
			vector<string> associated_symptom(string);
			//preview appointment based on app detail & role
			void preview_appointment(vector<string>,int);
			//view full appointment detail
			void fullview_appointment(vector<string>);
			//save appointment
			void save_appointment(string,vector<string>);
			//check if any appointment expired
			bool check_appointment_expired();
			
		
		//PATIENT
			//add appointment based on patient ID
			void add_appointment(string);
			//return chosen symptom
			vector<string> add_symptom();
			//edit pending appointment only
			void edit_appointment(string);
			//modify associated symptom/treatment (cannot be none)
			void modify_symptom(vector<string>);
			//remove only pending appointment
			void cancel_appointment();
		
};

#endif
