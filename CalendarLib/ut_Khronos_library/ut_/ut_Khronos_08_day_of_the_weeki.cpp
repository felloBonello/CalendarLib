/** @file ut_khronos_08_day_of_the_week.cpp

	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library day-of-the-week unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
using namespace khronos;



#if TEST_PHASE>=24
/** Day-of-week from JD. */
BOOST_AUTO_TEST_CASE(day_of_week_base_func_test) {
	PhaseList::instance().implements(24);
	Gregorian g(2012_CE, September, 24);  // a monday
	Jd jd = g;

	for (double offset = 0.0; offset < 1.0; offset += 0.01)
		BOOST_CHECK(day_of_week(jd.jd() + offset) == Monday);

	BOOST_CHECK(day_of_week(jd.jd() + 1.0) == Tuesday);
}
#endif