/** @file ut_khronos_19_hebrew_class.cpp
	@author Garth Santor
	@date 2015-09-21
	@version 1.0.0
	@note C++ 11/vc14
	@brief Khronos library Hebew Calendar class unit test.
*/

#include <khronos.hpp>
using namespace khronos;
#include <ctime>
using namespace std;
#include "ut_phase_list.hpp"
#include <boost/test/auto_unit_test.hpp>



#if TEST_PHASE>=34
/** Default constructor initializes to current time. */
BOOST_AUTO_TEST_CASE(test_Hebrew_ctor_default) {
	PhaseList::instance().implements(34);
	time_t utcTime = time(NULL);
	Hebrew const now;
	Hebrew const today(NOTIMEOFDAY);
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

	// Hebrew days start at noon
	Gregorian localDate(
		year_t(tmLocal.tm_year + 1900),
		month_t(tmLocal.tm_mon + 1),
		day_t(tmLocal.tm_mday)
		);

	BOOST_CHECK(localDateTime == now);
	BOOST_CHECK(localDate == today);
}



BOOST_AUTO_TEST_CASE(test_Hebrew_ctor_literal) {
	Hebrew const	hebrewEpoch(1, Nisan, 1);
	BOOST_CHECK(1 == hebrewEpoch.year());
	BOOST_CHECK(Nisan == hebrewEpoch.month());
	BOOST_CHECK(1 == hebrewEpoch.day());

	Hebrew const aDay(5774, Heshvan, 16, 12, 30, 45);
	BOOST_CHECK(5774 == aDay.year());
	BOOST_CHECK(Heshvan == aDay.month());
	BOOST_CHECK(16 == aDay.day());
	BOOST_CHECK(12 == aDay.hour());
	BOOST_CHECK(30 == aDay.minute());
	BOOST_CHECK(45 == aDay.second());
}



BOOST_AUTO_TEST_CASE(test_Hebrew_ctor_from_Jd) {
	Hebrew i(Jd(0.0));
	BOOST_CHECK_EQUAL(i.year(), -952);
	BOOST_CHECK_EQUAL(i.month(), Teveth);
	BOOST_CHECK_EQUAL(i.day(), 21);
	BOOST_CHECK_EQUAL(i.hour(), 12);
	BOOST_CHECK_EQUAL(i.minute(), 0);
	BOOST_CHECK_EQUAL(i.second(), 0);
}



BOOST_AUTO_TEST_CASE(test_Hebrew_cast_to_Jd) {
	Hebrew const	i(-952, Teveth, 21, 12, 0, 0);
	Jd je = i;
	BOOST_CHECK_EQUAL(je.jd(), 0.0);
}



BOOST_AUTO_TEST_CASE(test_Hebrew_assignment_from_Jd) {
	Hebrew i;
	i = Jd(0.0);
	BOOST_CHECK_EQUAL(i.year(), -952);
	BOOST_CHECK_EQUAL(i.month(), Teveth);
	BOOST_CHECK_EQUAL(i.day(), 21);
	BOOST_CHECK_EQUAL(i.hour(), 12);
	BOOST_CHECK_EQUAL(i.minute(), 0);
	BOOST_CHECK_EQUAL(i.second(), 0);
}



BOOST_AUTO_TEST_CASE(test_Hebrew_add_days) {
	Hebrew date(5774, Heshvan, 16);
	Hebrew res = date + days(100);
	BOOST_CHECK(res == Hebrew(5774, Shevat, 27));
	res = res - days(100);
	BOOST_CHECK(res == date);
}



BOOST_AUTO_TEST_CASE(test_Hebrew_add_weeks) {
	Hebrew date(5774, Heshvan, 16);
	Hebrew res = date + weeks(10);
	BOOST_CHECK(date + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(date == res);
}



BOOST_AUTO_TEST_CASE(test_Hebrew_relational) {
	Hebrew low(5774, Teveth, 1);
	Hebrew high(5774, Shevat, 29);
	Hebrew copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
}



BOOST_AUTO_TEST_CASE(test_Hebrew_to_string) {
	BOOST_CHECK_EQUAL(Hebrew(1000, Nisan, 1).to_string(), std::string("Nisan 1 1000, 12:00:00 am"));
	BOOST_CHECK_EQUAL(Hebrew(2000, Shevat, 29, 12, 0, 0).to_string(), std::string("Shevat 29 2000, 12:00:00 pm"));
	BOOST_CHECK_EQUAL(Hebrew(2010, Heshvan, 12, 23, 45, 8).to_string(), std::string("Heshvan 12 2010, 11:45:08 pm"));
	BOOST_CHECK_EQUAL(Hebrew(-100, Nisan, 1, 6, 7, 8).to_string(), std::string("Nisan 1 -100, 6:07:08 am"));

	std::ostringstream oss;
	oss << Hebrew(2010, Heshvan, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(oss.str(), std::string("Heshvan 12 2010, 11:45:08 pm"));
}
#endif