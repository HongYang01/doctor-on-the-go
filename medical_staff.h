/*
	Implemedted by: Ee Chee Fat (79260)
*/

#ifndef MEDICAL_STAFF_H
#define MEDICAL_STAFF_H

#include <string>
#include "user.h"
#include "hospital.h"
#include "visitation.h"
#include "appointment.h"

using namespace std;

class medical_staff : public user
{
	protected:
		hospital hos;
		string ms_hosID;
		
		appointment app5;
		visitation v2;
		
	public:
		medical_staff();
		~medical_staff();
		
		bool login(int);
		void view_upcoming_schedule();
};

#endif
