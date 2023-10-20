/*
	Implemedted by: Ee Chee Fat (79260)
*/

#ifndef NURSE_H
#define NURSE_H

#include "medical_staff.h"

using namespace std;

class nurse : public medical_staff
{
	public:
		nurse();
		~nurse();
		
		void main_menu();
		
};

#endif
