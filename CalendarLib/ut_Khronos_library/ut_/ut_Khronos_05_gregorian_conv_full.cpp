/** @file ut_khronos_05_gregorian_conv_full.cpp

	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library jdn to gregorian functions unit test.
*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
using namespace std;



#if defined(FULL_TEST)
#if TEST_PHASE>=38
/**	Check all conversions from the lowest Proleptic Gregorian date, until a day well in the future. */
BOOST_AUTO_TEST_CASE(test_gregorian_full) {
	PhaseList::instance().implements(38);
	using namespace khronos;

	cout << "Starting Gregorian FULL_TEST: ";
	auto low = gregorian_to_jd(4800_BCE, January, 1);
	auto high = gregorian_to_jd(4800_CE, January, 1);
	for (auto jd = low; jd <= high; jd += 0.125) {
		year_t year;
		month_t month;
		day_t day;
		jd_to_gregorian(jd, year, month, day);
		auto result = gregorian_to_jd(year, month, day);
		BOOST_CHECK_EQUAL(jd_to_jdn(jd)-0.5, result);
		hour_t hours;
		minute_t minutes;
		second_t seconds;
		jd_to_gregorian(jd, year, month, day, hours, minutes, seconds);
		result = gregorian_to_jd(year, month, day, hours, minutes, seconds);
		BOOST_CHECK_CLOSE(jd, result,0.00001);
	}
	cout << "... completed\n";
}
#endif
#endif