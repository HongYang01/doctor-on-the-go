/*
	Implemedted by: Chin Teck Yung (79065)
*/

#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include "medical_staff.h"

using namespace std;

class doctor : public medical_staff
{
	
	private:
		
		appointment app3;
		transportation trans2;
		visitation v;
		user u4;
		
	public:
		doctor();
		~doctor();
		
		
		//method
		void main_menu();
		void approve_appointment();
		bool add_treatment_medication_plan(string ID);
		void monitor_patient_health_status();
		
		//how many patient in that area
		void view_summary();
		
		
		
};

#endif
