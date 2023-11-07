/*
Author: Sam Nasser
Student #: 1139908
Date: Nov 1, 2023

*/
#pragma once

#include <string>

/**
 * @brief Class representing a medical ailment.
 *
 * This class encapsulates data for an ailment, including its name, severity, time sensitivity,
 * and level of contagiousness. It provides accessor methods to retrieve these properties.
 * The severity, time sensitivity, and contagiousness are represented using an integer type
 * that is capable of holding very large values (std::uintmax_t).
 *
 */
class Ailment
{
public:
	using int_type = std::uintmax_t;

private:
	std::string name;
	int_type severity;
	int_type time_sensitivity;
	int_type contagiousness;

public:
	 Ailment(std::string n = "", int_type s = 0, int_type ts = 0, int_type c = 0) :
		name(n),severity(s),time_sensitivity(ts),contagiousness(c) {}

	 std::string get_name() const { return name; }
	 constexpr int_type get_severity() const { return severity; }
	 constexpr int_type get_time_sensitivity() const { return time_sensitivity; }
	 constexpr int_type get_contagiousness() const { return contagiousness; }


	constexpr bool operator==(const Ailment& other) const
	 {
		return other.name == name && other.severity == severity &&
			other.time_sensitivity == time_sensitivity && other.contagiousness ==
			contagiousness;



	 }
};
