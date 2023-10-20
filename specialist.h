/*
	Implemedted by: Chai Cheng Kang (79027)
*/

#ifndef SPECIALIST_H
#define SPECIALIST_H

#include "medical_assistant.h"

using namespace std;

class specialist : public medical_assistant
{
	public:
		specialist();
		~specialist();
		
		void main_menu();
};

#endif
