/*
	Implemedted by: Ee Chee Fat (79260)
*/

#ifndef PATIENT_H
#define PATIENT_H

#include "user.h"
#include "appointment.h"

class patient : public user
{
	private:
		
		appointment app2; //patient HAS appointment (aggregation)
		
	public:
		patient();
		~patient();
		
		bool login();
		void main_menu();
		//add,edit,cancel appointment
		void manage_appointment();
		//manage health condition
		void update_health_condition();
		//view health conditition history
		void view_health_condition();
		
		
};

#endif
