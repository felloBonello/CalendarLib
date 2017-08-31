#include "khronos/julian_day.hpp"
#include <ctime>
#include "khronos/gregorian_calendar.hpp"
#include <sstream>
using namespace std;


namespace khronos {

	// Default ctor initializes the object to the current time
	Jd::Jd() {
		time_t utcTime = time(NULL);

		struct tm tmLocal;
		localtime_s(&tmLocal, &utcTime);
		jd_ = gregorian_to_jd(
			year_t(tmLocal.tm_year + 1900), 
			month_t(tmLocal.tm_mon + 1), 
			day_t(tmLocal.tm_mday),
			hour_t(tmLocal.tm_hour), 
			minute_t(tmLocal.tm_min), 
			second_t(tmLocal.tm_sec));

	}

	std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << "JD " << jd.jd();
	}
}