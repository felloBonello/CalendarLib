#ifndef __GREGORIAN_CALENDAR_HPP__
#define __GREGORIAN_CALENDAR_HPP__
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
	jd_t const GREGORIAN_EPOCH = 1721425.5;

	// constexpr
	constexpr long long operator ""_BCE(unsigned long long y)
	{
		return -(long long)y + 1;
	}
	constexpr long long operator ""_CE(unsigned long long y)
	{
		return (long long)y;
	}

	// define it inline so that way it will do a code replacement in the 
	// gregorian_to_jd function in that .cpp file
 bool is_gregorian_leapyear(year_t year);

	// conversion functions
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day);
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	

	// Gregorian Class derives from our base calendar class
	class Gregorian : public Calendar
	{
		void from_jd(jd_t jd){jd_to_gregorian(jd, year_, month_, day_, hour_, minute_, second_);	}
		jd_t to_jd() const {return gregorian_to_jd(year_, month_, day_, hour_, minute_, second_);	}

		string getMonthName()
		{ 
			array<string, 13> names = { "", "January", "February", "March",
				"April", "May", "June", "July", "August", "September", "October",
				"November", "December" };
			return names[month_];
		}

		string getWeekDay() 
		{
			array<string, 7> names = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
			return names[day_of_week(Jd(to_jd()))]; 
		}

		string formatYear()
		{
			string y;
			if (year_ < 0)

				y = std::to_string(abs(year_) + 1) + " BCE";
			else
				y = std::to_string(year_) + " CE";
			return y;
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
				adjustedHour = hour_ ;
				ampm = " am";
			}
			ostringstream stringStream;
			stringStream << adjustedHour << ":" << setw(2) << setfill('0') << minute_ << ":" << setw(2) << setfill('0') << second_ << ampm;
			string copyOfStr = stringStream.str();
			return copyOfStr;
		}
	public:
		// default constructor
		Gregorian();
		// Constructors
		Gregorian(year_t y, month_t m, day_t d) :Calendar(y, m, d) {}
		Gregorian(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s);
		Gregorian(Jd const& jd) { from_jd(jd.jd()); }
		// implicit operator
		// Allows Jd jd = g;
		operator Jd () const { return Jd(to_jd()); }
		// Assignment operator converts from Jd type to Gregorian type
		string to_string()
		{
			string d = std::to_string(day_);
			string h = std::to_string(hour_);
			string m = std::to_string(minute_);
			string s = std::to_string(second_);

			return  (getWeekDay() + ", " + getMonthName() + " " + d + " " + formatYear() + ", " + formatTime());
		}

		Gregorian& operator = (Jd const& jd)
		{
			from_jd(jd.jd());
			return *this;
		}

		~Gregorian() {}
	};

	inline string gregorian_month_name(month_t i)
	{
		array<string, 13> names = { "", "January", "February", "March",
			"April", "May", "June", "July", "August", "September", "October",
			"November", "December" };
		return names[i];
	}
	
	inline string gregorian_short_month_name(month_t i)
	{
		array<string, 13> names = { "", "JAN", "FEB", "MAR",
			"APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT",
			"NOV", "DEC" };
		return names[i];
	}

	inline int gregorian_days_in_month(month_t m, bool isLeapYear)
	{
		if (isLeapYear && m == 2)
			return 29;
		else if (!isLeapYear && m == 2)
			return 28;

		return ((m == 4 || m == 6 || m == 9 || m == 11) ? 30 : 31);
	}

	inline Gregorian operator + (Gregorian const& dt, packaged_month pm) {
		long long year = static_cast<long long>(dt.year());
		long long month = static_cast<long long>(dt.month());
		int day = static_cast<int>(dt.day());

		long long y = year + pm.nMonths_ / 12;
		long long m = month + pm.nMonths_ % 12;
		long long adjust = (m - 1) / 12 + (m - 12) / 12;
		y = y + adjust;
		m = m - adjust * 12;

		year_t newYear = static_cast<year_t>(y);
		month_t newMonth = static_cast<month_t>(m);
		int d = min(day, gregorian_days_in_month(newMonth, is_gregorian_leapyear(newYear)));
		day_t newDay = static_cast<day_t>(d);
		return Gregorian(newYear, newMonth, newDay, dt.hour(), dt.minute(), dt.second());
	}

	inline Gregorian operator - (Gregorian const& dt, packaged_month pm) {
		long long year = static_cast<long long>(dt.year());
		long long month = static_cast<long long>(dt.month());
		int day = static_cast<int>(dt.day());

		long long y = year - pm.nMonths_ / 12;
		long long m = month - pm.nMonths_ % 12;
		long long adjust = (m - 1) / 12 + (m - 12) / 12;
		y = y - adjust;
		m = m + adjust * 12;

		year_t newYear = static_cast<year_t>(y);
		month_t newMonth = static_cast<month_t>(m);
		int d = min(day, gregorian_days_in_month(newMonth, is_gregorian_leapyear(newYear)));
		day_t newDay = static_cast<day_t>(d);
		return Gregorian(newYear, newMonth, newDay, dt.hour(), dt.minute(), dt.second());
	}
	
	inline Gregorian operator + (Gregorian const& g, packaged_year years)
	{
		year_t y = g.year() + static_cast<year_t>(years.nYears_);
		month_t m = g.month();
		day_t d = g.day();

		if (m == February && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Gregorian(y, m, d, g.hour(), g.minute(), g.second());
	}
	inline Gregorian operator - (Gregorian const& g, packaged_year years) {
		year_t y = g.year() - static_cast<year_t>(years.nYears_);
		month_t m = g.month();
		day_t d = g.day();

		if (m == February && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Gregorian(y, m, d, g.hour(), g.minute(), g.second());
	}

	std::ostream& operator << (std::ostream& os, Gregorian const& g);

}


#endif
