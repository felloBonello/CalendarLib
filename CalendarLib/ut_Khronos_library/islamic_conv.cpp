#include "khronos/julian_day.hpp"
#include "khronos/islamic.hpp"
#include <cmath>
#include <cassert>
#include <string>
#include <array>
using namespace std;

namespace khronos {
	bool is_islamic_leapyear(year_t year)
	{
		return (((11 * year) + 14) % 30 < 11);
	}

	jd_t islamic_to_jd(year_t year, month_t month, day_t day)
	{
		jd_t jdn = day + ceil(29.5 * (month - 1.00)) + (year - 1.00) * 354.00 + floor((3.0 + 11.0 * year) / 30.0) + ISLAMIC_EPOCH - 1.0;
		return jdn;
	}

	jd_t islamic_to_jd(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s)
	{
		double jdn = islamic_to_jd(y, m, d);
		double time = tod(h, mi, s);
		time = (time >= 0.5) ? (time - 1) : (time);
		return jdn + time;
	}
	
	void jd_to_islamic(jdn_t jdn, year_t &year, month_t &month, day_t &day)
	{
		jdn = floor(jdn) + 0.5;
		year = static_cast<year_t>(floor((30 * (jdn - ISLAMIC_EPOCH) + 10646) / 10631));
		month = static_cast<month_t>(min(12.00 , ceil((jdn - (29 + islamic_to_jd(year, 1, 1))) / 29.5) + 1));
		day = static_cast<day_t>(jdn - islamic_to_jd(year, month, 1) + 1);
	}

	void jd_to_islamic(jdn_t jdn, year_t &y, month_t &m, day_t &d, hour_t &h, minute_t &mi, second_t &s)
	{
		jd_to_islamic(jdn, y, m, d);
		hms(jdn, h, mi, s);
	}
}