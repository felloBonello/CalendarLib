/** @file ut_khronos_13_islamic_concepts.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Islamic Calendar concepts unit test.
*/

#include <khronos.hpp>
using namespace khronos;

#include <array>
using namespace std;

#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>


#if TEST_PHASE>=29
BOOST_AUTO_TEST_CASE(test_Islamic_leapyear_test) {
	PhaseList::instance().implements(29);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1400), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1401), true);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1402), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1403), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1404), true);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1405), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(0), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(-1), true);
}



/** Check islamic leap years. */
BOOST_AUTO_TEST_CASE(test_islamic_leapyear) {
	BOOST_CHECK_EQUAL(is_islamic_leapyear(-5498), true);				// beginning of the Julian Epoch
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1), false);					// Muharram 1, 1 A.H.
	BOOST_CHECK_EQUAL(is_islamic_leapyear(990), false);					// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1165), false);				// Gregorian adoption date British Empire
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1275), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1433), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1434), true);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1557), false);
}



BOOST_AUTO_TEST_CASE(test_Islamic_month_name) {
	std::array<std::string, 13> const names = { "", "Muharram", "Safar", "Rabi'al-Awwal",
		"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
		"Dhu I-Qa'da", "Dhu I-Hijja" };

	for (month_t i = 1; i <= 12; ++i)
		BOOST_CHECK(islamic_month_name(i) == names[i]);
}
#endif