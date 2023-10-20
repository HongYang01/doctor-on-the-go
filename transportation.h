/*
	Implemedted by: Annastasha Chang See May (78855)
*/

#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

#include <string>
#include "hospital.h"

using namespace std;

class transportation
{
	private:
		string trans_id, trans_hos_ID;
		int trans_type;
		
		hospital hos4;
	
	public:
		transportation();
		~transportation();
		
		void add_trans();
		void edit_trans();
		
		bool search_transportation(string); //by id
		vector<vector<string>> search_transportation(string,int); //by hos_id & type
		
		void fullview_trans_detail(vector<string>);
		
		//save transporatation schedule
		bool save_trans_data(string,vector<string>);
		
		//check if transportation clashes
		bool trans_schedule_clash(string ID,int day,int month,int year);
		
		int get_transType();
	
		
};

#endif
