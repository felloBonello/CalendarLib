/** @file ut_khronos_20_vulcan_conv.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Vulcan Calendar conversion unit test.
*/

#include <khronos.hpp>
using namespace khronos;

#include <sstream>
#include <iomanip>
using namespace std;

#include "ut_phase_list.hpp"
#include "ut_utilities.hpp"
#include <boost/test/auto_unit_test.hpp>



#if TEST_PHASE>=36
/** Test known Vulcan to JD conversions. */
BOOST_AUTO_TEST_CASE(test_vulcan_to_jd) {
	PhaseList::instance().implements(36);

	auto test = [](year_t year, month_t month, day_t day, jd_t jd, int line) {
		auto jg = vulcan_to_jd(year, month, day);
		jg = round(jg, 4);
		jd = round(jd, 4);
		ostringstream oss;
		oss << fixed << setprecision(15) << "jg(" << jg << ") != jd(" << jd << ") from line: " << line;
		BOOST_CHECK_MESSAGE(jg == jd, oss.str());
	};

	test(1, Zat, 1, VULCAN_EPOCH, __LINE__);
	test(-651, Druh, 18, -1.0285714, __LINE__);					// beginning of the Julian Epoch 


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd, int line) {
		auto jg = vulcan_to_jd(year, month, day, hour, minute, seconds);
		jg = round(jg, 4);
		jd = round(jd, 4);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jd(" << jd << ") from line: " << line;
		BOOST_CHECK_MESSAGE(jg == jd, oss.str());
	};
	test2(1, Zat, 1, 0, 0, 0, VULCAN_EPOCH, __LINE__);
	test2(8733, TaKrat, 10, 15, 4, 20, 2500000, __LINE__);
}



/**	Test known JD to Vulcan conversions. */
BOOST_AUTO_TEST_CASE(test_jd_to_vulcan) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		jd_to_vulcan(jd, y, m, d);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << " from line: " << line;
		BOOST_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << " from line: " << line;
		BOOST_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << " from line: " << line;
		BOOST_CHECK_MESSAGE(d == day, ossD.str());
	};

	test(-651, Druh, 18, 0, __LINE__);						// beginning of the Julian Epoch 
	test(1, Zat, 1, VULCAN_EPOCH, __LINE__);


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_vulcan(jd, y, m, d, h, mi, s);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << ") from line: " << line;
		BOOST_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << ") from line: " << line;
		BOOST_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << ") from line: " << line;
		BOOST_CHECK_MESSAGE(d == day, ossD.str());

		ostringstream ossH;
		ossH << "h(" << h << ") != hour(" << hour << ") from line: " << line;
		BOOST_CHECK_MESSAGE(h == hour, ossH.str());

		ostringstream ossMi;
		ossMi << "mi(" << mi << ") != minute(" << minute << ") from line: " << line;
		BOOST_CHECK_MESSAGE(mi == minute, ossMi.str());

		ostringstream ossS;
		ossS << "s(" << s << ") != second(" << second << ") from line: " << line;
		BOOST_CHECK_MESSAGE(round(s) == second, ossS.str());
	};
	test2(1, Zat, 1, 0, 0, 0, VULCAN_EPOCH, __LINE__);
	test2(8733, TaKrat, 10, 15, 4, 20, 2500000, __LINE__);
}
#endif


#if TEST_PHASE>=38
/**	Check all conversions from the lowest Proleptic Vulcan date, until a day well in the future. */
#if defined( FULL_TEST )
BOOST_AUTO_TEST_CASE(test_vulcan_to_jd_full) {

	cout << "Starting Vulcan FULL_TEST: ";
	auto increment = 0.1;
	jd_t low = vulcan_to_jd(1, Zat, 1);
	jd_t high = vulcan_to_jd(10000, Tasmeen, 21);
	for (jd_t jd = low; jd <= high; jd += increment) {
		year_t year;
		month_t month;
		day_t day;
		hour_t hours;
		minute_t minutes;
		second_t seconds;
		jd_to_vulcan(jd, year, month, day, hours, minutes, seconds);
		jd_t result = vulcan_to_jd(year, month, day, hours, minutes, seconds);
		BOOST_CHECK_CLOSE(jd, result, 0.0000001);
	}
	cout << "... completed\n";
}
#endif
#endif