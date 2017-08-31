/** @file ut_khronos_19_vulcan_concepts.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Vulcan Calendar concepts unit test.
*/

#include <khronos.hpp>
using namespace khronos;
#include <array>

#include "ut_phase_list.hpp"
#include "ut_utilities.hpp"
#include <boost/test/auto_unit_test.hpp>



#if TEST_PHASE>=35
BOOST_AUTO_TEST_CASE(test_vulcan_days_of_month) {
	PhaseList::instance().implements(35);
	BOOST_CHECK_EQUAL(vulcan_days_in_month(), 21);
}


BOOST_AUTO_TEST_CASE(test_Vulcan_month_name) {
	static std::array<char const *, 13> const names = {
		"",
		"Z'at",
		"D'ruh",
		"K'riBrax",
		"re'T'Khutai",
		"T'keKhuti",
		"Khuti",
		"Ta'Krat",
		"K'ri'lior",
		"et'khior",
		"T'lakht",
		"T'ke'Tas",
		"Tasmeen",
	};

	for (month_t i = 1; i <= 12; ++i)
		BOOST_CHECK(vulcan_month_name(i) == names[i]);

}



/** Test Vulcan month names. */
BOOST_AUTO_TEST_CASE(test_vulcan_month_names) {
	BOOST_CHECK(boost_compare("Z'at", vulcan_month_name(1)));
	BOOST_CHECK(boost_compare("D'ruh", vulcan_month_name(2)));
	BOOST_CHECK(boost_compare("K'riBrax", vulcan_month_name(3)));
	BOOST_CHECK(boost_compare("re'T'Khutai", vulcan_month_name(4)));
	BOOST_CHECK(boost_compare("T'keKhuti", vulcan_month_name(5)));
	BOOST_CHECK(boost_compare("Khuti", vulcan_month_name(6)));
	BOOST_CHECK(boost_compare("Ta'Krat", vulcan_month_name(7)));
	BOOST_CHECK(boost_compare("K'ri'lior", vulcan_month_name(8)));
	BOOST_CHECK(boost_compare("et'khior", vulcan_month_name(9)));
	BOOST_CHECK(boost_compare("T'lakht", vulcan_month_name(10)));
	BOOST_CHECK(boost_compare("T'ke'Tas", vulcan_month_name(11)));
	BOOST_CHECK(boost_compare("Tasmeen", vulcan_month_name(12)));
}
#endif