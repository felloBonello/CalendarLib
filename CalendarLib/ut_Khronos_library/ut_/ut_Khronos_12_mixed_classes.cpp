/** @file ut_khronos_12_mixed_classes.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library mixed classes unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>



#if TEST_PHASE>=28
BOOST_AUTO_TEST_CASE(mixed_differences) {
	PhaseList::instance().implements(28);
	using namespace khronos;
	Gregorian low(2000);
	Jd high = Jd(low).jd() + 1;
	Julian copyLow(low);

	BOOST_CHECK(high - low == 1);
	BOOST_CHECK(low - high == -1);
	BOOST_CHECK(low - copyLow == 0);
	BOOST_CHECK(copyLow - low == 0);
}



BOOST_AUTO_TEST_CASE(mixed_relational) {
	using namespace khronos;
	Gregorian low(2000);
	Jd high = Jd(low).jd() + 1;
	Julian copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
}



/**	Base objects. */
khronos::Jd const			epochJdn(-0.5);
khronos::Julian const		epochJulian(-4712, 1, 1);
khronos::Gregorian const	epochGregorian(-4713, 11, 24);



/** Test assignment to Jdn conversions. */
BOOST_AUTO_TEST_CASE(assignment_conversion_to_jdn_tests) {
	using namespace khronos;

	{	Jd jdn;
	jdn = epochJulian;
	BOOST_CHECK(jdn == epochJulian);
	}
	{	Jd jdn;
	jdn = epochGregorian;
	BOOST_CHECK(jdn == epochGregorian);
	}
	{	Jd jdn;
	jdn = epochJdn;
	BOOST_CHECK(jdn == epochJdn);
	}
}



/** Test assignment to Gregorian conversions. */
BOOST_AUTO_TEST_CASE(assignment_conversion_to_gregorian_tests) {
	using namespace khronos;
	Gregorian greg;

	{	Gregorian greg;
	greg = epochJulian;
	BOOST_CHECK(greg == epochJulian);
	}
	{	Gregorian greg;
	greg = epochGregorian;
	BOOST_CHECK(greg == epochGregorian);
	}
	{	Gregorian greg;
	greg = epochJdn;
	BOOST_CHECK(greg == epochJdn);
	}
}



/** Test assignment to Julian conversions. */
BOOST_AUTO_TEST_CASE(assignment_conversion_to_julian_tests) {
	using namespace khronos;

	Julian julian;

	{	Julian julian;
	julian = epochJulian;
	BOOST_CHECK(julian == epochJulian);
	}
	{	Julian julian;
	julian = epochGregorian;
	BOOST_CHECK(julian == epochGregorian);
	}
	{	Julian julian;
	julian = epochJdn;
	BOOST_CHECK(julian == epochJdn);
	}
}
#endif


#if TEST_PHASE>=34
/** Test now */
BOOST_AUTO_TEST_CASE(test_defaults) {
	using namespace khronos;

	Gregorian gNow(NOTIMEOFDAY);
	Julian jNow(NOTIMEOFDAY);
	//Islamic iNow(NOTIMEOFDAY);
	//Hebrew hNow(NOTIMEOFDAY);
	Jd now(NOTIMEOFDAY);

	BOOST_CHECK(gNow == jNow);
	//BOOST_CHECK(iNow == hNow);
}
#endif