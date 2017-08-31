#include "khronos/julian_day.hpp"
#include "khronos/hebrew.hpp"
#include <cmath>
#include <cassert>
#include <string>
#include <array>
using namespace std;

namespace khronos {

	bool is_hebrew_leapyear(year_t year)
	{
		return ((7 * year + 1) % 19 < 7);
	}

	int delay_of_week(year_t year)
	{
		long long months = static_cast<long long>(floor((235 * year - 234) / 19));
		long long parts = 12084 + 13753 * months;
		long long days = static_cast<long long>(months * 29 + floor(parts / 25920));
		return static_cast<int>((((3 * (days + 1)) % 7) < 3) ? (days + 1) : (days));
	}

	int delay_adjacent_year(year_t year)
	{
		int days = 0;
		int last = delay_of_week(year - 1);
		int present = delay_of_week(year);
		int next = delay_of_week(year + 1);
		if (next - present == 356)
			days = 2;
		if (next - present != 356 && present - last == 382)
			days = 1;
		return days;
	}

	jdn_t hebrew_to_jd(year_t y, month_t m, day_t d)
	{
		jdn_t jdn = HEBREW_EPOCH + delay_of_week(y) + delay_adjacent_year(y) + d + 1;
		if (m < 7)
		{
			for (int i = 7; i <= hebrew_months_in_year(y); ++i)
				jdn += hebrew_days_in_month(y, i);
			for (int i = 1; i <= m - 1; ++i)
				jdn += hebrew_days_in_month(y, i);
		}
		if (m >= 7)
			for (int i = 7; i <= m - 1; ++i)
				jdn += hebrew_days_in_month(y, i);
		return jdn;
	}

	jd_t hebrew_to_jd(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s)
	{
		double jdn = hebrew_to_jd(y, m, d);
		double time = tod(h, mi, s);
		time = (time >= 0.5) ? (time - 1) : (time);
		return jdn + time;
	}

	void jd_to_hebrew(jdn_t jdn, year_t &year, month_t &month, day_t &day)
	{
		jdn = floor(jdn) + 0.5;
		int count = static_cast<int>(floor(((jdn - HEBREW_EPOCH) * 98496) / 35975351));
		year = count - 1;
		int  i = count;
		while (jdn >= hebrew_to_jd(i, 7, 1))
		{
			year += 1;
			i += 1;
		}
		int first = (jdn < hebrew_to_jd(year, 1, 1)) ? (7) : (1);
		month = first;
		i = first;
		while (jdn > hebrew_to_jd(year, i, hebrew_days_in_month(year, i)))
		{
			month += 1;
			i += 1;
		}
		day = static_cast<day_t>(floor(jdn - hebrew_to_jd(year, month, 1) + 1));
	}

	void jd_to_hebrew(jdn_t jdn, year_t &y, month_t &m, day_t &d, hour_t &h, minute_t &mi, second_t &s)
	{
		jd_to_hebrew(jdn, y, m, d);
		hms(jdn, h, mi, s);
	}
}