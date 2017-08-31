/** @file ut_khronos_11_julian_class.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Julian Calendar class unit test.
	*/

#include <khronos.hpp>
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>
using namespace khronos;

#include <ctime>
using namespace std;



#if TEST_PHASE>=27
/* Default constructor initializes to current time. */
BOOST_AUTO_TEST_CASE(test_Julian_ctor_default) {
	PhaseList::instance().implements(27);
	time_t utcTime = time(NULL);
	Julian const	now;
	Julian const today(NOTIMEOFDAY);
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);

	Gregorian		localDateTime(
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



BOOST_AUTO_TEST_CASE(test_Julian_ctor_literal) {
	Julian const		epochJulian(-4712, January, 1);
	BOOST_CHECK(-4712 == epochJulian.year());
	BOOST_CHECK(January == epochJulian.month());
	BOOST_CHECK(1 == epochJulian.day());

	Julian const greatWar(1918, October, 29, 11, 11, 11);
	BOOST_CHECK(1918 == greatWar.year());
	BOOST_CHECK(October == greatWar.month());
	BOOST_CHECK(29 == greatWar.day());
	BOOST_CHECK(11 == greatWar.hour());
	BOOST_CHECK(11 == greatWar.minute());
	BOOST_CHECK(11 == greatWar.second());
}



BOOST_AUTO_TEST_CASE(test_Julian_ctor_from_Jd) {
	Julian g(Jd(-0.5));
	BOOST_CHECK_EQUAL(g.year(), -4712);
	BOOST_CHECK_EQUAL(g.month(), January);
	BOOST_CHECK_EQUAL(g.day(), 1);
	BOOST_CHECK_EQUAL(g.hour(), 0);
	BOOST_CHECK_EQUAL(g.minute(), 0);
	BOOST_CHECK_EQUAL(g.second(), 0);
}



BOOST_AUTO_TEST_CASE(test_Julian_cast_to_Jd) {
	Julian const	julianEpoch(-4712, January, 1);
	Jd je = julianEpoch;
	BOOST_CHECK_EQUAL(je.jd(), -0.5);
}



BOOST_AUTO_TEST_CASE(test_Julian_assignment_from_Jd) {
	Julian g;
	g = Jd(-0.5);
	BOOST_CHECK_EQUAL(g.year(), -4712);
	BOOST_CHECK_EQUAL(g.month(), January);
	BOOST_CHECK_EQUAL(g.day(), 1);
	BOOST_CHECK_EQUAL(g.hour(), 0);
	BOOST_CHECK_EQUAL(g.minute(), 0);
	BOOST_CHECK_EQUAL(g.second(), 0);
}



BOOST_AUTO_TEST_CASE(test_Julian_add_days) {
	Julian d(2000, January, 1);
	Julian res = d + days(10);
	BOOST_CHECK(res == Julian(2000, January, 11));
	res = res - days(10);
	BOOST_CHECK(res == d);
}



BOOST_AUTO_TEST_CASE(test_Julian_add_days_with_time) {
	Julian d(2000, January, 1, 12, 13, 14);
	Julian res = d + days(10);
	BOOST_CHECK(res == Julian(2000, January, 11, 12, 13, 14));
	res = res - days(10);
	BOOST_CHECK(res == d);
}



BOOST_AUTO_TEST_CASE(test_Julian_add_weeks) {
	Julian d(2000, JAN, 1);
	Julian res = d + weeks(10);
	BOOST_CHECK(d + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(d == res);
}



BOOST_AUTO_TEST_CASE(test_Julian_add_weeks_with_time) {
	Julian d(2000, JAN, 1, 6, 7, 8);
	Julian res = d + weeks(10);
	BOOST_CHECK(d + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(d == res);
}



BOOST_AUTO_TEST_CASE(test_Julian_add_months) {
	{	Julian start(2000, JAN, 1);
	Julian end(2000, FEB, 1);
	Julian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == start);
	}
	{	Julian start(2000, JAN, 1, 12, 13, 14);
	Julian end(2001, FEB, 1, 12, 13, 14);
	Julian res = start + months(13);
	BOOST_CHECK(end == res);
	res = end - months(13);
	BOOST_CHECK(res == start);
	}

	// shouldn't compile
	//start + months(1.2);
}



BOOST_AUTO_TEST_CASE(test_Julian_add_months_w_carry) {
	{	Julian start(2000, OCT, 1);
	Julian end(2001, FEB, 1);
	Julian res = start + months(4);
	BOOST_CHECK(end == res);
	res = end - months(4);
	BOOST_CHECK(res == start);
	}
	{	Julian start(2000, OCT, 1, 6, 7, 8);
	Julian end(2003, FEB, 1, 6, 7, 8);
	Julian res = start + months(28);
	BOOST_CHECK(end == res);
	res = end - months(28);
	BOOST_CHECK(res == start);
	}
}



BOOST_AUTO_TEST_CASE(test_Julian_add_month_leap) {
	{	Julian start(2000, February, 29);
	Julian end(2000, March, 29);
	Julian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == start);
	}
	{	Julian start(2000, January, 31, 6, 7, 8);
	Julian end(2000, February, 29, 6, 7, 8);
	Julian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == Julian(2000, January, 29, 6, 7, 8));
	}
}



BOOST_AUTO_TEST_CASE(test_Julian_add_years) {
	Julian date(2000, January, 1);
	Julian result = date + years(10);
	BOOST_CHECK(Julian(2010, January, 1) == result);
	result = result - years(10);
	BOOST_CHECK(result == date);

	// The following won't compile (we made the operator private)
	//result = date + years(10.4);
}



BOOST_AUTO_TEST_CASE(test_Julian_add_years_leapyear) {
	Julian d(2000, February, 29, 12, 13, 14);
	Julian later = d + years(2);
	BOOST_CHECK(Julian(2002, February, 28, 12, 13, 14) == later);
}



BOOST_AUTO_TEST_CASE(test_Julian_relational) {
	Julian low(2009, 1, 1);
	Julian high(2009, 12, 31);
	Julian copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
}



BOOST_AUTO_TEST_CASE(test_Julian_to_string) {
	BOOST_CHECK_EQUAL(Julian(1000, January, 1).to_string(), std::string("Monday, January 1 1000 AD, 12:00:00 am"));
	BOOST_CHECK_EQUAL(Julian(2000, February, 29, 12, 30, 11).to_string(), std::string("Monday, February 29 2000 AD, 12:30:11 pm"));
	BOOST_CHECK_EQUAL(Julian(2010, September, 12, 23, 45, 8).to_string(), std::string("Saturday, September 12 2010 AD, 11:45:08 pm"));
	BOOST_CHECK_EQUAL(Julian(-100, January, 1, 6, 7, 8).to_string(), std::string("Friday, January 1 101 BC, 6:07:08 am"));

	std::ostringstream oss;
	oss << Julian(2010, September, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(oss.str(), std::string("Saturday, September 12 2010 AD, 11:45:08 pm"));
}



BOOST_AUTO_TEST_CASE(test_Julian_element_functions) {
	Julian g(2010, September, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(year(g), 2010);
	BOOST_CHECK_EQUAL(month(g), September);
	BOOST_CHECK_EQUAL(day(g), 12);
	BOOST_CHECK_EQUAL(hour(g), 23);
	BOOST_CHECK_EQUAL(minute(g), 45);
	BOOST_CHECK_EQUAL(second(g), 8);
}

BOOST_AUTO_TEST_CASE(julian_differences) {
	Julian past(1858, 11, 16);
	Julian future(2132, 8, 31);

	BOOST_CHECK(future - past == 100002);
	BOOST_CHECK(past - future == -100002);

	Julian start(2000, 1, 1);
	Julian end(2001, 1, 1);

	BOOST_CHECK(end - start == 366);
	BOOST_CHECK(start - end == -366);
}
#endif