/** @file ut_khronos_10_julian_conv.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Julian Calendar class unit test.
*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
using namespace khronos;

#include <iomanip>
#include <sstream>
using namespace std;



#if TEST_PHASE>=26
/** Test known Julian to JD conversions. */
BOOST_AUTO_TEST_CASE(test_Julian_to_jd) {
	PhaseList::instance().implements(26);

	auto test = [](year_t year, month_t month, day_t day, jd_t jdn, int line) {
		auto jg = julian_to_jd(year, month, day);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jdn(" << jdn << ") from line: " << line;
		BOOST_CHECK_MESSAGE(jg == jdn, oss.str());
	};

	test(-4712, January, 1, -0.5, __LINE__);				// beginning of the Julian Epoch 
	test(1, January, 1, JULIAN_EPOCH, __LINE__);			// January 1, 1 CE
	test(1582, October, 5, 2299160.5, __LINE__);			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582, December, 10, 2299226.5, __LINE__);		// Gregorian adoption date France
	test(1752, September, 3, 2361221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858, November, 4, 2400000 - 0.5, __LINE__);
	test(2012, September, 1, 2456184.5, __LINE__);
	test(2132, August, 17, 2500000 - 0.5, __LINE__);


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jdn, int line) {
		auto jg = julian_to_jd(year, month, day, hour, minute, seconds);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jdn(" << jdn << ") from line: " << line;
		BOOST_CHECK_MESSAGE(jg == jdn, oss.str());
	};
	test2(2132, August, 17, 12, 0, 0, 2500000, __LINE__);
	test2(2132, August, 17, 6, 0, 0, 2500000 - 0.25, __LINE__);
	test2(2132, August, 17, 18, 0, 0, 2500000 + 0.25, __LINE__);
	test2(2132, August, 17, 12, 0, 1, 2500000 + 1.0 / (24 * 60 * 60), __LINE__);
}


/**	Test known JD to Julian conversions. */
BOOST_AUTO_TEST_CASE(jdn_to_gregorian_test) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jdn, int line) {
		year_t y;
		month_t m;
		day_t d;
		jd_to_julian(jdn, y, m, d);

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

	test(4713_BC, January, 1, -0.5, __LINE__);			// beginning of the Julian Epoch 
	test(1, January, 1, JULIAN_EPOCH, __LINE__);		// January 1, 1 CE
	test(1582, October, 5, 2299160.5, __LINE__);		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582, December, 10, 2299226.5, __LINE__);		// Gregorian adoption date France
	test(1752, September, 3, 2361221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858, November, 4, 2400000 - 0.5, __LINE__);
	test(2012, September, 1, 2456184.5, __LINE__);
	test(2132, August, 17, 2500000 - 0.5, __LINE__);


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second, jd_t jdn, int line) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_julian(jdn, y, m, d, h, mi, s);

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
		ossY << "h(" << h << ") != hour(" << hour << " from line: " << line;
		BOOST_CHECK_MESSAGE(h == hour, ossH.str());

		ostringstream ossMi;
		ossMi << "mi(" << mi << ") != minute(" << minute << " from line: " << line;
		BOOST_CHECK_MESSAGE(mi == minute, ossMi.str());

		ostringstream ossS;
		ossS << "s(" << s << ") != second(" << second << " from line: " << line;
		BOOST_CHECK_MESSAGE(s == second, ossS.str());
	};
	test2(2132, August, 17, 12, 0, 0, 2500000, __LINE__);
	test2(2132, August, 17, 6, 0, 0, 2500000 - 0.25, __LINE__);
	test2(2132, August, 17, 18, 0, 0, 2500000 + 0.25, __LINE__);
	test2(2132, August, 17, 12, 0, 1, 2500000 + 1.0 / (24 * 60 * 60), __LINE__);
}
#endif



#if TEST_PHASE>=38
#if defined( FULL_TEST )
/**	Check all conversions from the lowest Proleptic Julian date, until a day well in the future. */
BOOST_AUTO_TEST_CASE(test_julian_full) {

	cout << "Starting Julian FULL_TEST: ";
	jd_t low = julian_to_jd(-4799, January, 1);
	jd_t high = julian_to_jd(4800, January, 1);
	for (jd_t jd = low; jd <= high; jd += 0.125) {
		year_t year;
		month_t month;
		day_t day;
		jd_to_julian(jd, year, month, day);
		jd_t result = julian_to_jd(year, month, day);
		BOOST_CHECK_EQUAL(jd_to_jdn(jd)-0.5, result);
		hour_t hours;
		minute_t minutes;
		second_t seconds;
		jd_to_julian(jd, year, month, day, hours, minutes, seconds);
		result = julian_to_jd(year, month, day, hours, minutes, seconds);
		BOOST_CHECK_EQUAL(jd, result);
	}
	cout << "... completed\n";
}
#endif
#endif