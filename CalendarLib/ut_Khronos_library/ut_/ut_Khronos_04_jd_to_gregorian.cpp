/** @file ut_khronos_04_jd_to_gregorian.cpp

	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library jdn to gregorian functions unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>

#include <iomanip>
#include <strstream>
using namespace std;
using namespace khronos;





#if TEST_PHASE>=9
/**	Test known JD to Gregorian conversions. */
BOOST_AUTO_TEST_CASE(test_jd_to_gregorian) {
	PhaseList::instance().implements(9);

	auto test = [](year_t year, month_t month, day_t day, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		jd_to_gregorian(jd, y, m, d);

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

	test(4714_BCE, November, 24, -0.5, __LINE__);			// beginning of the Julian Epoch 
	test(1_CE, January, 1, GREGORIAN_EPOCH, __LINE__);		// January 1, 1 CE
	test(1582_CE, October, 15, 2299160.5, __LINE__);		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582_CE, December, 20, 2299226.5, __LINE__);		// Gregorian adoption date France
	test(1752_CE, September, 14, 2361221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858_CE, November, 16, 2400000 - 0.5, __LINE__);
	test(2012_CE, September, 14, 2456184.5, __LINE__);
	test(2132_CE, August, 31, 2500000 - 0.5, __LINE__);


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_gregorian(jd, y, m, d, h, mi, s);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << " from line: " << line;
		BOOST_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << " from line: " << line;
		BOOST_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << " from line: " << line;
		BOOST_CHECK_MESSAGE(d == day, ossD.str());

		ostringstream ossH;
		ossH << "h(" << h << ") != hour(" << hour << " from line: " << line;
		BOOST_CHECK_MESSAGE(h == hour, ossH.str());

		ostringstream ossMi;
		ossMi << "mi(" << mi << ") != minute(" << minute << " from line: " << line;
		BOOST_CHECK_MESSAGE(mi == minute, ossMi.str());

		ostringstream ossS;
		ossS << "s(" << s << ") != second(" << second << " from line: " << line;
		BOOST_CHECK_MESSAGE(s == second, ossS.str());
	};
	test2(2132_CE, August, 31, 12, 0, 0, 2500000, __LINE__);
	test2(2132_CE, August, 31,   6, 0, 0, 2500000 - 0.25, __LINE__);
	test2(2132_CE, August, 31, 18, 0, 0, 2500000 + 0.25, __LINE__);
	test2(2132_CE, August, 31, 12, 0, 1, 2500000 + 1.0 / (24 * 60 * 60), __LINE__);
}
#endif // TEST_PHASE 9