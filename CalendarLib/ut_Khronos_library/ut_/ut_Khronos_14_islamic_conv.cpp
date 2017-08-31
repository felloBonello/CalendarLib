/** @file ut_khronos_14_islamic_conv.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Islamic Calendar conversions unit test.
*/

#include <khronos.hpp>
using namespace khronos;
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
using namespace std;


#if TEST_PHASE>=30
/** Test known Islamic to JDN conversions. */
BOOST_AUTO_TEST_CASE(test_islamic_to_jd) {
	PhaseList::instance().implements(30);

	auto test = [](year_t year, month_t month, day_t day, jd_t jdn)->bool {
		return  islamic_to_jd(year, month, day) == jdn;
	};

	BOOST_CHECK(test(-5498, Shaban, 16, -0.5));			// beginning of the Julian Epoch
	BOOST_CHECK(test(1, Muharram, 1, ISLAMIC_EPOCH));	// Muharram 1, 1 A.H.
	BOOST_CHECK(test(990, Ramadan, 17, 2299160.5));		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	BOOST_CHECK(test(990, DhulQadah, 24, 2299226.5));		// Gregorian adoption date France
	BOOST_CHECK(test(1165, DhulQadah, 5, 2361221.5));		// Gregorian adoption date British Empire
	BOOST_CHECK(test(1275, RabiathThani, 9, 2400000 - 0.5));
	BOOST_CHECK(test(1433, Shawwal, 27, 2456184.5));
	BOOST_CHECK(test(1557, JumadatTania, 18, 2500000 - 0.5));


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jdn) {
		auto jd = islamic_to_jd(year, month, day, hour, minute, seconds);
		BOOST_CHECK_EQUAL(jd, jdn);
	};
	test2(1557, JumadatTania, 19, 12, 0, 0, 2500000);
	test2(1557, JumadatTania, 18, 6, 0, 0, 2500000 - 0.25);
	test2(1557, JumadatTania, 19, 18, 0, 0, 2500000 + 0.25);
	test2(1557, JumadatTania, 19, 12, 0, 1, 2500000 + 1.0 / (24 * 60 * 60));
}



/**	Test known JDN to Islamic conversions. */
BOOST_AUTO_TEST_CASE(test_jd_to_islamic) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jd)->bool {
		year_t y;
		month_t m;
		day_t d;
		jd_to_islamic(jd, y, m, d);
		return y == year && m == month && d == day;
	};

	BOOST_CHECK(test(-5498, Shaban, 16, -0.5));				// beginning of the Julian Epoch 
	BOOST_CHECK(test(1, Muharram, 1, ISLAMIC_EPOCH));		// January 1, 1 CE
	BOOST_CHECK(test(990, Ramadan, 17, 2299160.5));			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	BOOST_CHECK(test(990, DhulQadah, 24, 2299226.5));		// Gregorian adoption date France
	BOOST_CHECK(test(1165, DhulQadah, 5, 2361221.5));		// Gregorian adoption date British Empire
	BOOST_CHECK(test(1275, RabiathThani, 9, 2400000 - 0.5));
	BOOST_CHECK(test(1433, Shawwal, 27, 2456184.5));
	BOOST_CHECK(test(1557, JumadatTania, 18, 2500000 - 0.5));


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_islamic(jd, y, m, d, h, mi, s);
		BOOST_CHECK_EQUAL(y, year);
		BOOST_CHECK_EQUAL(m, month);
		BOOST_CHECK_EQUAL(d, day);
		BOOST_CHECK_EQUAL(h, hour);
		BOOST_CHECK_EQUAL(mi, minute);
		BOOST_CHECK_EQUAL(s, seconds);
	};
	test2(1557, JumadatTania, 19, 12, 0, 0, 2500000.0);
	test2(1557, JumadatTania, 18, 6, 0, 0, 2500000 - 0.25);
	test2(1557, JumadatTania, 19, 18, 0, 0, 2500000 + 0.25);
	test2(1557, JumadatTania, 19, 12, 0, 1, 2500000 + 1.0 / (24 * 60 * 60));
}
#endif



#if TEST_PHASE>=38
#if defined( FULL_TEST )
/**	Check all conversions from the lowest Proleptic Islamic date, until a day well in the future. */
BOOST_AUTO_TEST_CASE(test_islamic_full) {
	cout << "Starting Islamic FULL_TEST: ";
	jd_t low = islamic_to_jd(-4799, 1, 1);
	jd_t high = islamic_to_jd(4800, 1, 1);
	for (jd_t jdn = low; jdn <= high; jdn += 1.0) {
		year_t year;
		month_t month;
		day_t day;
		jd_to_islamic(jdn, year, month, day);
		jd_t result = islamic_to_jd(year, month, day);
		BOOST_CHECK_EQUAL(jdn, result);
	}
	cout << "... completed\n";
}
#endif
#endif