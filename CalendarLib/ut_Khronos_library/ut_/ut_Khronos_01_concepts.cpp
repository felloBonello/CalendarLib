/** @file ut_khronos_01_concepts.cpp

	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library concepts unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>



#if TEST_PHASE>=1
BOOST_AUTO_TEST_CASE(concept_am_pm_UDL) {
	PhaseList::instance().implements(1);
	using namespace khronos;
	BOOST_CHECK_EQUAL(12_am, 0);
	BOOST_CHECK_EQUAL(1_am, 1);
	BOOST_CHECK_EQUAL(12_pm, 12);
	BOOST_CHECK_EQUAL(1_pm, 13);
}
#endif



#if TEST_PHASE>=2
BOOST_AUTO_TEST_CASE(concept_time_of_day) {
	PhaseList::instance().implements(2);
	using namespace khronos;
	BOOST_CHECK_EQUAL(SECONDS_PER_DAY, 24 * 60 * 60);
	BOOST_CHECK_EQUAL(tod(12_am, 0, 0), 0.0);
	BOOST_CHECK_EQUAL(tod(12_pm, 1, 1.5), ((12*60+1)*60+1.5)/SECONDS_PER_DAY);
}
#endif



#if TEST_PHASE>=3
BOOST_AUTO_TEST_CASE(concept_CE_BCE_to_Gregorian_astro) {
	PhaseList::instance().implements(3);
	using namespace khronos;
	BOOST_CHECK_EQUAL(1975_CE, 1975);
	BOOST_CHECK_EQUAL(1975_BCE, -1974);
}
#endif
