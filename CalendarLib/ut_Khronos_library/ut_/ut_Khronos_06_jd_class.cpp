	/** @file ut_khronos_06_jd_class.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Julian Day unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <ctime>
using namespace khronos;
using namespace std;



#if TEST_PHASE>=10
BOOST_AUTO_TEST_CASE(Jdn_differences) {
	PhaseList::instance().implements(10);
	Jd past(1000);
	Jd future(2000);

	BOOST_CHECK(future - past == 1000);
	BOOST_CHECK(past - future == -1000);
}
#endif



#if TEST_PHASE>=11
/* Default constructor initializes to current time. */
BOOST_AUTO_TEST_CASE(test_Jd_ctor_default) {
	PhaseList::instance().implements(11);
	time_t utcTime = time(NULL);
	Jd const nowJD;

	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);
	jd_t jd = gregorian_to_jd(
		tmLocal.tm_year + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour), minute_t(tmLocal.tm_min), second_t(tmLocal.tm_sec));

	BOOST_CHECK_EQUAL(nowJD, jd);
}



/* Default constructor initializes to current time suppressing time of day.*/
BOOST_AUTO_TEST_CASE(test_Jd_ctor_default_no_time_of_day) {
	time_t utcTime = time(NULL);
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);
	Jd const nowJD(WTIMEOFDAY);
	Jd const nowJDN(NOTIMEOFDAY);

	jd_t jdn = gregorian_to_jd(tmLocal.tm_year + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday));
	BOOST_CHECK_EQUAL(nowJDN.jd(), jdn);

	jd_t jd = gregorian_to_jd(
		tmLocal.tm_year + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour), minute_t(tmLocal.tm_min), second_t(tmLocal.tm_sec));
	BOOST_CHECK_EQUAL(nowJD, jd);
}



/** Test literal constructors. */
BOOST_AUTO_TEST_CASE(test_Jd_ctor_literal) {
	Jd const epochJdn(-0.5);
	BOOST_CHECK(-0.5 == epochJdn);
}
#endif // TEST_PHASE 11



#if TEST_PHASE>=12
BOOST_AUTO_TEST_CASE(test_Jd_add_days) {
	PhaseList::instance().implements(12);
	Jd d(2000);
	Jd res = d + days(10);
	BOOST_CHECK(res.jd() == 2010);
	res = res - days(10);
	BOOST_CHECK(res.jd() == 2000);
}



BOOST_AUTO_TEST_CASE(test_Jd_add_weeks) {
	Jd d(2000);
	Jd res = d + weeks(10);
	BOOST_CHECK(d + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(d == res);
}



BOOST_AUTO_TEST_CASE(test_Jd_add_years) {
	Jd d = 2000;
	double const astroYears = 10.4;
	Jd res = d + years(astroYears);
	BOOST_CHECK(2000 + EARTH_ORBITAL_PERIOD_DAYS * astroYears == res);
	res = d - years(astroYears);
	BOOST_CHECK(2000 - EARTH_ORBITAL_PERIOD_DAYS * astroYears == res);
}
#endif



#if TEST_PHASE>=13
BOOST_AUTO_TEST_CASE(test_Jd_day_of_week) {
	PhaseList::instance().implements(13);
	Gregorian g(2012, September, 24);  // a monday

	BOOST_CHECK(day_of_week(g) == Monday);
}
#endif



#if TEST_PHASE>=14
BOOST_AUTO_TEST_CASE(Test_Jd_relational) {
	PhaseList::instance().implements(14);
	Jd low(2009);
	Jd high(2010);
	Jd copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
}
#endif



#if TEST_PHASE>=15
BOOST_AUTO_TEST_CASE(test_Jd_to_string) {
	PhaseList::instance().implements(15);
	BOOST_CHECK_EQUAL(Jd(0).to_string(), std::string("JD 0"));
	BOOST_CHECK_EQUAL(Jd(10000).to_string(), std::string("JD 10000"));
	BOOST_CHECK_EQUAL(Jd(-10).to_string(), std::string("JD -10"));

	std::ostringstream oss;
	oss << Jd(0.5);
	BOOST_CHECK_EQUAL(oss.str(), std::string("JD 0.5"));
}
#endif