#include "khronos/julian_day.hpp"
#include <cmath>
#include <cassert>
#include <string>
#include <array>
using namespace std;

namespace khronos {
	bool is_julian_leapyear(year_t year)
	{
		return (year % 4 == 0);
	}

	jd_t julian_to_jd(year_t year, month_t month, day_t day)
	{
		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;
		jdn_t jdn = day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083.5;
		return jdn;
	}

	jd_t julian_to_jd(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s)
	{
		double jdn = julian_to_jd(y, m, d);
		double time = tod(h, mi, s);
		return jdn + time;
	}

	void jd_to_julian(jdn_t jdn, year_t &year, month_t &month, day_t &day)
	{
		long long a = static_cast<long long>(floor(jdn + 0.5));
		long long b = a + 1524;
		long long c = static_cast<long long>(floor((b - 122.1) / 365.25));
		long long d = static_cast<long long>(floor(365.25 * c));
		long long e = static_cast<long long>(floor((b - d) / 30.6001));
		month = static_cast<month_t>(floor((e < 14) ? e - 1 : e - 13));
		year = static_cast<year_t>(floor((month > 2) ? c - 4716 : c - 4715));
		day = static_cast<day_t>(b - d - floor(30.6001 * e));
	}

	void jd_to_julian(jdn_t jdn, year_t &y, month_t &m, day_t &d, hour_t &h, minute_t &mi, second_t &s)
	{
		jd_to_julian(jdn, y, m, d);
		hms(jdn, h, mi, s);
	}
}