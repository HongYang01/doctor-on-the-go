/*
	Implemedted by: Chin Teck Yung (79065)
*/

#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "hospital.h"

class admin : public user{
	
	user u5;
	hospital hos2;
	
	public:
		admin();
		~admin();
		
		//method
		bool login();
		void main_menu();
		void verify_new_user();
	
};

#endif
