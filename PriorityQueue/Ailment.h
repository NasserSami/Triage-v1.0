#pragma once

#include <string>

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
	 Ailment(std::string n = "", int s = 0, int ts = 0, int c = 0) : 
		name(n),severity(s),time_sensitivity(ts),contagiousness(c) {}

	 std::string get_name() const { return name; }
	 constexpr int_type get_severity() const { return severity; }
	 constexpr int_type get_time_sensitivity() const { return time_sensitivity; }
	 constexpr int_type get_contagiousness() const { return contagiousness; }



};
