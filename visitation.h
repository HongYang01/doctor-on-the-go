/*
	Implemedted by: Lim Hong Yang (79880)
*/

#ifndef VISITATION_H
#define VISITATION_H

#include <string>
#include <vector>

#include "user.h"
#include "appointment.h"
#include "transportation.h"

using namespace std;

class visitation
{
	private:
		string v_id, v_street;
		int v_type,v_day,v_month,v_year,v_city, v_time;
		string v_trans_id;
		
		appointment app4;
		user u3;
		transportation trans3;
		hospital hos5, hos6;
		
	public:
		
		visitation();
		~visitation();
		
		void preview_visitation(vector<string>);
		void fullview_visitation(vector<string>);
		
		
		bool add_visitation(string,string,int);
		//assigning ms for visitation
		vector<string> add_ms_to_visitation(string docID, int city, int day, int month, int year);
		//search visitation detail based on v_id
		bool search_visitation(string);
		//save visitation
		void save_visitation(string,vector<string>);
		//check visitation time clash & type of visitation (1=ONE-TIME,2=ROUTINE) & date
		bool visitation_clash(string docID, int type,int day,int month,int year);
		
};

#endif
