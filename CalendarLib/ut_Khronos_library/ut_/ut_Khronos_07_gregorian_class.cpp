/** @file ut_khronos_07_gregorian_class.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Gregorian class unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
#include <ctime>
using namespace khronos;



#if TEST_PHASE>=16
BOOST_AUTO_TEST_CASE(gregorian_differences) {
	PhaseList::instance().implements(16);
	Gregorian past(1858, 11, 16);
	Gregorian future(2132, 8, 31);

	BOOST_CHECK(future - past == 100000);
	BOOST_CHECK(past - future == -100000);

	Gregorian start(2000, 1, 1);
	Gregorian end(2001, 1, 1);

	BOOST_CHECK(end - start == 366);
	BOOST_CHECK(start - end == -366);
}
#endif





#if TEST_PHASE>=17
/* Default constructor initializes to current time. */
BOOST_AUTO_TEST_CASE(test_Gregorian_ctor_default) {
	PhaseList::instance().implements(17);
	time_t utcTime = time(NULL);
	Gregorian const now;
	Gregorian const today(NOTIMEOFDAY);
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);

	Gregorian localDateTime(
		year_t(tmLocal.tm_year + 1900),
		month_t(tmLocal.tm_mon + 1),
		day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour),
		minute_t(tmLocal.tm_min),
		second_t(tmLocal.tm_sec)
		);

	Gregorian localDate(
		year_t(tmLocal.tm_year + 1900),
		month_t(tmLocal.tm_mon + 1),
		day_t(tmLocal.tm_mday)
		);

	BOOST_CHECK(localDateTime == now);
	BOOST_CHECK(localDate == today);
}



BOOST_AUTO_TEST_CASE(test_gregorian_ctor_literal) {
	Gregorian const	julianEpoch(-4713, November, 24);
	BOOST_CHECK(-4713 == julianEpoch.year());
	BOOST_CHECK(November == julianEpoch.month());
	BOOST_CHECK(24 == julianEpoch.day());

	Gregorian const greatWar(1918, NOV, 11, 11, 11, 11);
	BOOST_CHECK(1918 == greatWar.year());
	BOOST_CHECK(November == greatWar.month());
	BOOST_CHECK(11 == greatWar.day());
	BOOST_CHECK(11 == greatWar.hour());
	BOOST_CHECK(11 == greatWar.minute());
	BOOST_CHECK(11 == greatWar.second());
}



BOOST_AUTO_TEST_CASE(test_Gregorian_ctor_from_Jd) {
	Gregorian g(Jd(-0.5));
	BOOST_CHECK_EQUAL(g.year(), -4713);
	BOOST_CHECK_EQUAL(g.month(), November);
	BOOST_CHECK_EQUAL(g.day(), 24);
	BOOST_CHECK_EQUAL(g.hour(), 0);
	BOOST_CHECK_EQUAL(g.minute(), 0);
	BOOST_CHECK_EQUAL(g.second(), 0);
}
#endif



#if TEST_PHASE>=18
BOOST_AUTO_TEST_CASE(test_Gregorian_cast_to_Jd) {
	PhaseList::instance().implements(18);
	Gregorian const	julianEpoch(-4713, November, 24);
	Jd je = julianEpoch;
	BOOST_CHECK_EQUAL(je.jd(), -0.5);
}



BOOST_AUTO_TEST_CASE(test_Gregorian_assignment_from_Jd) {
	Gregorian g;
	g = Jd(-0.5);
	BOOST_CHECK_EQUAL(g.year(), -4713);
	BOOST_CHECK_EQUAL(g.month(), November);
	BOOST_CHECK_EQUAL(g.day(), 24);
	BOOST_CHECK_EQUAL(g.hour(), 0);
	BOOST_CHECK_EQUAL(g.minute(), 0);
	BOOST_CHECK_EQUAL(g.second(), 0);
}
#endif



#if TEST_PHASE>=19
BOOST_AUTO_TEST_CASE(test_Gregorian_add_days) {
	PhaseList::instance().implements(19);
	Gregorian date(2000, January, 1);
	Gregorian res = date + days(10);
	BOOST_CHECK(res == Gregorian(2000, January, 11));
	res = res - days(10);
	BOOST_CHECK(res == date);
}



BOOST_AUTO_TEST_CASE(test_Gregorian_add_days_with_time) {
	Gregorian date(2000, January, 1, 12, 13, 14);
	Gregorian res = date + days(10);
	BOOST_CHECK(res == Gregorian(2000, January, 11, 12, 13, 14));
	res = res - days(10);
	BOOST_CHECK(res == date);
}



BOOST_AUTO_TEST_CASE(test_Gregorian_add_weeks) {
	Gregorian date(2000, JAN, 1);
	Gregorian res = date + weeks(10);
	BOOST_CHECK(date + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(date == res);
}



BOOST_AUTO_TEST_CASE(test_Gregorian_add_weeks_with_time) {
	Gregorian date(2000, JAN, 1, 6, 7, 8);
	Gregorian res = date + weeks(10);
	BOOST_CHECK(date + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(date == res);
}
#endif



#if TEST_PHASE>=20
BOOST_AUTO_TEST_CASE(test_Gregorian_add_months) {
	PhaseList::instance().implements(20);
	{	Gregorian start(2000, JAN, 1);
	Gregorian end(2000, FEB, 1);
	Gregorian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == start);
	}
	{	Gregorian start(2000, JAN, 1, 12, 13, 14);
	Gregorian end(2001, FEB, 1, 12, 13, 14);
	Gregorian res = start + months(13);
	BOOST_CHECK(end == res);
	res = end - months(13);
	BOOST_CHECK(res == start);
	}

	// shouldn't compile
	// start + months(1.2);
}


BOOST_AUTO_TEST_CASE(test_Gregorian_add_months_w_carry) {

	{	Gregorian start(2000, OCT, 1);
	Gregorian end(2001, FEB, 1);
	Gregorian res = start + months(4);
	BOOST_CHECK(end == res);
	res = end - months(4);
	BOOST_CHECK(res == start);
	}
	{	Gregorian start(2000, OCT, 1, 6, 7, 8);
	Gregorian end(2003, FEB, 1, 6, 7, 8);
	Gregorian res = start + months(28);
	BOOST_CHECK(end == res);
	res = end - months(28);
	BOOST_CHECK(res == start);
	}
}



BOOST_AUTO_TEST_CASE(test_Gregorian_add_month_leap) {

	{	Gregorian start(2000, February, 29, 12, 13, 14);
	Gregorian end(2000, March, 29, 12, 13, 14);
	Gregorian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == start);
	}
	{	Gregorian start(2000, January, 31, 6, 7, 8);
	Gregorian end(2000, February, 29, 6, 7, 8);
	Gregorian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == Gregorian(2000, January, 29, 6, 7, 8));
	}
}
#endif


#if TEST_PHASE>=21
BOOST_AUTO_TEST_CASE(test_Gregorian_add_years) {
	PhaseList::instance().implements(21);
	Gregorian date(2000, January, 1, 6, 7, 8);
	Gregorian res = date + years(10);
	BOOST_CHECK(Gregorian(2010, January, 1, 6, 7, 8) == res);
	res = res - years(10);
	BOOST_CHECK(res == date);

	// The following won't compile (we made the operator private)
	//res = date + years(10.4);
}



BOOST_AUTO_TEST_CASE(test_Gregorian_add_years_leapyear) {
	Gregorian date(2000, February, 29, 12, 13, 14);
	Gregorian later = date + years(2);
	BOOST_CHECK(Gregorian(2002, February, 28, 12, 13, 14) == later);
}
#endif



#if TEST_PHASE>=22
BOOST_AUTO_TEST_CASE(test_Gregorian_relational) {
	PhaseList::instance().implements(22);
	Gregorian low(2009, January, 1);
	Gregorian high(2009, December, 31);
	Gregorian copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
}



BOOST_AUTO_TEST_CASE(test_Gregorian_element_functions) {
	Gregorian g(2010, September, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(year(g), 2010);
	BOOST_CHECK_EQUAL(month(g), September);
	BOOST_CHECK_EQUAL(day(g), 12);
	BOOST_CHECK_EQUAL(hour(g), 23);
	BOOST_CHECK_EQUAL(minute(g), 45);
	BOOST_CHECK_EQUAL(second(g), 8);
}
#endif



#if TEST_PHASE>=23
BOOST_AUTO_TEST_CASE(test_Gregorian_to_string) {
	PhaseList::instance().implements(23);
	BOOST_CHECK_EQUAL(Gregorian(1000, January, 1).to_string(), std::string("Wednesday, January 1 1000 CE, 12:00:00 am"));
	BOOST_CHECK_EQUAL(Gregorian(2000, February, 29, 12, 30, 11).to_string(), std::string("Tuesday, February 29 2000 CE, 12:30:11 pm"));
	BOOST_CHECK_EQUAL(Gregorian(2010, September, 12, 23, 45, 8).to_string(), std::string("Sunday, September 12 2010 CE, 11:45:08 pm"));
	BOOST_CHECK_EQUAL(Gregorian(101_BCE, January, 1, 6, 7, 8).to_string(), std::string("Monday, January 1 101 BCE, 6:07:08 am"));

	std::ostringstream oss;
	oss << Gregorian(2010, September, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(oss.str(), std::string("Sunday, September 12 2010 CE, 11:45:08 pm"));
}
#endif

