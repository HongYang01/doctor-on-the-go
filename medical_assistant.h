/*
	Implemedted by: Chai Cheng Kang (79027)
*/

#ifndef MEDICAL_ASSISTANT_H
#define MEDICAL_ASSISTANT_H

#include "medical_staff.h"

using namespace std;

class medical_assistant : public medical_staff
{
	public:
		medical_assistant();
		~medical_assistant();
		
		void main_menu();
};

#endif
