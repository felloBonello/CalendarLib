/** @file ut_khronos_03_gregorian_to_jd.cpp

	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library gregorian to jdn functions unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>

#include <iomanip>
#include <strstream>
using namespace std;
using namespace khronos;



#if TEST_PHASE>=7
BOOST_AUTO_TEST_CASE(gregorian_to_jdn_basic_test) {
	PhaseList::instance().implements(7);

	auto test = [](year_t year, month_t month, day_t day, jd_t jdn, int line) {
		auto jg = gregorian_to_jd(year, month, day);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jdn(" << jdn << ") from line: " << line;
		BOOST_CHECK_MESSAGE(jg == jdn, oss.str());
	};

	test(4714_BCE, November, 24, -0.5, __LINE__);			// beginning of the Julian Epoch 
	test(1_CE, January, 1, GREGORIAN_EPOCH, __LINE__);		// January 1, 1 CE
	test(1582_CE, October, 15, 2299160.5, __LINE__);		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582_CE, December, 20, 2299226.5, __LINE__);		// Gregorian adoption date France
	test(1752_CE, September, 14, 2361221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858_CE, November, 16, 2400000 - 0.5, __LINE__);
	test(2012_CE, September, 14, 2456184.5, __LINE__);
	test(2132_CE, August, 31, 2500000 - 0.5, __LINE__);
}
#endif



#if TEST_PHASE>=8
BOOST_AUTO_TEST_CASE(concept_gregorian_jdn_with_tod_test) {
	PhaseList::instance().implements(8);
	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd, int line) {
		auto jg = gregorian_to_jd(year, month, day, hour, minute, seconds);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jd(" << jd << ") from line: " << line;
		BOOST_CHECK_MESSAGE(jg == jd, oss.str());
	};
	test2(2132_CE, August, 31, 12, 0, 0, 2500000, __LINE__);
	test2(2132_CE, August, 31, 6, 0, 0, 2500000 - 0.25, __LINE__);
	test2(2132_CE, August, 31, 18, 0, 0, 2500000 + 0.25, __LINE__);
	test2(2132_CE, August, 31, 12, 0, 1, 2500000 + 1.0 / (24 * 60 * 60), __LINE__);
}
#endif
