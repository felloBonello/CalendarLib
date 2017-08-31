/** @file ut_khronos_02_gregorian_to_jdn.cpp

	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library gregorian to jdn functions unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <array>
using namespace khronos;



#if TEST_PHASE>=4
BOOST_AUTO_TEST_CASE(test_Gregorian_leapyear_test) {
	PhaseList::instance().implements(4);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(2000_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1999_CE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1996_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(2001_CE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(2004_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1900_CE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1600_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(4_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1_CE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1_BCE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(2_BCE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(4_BCE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(5_BCE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(6_BCE), false);
}
#endif



#if TEST_PHASE>=5
BOOST_AUTO_TEST_CASE(test_Gregorian_days_of_month) {
	PhaseList::instance().implements(5);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JAN, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(FEB, false), 28);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(MAR, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(APR, false), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(MAY, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JUN, false), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JUL, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(AUG, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(SEP, false), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(OCT, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(NOV, false), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(DEC, false), 31);

	BOOST_CHECK_EQUAL(gregorian_days_in_month(JAN, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(FEB, true), 29);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(MAR, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(APR, true), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(MAY, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JUN, true), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JUL, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(AUG, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(SEP, true), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(OCT, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(NOV, true), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(DEC, true), 31);
}
#endif



#if TEST_PHASE>=6
BOOST_AUTO_TEST_CASE(test_Gregorian_month_name) {
	PhaseList::instance().implements(6);
	std::array<std::string, 13> names = { "", "January", "February", "March",
		"April", "May", "June", "July", "August", "September", "October",
		"November", "December" };

	for (month_t i = 1; i <= 12; ++i)
		BOOST_CHECK(gregorian_month_name(i) == names[i]);

	for (month_t i = 1; i <= 12; ++i) {
		auto s = names[i].substr(0, 3);
		s[1] = (char)toupper(s[1]);
		s[2] = (char)toupper(s[2]);
		BOOST_CHECK(gregorian_short_month_name(i) == s);
	}
}
#endif