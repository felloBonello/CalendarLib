#ifndef __DEF_HPP__
#define __DEF_HPP__
#include <math.h>
#include <ctime>

using namespace std;


namespace khronos
{
	// typedef
	typedef double jd_t;   // Julian Date
	typedef double jdn_t;  // Julian Day Number
	typedef double tod_t;  // Time of day
	typedef long long year_t; // year
	typedef short month_t;    // month
	typedef short day_t;      // day
	typedef short hour_t;
	typedef short  minute_t;
	typedef double second_t;
	// values
	double const EARTH_ORBITAL_PERIOD_DAYS = 365.256363004;
	int  const SECONDS_PER_DAY = 86400;


	enum civil_month_codes_long { January = 1, February,March,April,
		May,June,July,August,September,October,November,December};
	enum Month { JAN = January, FEB, MAR, APR, MAY, JUN, JUL, AUG, 
		SEP, OCT, NOV, DEC };
	enum civil_weekday_codes_long { Monday=0,Tuesday,Wednesday,
		Thursday,Friday,Saturday,Sunday };
	enum DayOfWeek { MON=Monday, TUE, WED, THU, FRI, SAT, SUN };

	class Calendar
	{
	protected:
		year_t year_;
		month_t month_;
		day_t day_;
		hour_t hour_;
		minute_t minute_;
		second_t second_;
	public:
		// default constructor
		Calendar() :year_(1), month_(1), day_(1) {}
		// 3 arg constructor
		Calendar(year_t y, month_t m, day_t d) :year_(y), month_(m), day_(d), hour_(0), minute_(0), second_(0) {}
		// getters
		year_t year() const { return year_; }
		month_t month() const { return month_; }
		day_t day() const { return day_; }
		hour_t hour() const { return hour_; }
		minute_t minute() const { return minute_; }
		second_t second() const { return second_; }

		~Calendar() {}
	};
	// Alternate query
	inline year_t year(Calendar const& date) { return date.year(); }
	inline month_t month(Calendar const& date) { return date.month(); }
	inline day_t day(Calendar const& date) { return date.day(); }
	inline year_t hour(Calendar const& date) { return date.hour(); }
	inline month_t minute(Calendar const& date) { return date.minute(); }
	inline second_t second(Calendar const& date) { return date.second(); }
}

#endif
