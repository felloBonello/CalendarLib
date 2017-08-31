/** @file ut_khronos_16_hebrew_concepts.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Hebrew Calendar concepts unit test.
*/

#include <khronos.hpp>
using namespace khronos;
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <array>



#if TEST_PHASE>=32
BOOST_AUTO_TEST_CASE(test_Hebrew_month_name) {
	PhaseList::instance().implements(32);
	std::array<std::string, 14> const names = { "",
		"Nisan", "Iyyar", "Sivan", "Tammuz",
		"Av", "Elul", "Tishri", "Heshvan",
		"Kislev", "Teveth", "Shevat", "Adar", "Veadar" };

	for (month_t i = 1; i <= 13; ++i)
		BOOST_CHECK(hebrew_month_name(i) == names[i]);
}
#endif