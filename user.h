/*
	Implemedted by: Annastasha Chang See May (78855)
*/

#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;

class user
{
	protected:
		string userID, userPwd, userName, userStreet, userPhone, userEmail;
		int userVerify, userRole, userAge, userRace, userCity, userGender;
		
	public:
		user();
		~user();
		
		//method
		void userSignup();
		//choose user role
		int choose_role();
		//verify credential while login
		bool verify_credential(int,string,string);
		//display user profile
		void my_profile();
		//get user detail using userID
		bool search_user(string);
		
		//getter
		//verification,role,IC,name,age,gender,race,street,city,phone,email,password
		string get_userID();
		int get_userRole();
		string get_userName();
		int get_userAge();
		int get_userGender();
		int get_userRace();
		string get_userStreet();
		int get_userCity();
		string get_userPhone();
};

#endif
