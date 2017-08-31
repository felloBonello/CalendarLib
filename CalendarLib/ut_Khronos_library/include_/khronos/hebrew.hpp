#ifndef __HEBREW_HPP__
#define __HEBREW_HPP__


#include "khronos/def.hpp"
#include "khronos/julian_day.hpp"
#include <string>
#include <array>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iomanip>


namespace khronos
{
	// constants
	jd_t const  HEBREW_EPOCH = 347995.5;

	enum hebrew_month_codes {
		Nisan = 1, Iyyar, Sivan, Tammuz,
		Av, Elul, Tishri, Heshvan,
		Kislev, Teveth, Shevat, Adar, Veadar
	};

	// define it inline so that way it will do a code replacement in the 
	// gregorian_to_jd function in that .cpp file
	bool is_hebrew_leapyear(year_t year);

	// conversion functions
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day);
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_hebrew(jdn_t jdn, year_t &year, month_t &month, day_t &day);
	void jd_to_hebrew(jdn_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);


	// Gregorian Class derives from our base calendar class
	class Hebrew : public Calendar
	{
		void from_jd(jd_t jd) { jd_to_hebrew(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return hebrew_to_jd(year_, month_, day_, hour_, minute_, second_); }

		string getMonthName()
		{
			array<string, 14> names = { "",
				"Nisan", "Iyyar", "Sivan", "Tammuz",
				"Av", "Elul", "Tishri", "Heshvan",
				"Kislev", "Teveth", "Shevat", "Adar", "Veadar" };
			return names[month_];
		}

		string formatTime()
		{
			int adjustedHour;
			string ampm;

			if (hour_ == 0)
			{
				adjustedHour = (hour_ + 12);
				ampm = " am";
			}
			else if (hour_ > 12)
			{
				adjustedHour = (hour_ - 12);
				ampm = " pm";
			}
			else if (hour_ == 12)
			{
				adjustedHour = hour_;
				ampm = " pm";
			}
			else if (hour_ < 12)
			{
				adjustedHour = hour_;
				ampm = " am";
			}
			ostringstream stringStream;
			stringStream << adjustedHour << ":" << setw(2) << setfill('0') << minute_ << ":" << setw(2) << setfill('0') << second_ << ampm;
			string copyOfStr = stringStream.str();
			return copyOfStr;
		}
	public:
		// default constructor
		Hebrew();
		// Constructors
		Hebrew(year_t y, month_t m, day_t d) :Calendar(y, m, d) {}
		Hebrew(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s);
		Hebrew(Jd const& jd) { from_jd(jd.jd()); }
		// implicit operator
		// Allows Jd jd = g;
		operator Jd () const { return Jd(to_jd()); }
		// Assignment operator converts from Jd type to Gregorian type
		string to_string()
		{
			string d = std::to_string(day_);
			string y = std::to_string(year_);

			return  (getMonthName() + " " + d + " " + y + ", " + formatTime());
		}

		Hebrew& operator = (Jd const& jd)
		{
			from_jd(jd.jd());
			return *this;
		}

		~Hebrew() {}
	};

	inline string hebrew_month_name(month_t i)
	{
		array<string, 14> names = { "",
			"Nisan", "Iyyar", "Sivan", "Tammuz",
			"Av", "Elul", "Tishri", "Heshvan",
			"Kislev", "Teveth", "Shevat", "Adar", "Veadar" };
		return names[i];
	}

	inline int hebrew_months_in_year(year_t year)
	{
		return (is_hebrew_leapyear(year)) ? (13) : (12);
	}

	inline int hebrew_days_in_year(year_t year)
	{
		return static_cast<int>(hebrew_to_jd(year + 1, 7, 1) - hebrew_to_jd(year, 7, 1));
	}

	inline int hebrew_days_in_month(year_t y, month_t m)
	{
		int days = 30;
		if (m == 2 || m == 4 || m == 6 || m == 10 || m == 13)
			days = 29;
		if (m == 12 && !is_hebrew_leapyear(y))
			days = 29;
		if (m == 8 && hebrew_days_in_year(y) % 10 != 5)
			days = 29;
		if (m == 9 && hebrew_days_in_year(y) % 10 == 3)
			days = 29;
		return days;
	}

	std::ostream& operator << (std::ostream& os, Hebrew const& g);

}


#endif