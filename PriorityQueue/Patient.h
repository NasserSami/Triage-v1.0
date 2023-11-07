/*
Author: Sam Nasser
Student #: 1139908
Date: Nov 1, 2023

*/

#pragma once
#include "Ailment.h"
#include "LinkedList.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <cctype>

using int_type = Ailment::int_type;


/**
 * @brief Class representing a patient.
 *
 * This class encapsulates data about a patient, including their name and a linked list
 * of ailments they are suffering from. It provides accessor methods to retrieve the
 * patient's name and their list of ailments, as well as a method to add an ailment to the list.
 * The class also includes a method to calculate a patient's priority score for treatment
 * based on the ailments they have.
 *
 * Equality operators are also provided to compare two Patient objects based on their names.
 * The class is designed to be used in medical queue management systems where patients'
 * treatment priorities need to be assessed and managed effectively.
 */
class Patient
{
	std::string name_;
	LinkedList<Ailment> ailments_;

public:

	Patient(std::string n = "") : name_(n) {}

	std::string get_name() const { return name_; }
	LinkedList<Ailment> get_ailments() const { return ailments_;}

	void add_ailment(const Ailment& ailment);
	int_type get_score() const;

	constexpr bool operator==(const Patient& other) const {

		return other.name_ == name_;
		
	}
	
};


