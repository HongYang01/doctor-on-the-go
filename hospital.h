/*
	Implemedted by: Chai Cheng Kang (79027)
*/

#ifndef FACILITY_H
#define FACILITY_H

#include <string>
#include <vector>
using namespace std;


class hospital
{
	private:
		string hos_id, hos_name, hos_street, hos_phone;
		int hos_city;
		
	public:
		
		//get medical staff hospital detail based on msID
		bool get_medical_staff_hos(string);
		
		//view facility detail by object
		void view_hospital_detail();
		
		//search hospital
		bool search_hospital(string);
		vector<vector<string>> search_hospital(int);
		
		
		//getter
		string get_hosID();
		string get_hosName();
		string get_hosStreet();
		int get_hosCity();
		string get_hosPhone();
		
};

#endif
