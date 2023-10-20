#ifndef HEALTH_STATUS_H
#define HEALTH_STATUS_H

#include <string>
#include <vector>

using namespace std;

class health_status
{
	public:
		string hs_patient_id;
		int hs_day, hs_month, hs_year, hs_blood_pressure, hs_pulse;
		float hs_temperature;
		
		health_status(string hs_patient_id, int hs_day, int hs_month, int hs_year, int hs_blood_pressure,int hs_pulse, float hs_temperature){
			
			this->hs_patient_id = hs_patient_id;
			this->hs_day = hs_day;
			this->hs_month = hs_month;
			this->hs_year = hs_year;
			this->hs_blood_pressure = hs_blood_pressure;
			this->hs_pulse = hs_pulse;
			this->hs_temperature = hs_temperature;
		}
		
};

#endif
