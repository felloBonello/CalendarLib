#include "khronos/gregorian_calendar.hpp"
#include "khronos/julian_calendar.hpp"
#include "khronos/julian_day.hpp"
#include "khronos/def.hpp"
#include <ctime>
using namespace std;



namespace khronos {
	Julian::Julian() {
		time_t utcTime = time(NULL);

		struct tm tmLocal;
		localtime_s(&tmLocal, &utcTime);

		year_ = tmLocal.tm_year + 1900;
		month_ = tmLocal.tm_mon + 1;
		day_ = tmLocal.tm_mday;
		hour_ = tmLocal.tm_hour;
		minute_= tmLocal.tm_min;
		second_ = tmLocal.tm_sec;
	}

	Julian::Julian(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s)
	{
		year_ = y;
		month_ = m;
		day_ = d;
		hour_ = h;
		minute_ = mi;
		second_ = s;
	}

	std::ostream& operator << (std::ostream& os, Julian const& j) {
		Julian julian = j;
		return os << julian.to_string();
	}
}