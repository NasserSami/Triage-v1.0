/*
Author: Sam Nasser
Student #: 1139908
Date: Nov 1, 2023

*/

#include "Patient.h"


/**
 * @brief Adds an ailment to the patient's list of ailments.
 *
 * This function takes an Ailment object and adds it to the patient's existing list of ailments.
 * It is used to keep track of all the ailments associated with a patient.
 *
 * @param ailment The Ailment object to be added to the patient's list.
 */
void Patient::add_ailment(const Ailment& ailment)
{
	Patient::ailments_.push_back(ailment);
}


/**
 * @brief Calculates the patient's priority score based on their ailments.
 *
 * This function iterates through the patient's list of ailments, calculating a score based on
 * the severity and time sensitivity of each ailment, as well as its contagiousness. The score
 * is intended to be used for prioritizing patients in a priority queue system, with a higher
 * score indicating a higher priority.
 *
 * @return int_type The calculated priority score for the patient.
 */
int_type Patient::get_score() const
{
	int_type score = 0;
	auto* ailment = Patient::get_ailments().begin();
	
	while (ailment != nullptr)
	{
		
		score += (ailment->data.get_severity() 
			* ailment->data.get_time_sensitivity())
			+ ailment->data.get_contagiousness();
		ailment = ailment->next;
	}
	

	return score;
}