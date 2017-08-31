#include "khronos/gregorian_calendar.hpp"
#include "khronos/julian_day.hpp"
#include <ctime>
using namespace std;



namespace khronos {
	Gregorian::Gregorian() {
		time_t utcTime = time(NULL);

		struct tm tmLocal;
		localtime_s(&tmLocal, &utcTime);
		year_ = tmLocal.tm_year + 1900;
		month_ = tmLocal.tm_mon + 1;
		day_ = tmLocal.tm_mday;
		hour_ = tmLocal.tm_hour;
		minute_ = tmLocal.tm_min;
		second_ = tmLocal.tm_sec;
	}

	Gregorian::Gregorian(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s)
	{
		year_ = y;
		month_ = m;
		day_ = d;
		hour_ = h;
		minute_ = mi;
		second_ = s;
	}

	std::ostream& operator << (std::ostream& os, Gregorian const& g) {
		Gregorian greg = g;
		return os << greg.to_string();
	}
}