#include "khronos/gregorian_calendar.hpp"
#include <cmath>
#include <cassert>
#include <string>
#include <array>
using namespace std;

namespace khronos {
	bool is_gregorian_leapyear(year_t year) {
		return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
	}


	namespace detail {
		jd_t gregorian_to_jd2(year_t year, month_t month, day_t day) {
			year_t y = year - 1;
			return
				(GREGORIAN_EPOCH - 1) +
				(365 * y) +
				floor(y / 4.0) +
				-floor(y / 100.0) +
				floor(y / 400.0) +
				floor(
					(((367 * month) - 362) / 12.0) +
					((month <= 2) ? 0 : (is_gregorian_leapyear(year) ? -1 : -2)) +
					day);
		}


		inline jd_t gregorian_to_jd1(year_t year, month_t month, day_t day) {
			long long a = (14 - month) / 12;
			long long y = year + 4800 - a;
			long long m = month + 12 * a - 3;
			return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 - 0.5;
		}
	}

	jd_t gregorian_to_jd(year_t year, month_t month, day_t day) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day of the month is 1");
		assert(day <= 31 && "Maximum day of the month is 31");
		assert(detail::gregorian_to_jd1(year, month, day) == detail::gregorian_to_jd2(year, month, day));
		return detail::gregorian_to_jd1(year, month, day);
	}

	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
	{
		return
			gregorian_to_jd(year, month, day)
			+ tod(hour, minute, second);
	}

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day) {
		jd = floor(jd - 0.5) + 0.5;
		long long a = static_cast<long long>(jd + 0.5) + 32044;
		long long b = (4 * a + 3) / 146097;
		long long c = a - b * 146097 / 4;
		long long d = (4 * c + 3) / 1461;
		long long e = c - 1461 * d / 4;
		long long m = (5 * e + 2) / 153;
		day = static_cast<day_t>(e - (153 * m + 2) / 5 + 1);
		month = static_cast<month_t>(m + 3 - 12 * (m / 10));
		year = b * 100 + d - 4800 + m / 10;
	}

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) 
	{
		jd_to_gregorian(jd, year, month, day);
		hms(jd, hour, minute, second);
	}
}