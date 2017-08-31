#ifndef __JULIAN_DAY_HPP__
#define __JULIAN_DAY_HPP__
#include "khronos/def.hpp"
#include <sstream>
#include <math.h>
#include <array>
namespace khronos
{

	// constexpr
	constexpr long long operator ""_BC(unsigned long long y)
	{
		return -(long long)y + 1;
	}
	constexpr long long operator ""_AD(unsigned long long y)
	{
		return (long long)y;
	}

	constexpr int operator ""_am(unsigned long long y)
	{
		return static_cast<int>((y == 12) ? (0) : (y));
	}
	constexpr int operator ""_pm(unsigned long long y)
	{
		return static_cast<int>((y == 12) ? (12) : (y + 12));
	}

	class Jd
	{
	private:
		jd_t jd_;
	public:
		// default constructor - sets jd value to the current date and time
		Jd();
		// Constructor from a Jd
		Jd(jd_t j) :jd_(j) {}
		// getter
		jd_t jd() const { return jd_; }
		string to_string()
		{
			return "JD " + std::to_string(int(jd_));
		}

		~Jd() {}
	};

	inline int julian_days_in_month(month_t m, bool isLeapYear)
	{
		if (isLeapYear && m == 2)
			return 29;
		else if (!isLeapYear && m == 2)
			return 28;

		return ((m == 4 || m == 6 || m == 9 || m == 11) ? 30 : 31);
	}

	bool is_julian_leapyear(year_t year);
	jd_t julian_to_jd(year_t y, month_t m, day_t d);
	jd_t julian_to_jd(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s);
	void jd_to_julian(jdn_t jdn, year_t &y, month_t &m, day_t &d);
	void jd_to_julian(jdn_t jdn, year_t &y, month_t &m, day_t &d, hour_t &h, minute_t &mi, second_t &s);

	inline string julian_month_name(month_t i)
	{
		array<string, 13> names = { "", "January", "February", "March",
			"April", "May", "June", "July", "August", "September", "October",
			"November", "December" };
		return names[i];
	}

	inline string julian_short_month_name(month_t i)
	{
		array<string, 13> names = { "", "JAN", "FEB", "MAR",
			"APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT",
			"NOV", "DEC" };
		return names[i];
	}

	inline civil_weekday_codes_long day_of_week(Jd date)
	{
		return  civil_weekday_codes_long(int(fmod((date.jd() + 0.5), 7)));
	}

	inline jdn_t tod(hour_t hour, minute_t min, second_t sec) { return ((sec + 60 * (min + 60 * hour)) / (24 * 60 * 60)); }

	inline double tod(jdn_t date) { return (date + 0.5) - floor(date + 0.5); }

	inline jdn_t jd_to_jdn(jd_t jd)
	{
		return floor(jd + 0.5);
	}

	inline void hms(jdn_t date, hour_t& hour, minute_t& min, second_t& sec)
	{
		double timeOfDay = tod(date);
		int secondsInDay = static_cast<int>(floor(timeOfDay * 24 * 60 * 60 + 0.5));
		hour = secondsInDay / (60 * 60);
		min = (secondsInDay / 60) % 60;
		sec = secondsInDay % 60;
	}

	/* Day addition/subtraction. */
	struct packaged_day
	{
		day_t nDays_;
		packaged_day(day_t d) : nDays_(d) {};
	};
	inline packaged_day days(day_t d) { return packaged_day(d); }
	inline Jd operator +(Jd const& jdn, packaged_day const& pd)
	{
		return Jd(jdn.jd() + pd.nDays_);
	}
	inline Jd operator -(Jd const& jdn, packaged_day const& pd)
	{
		return Jd(jdn.jd() - pd.nDays_);
	}

	/* Week addition/subtraction. */
	struct packaged_week {
		day_t nWeeks_;
		packaged_week(day_t w) :nWeeks_(w) {}
	};
	inline packaged_week weeks(day_t w) { return packaged_week(w); }
	inline Jd operator + (Jd const& jd, packaged_week weeks) {
		return Jd(jd.jd() + 7 * weeks.nWeeks_);
	}
	inline Jd operator - (Jd const& jd, packaged_week weeks) {
		return Jd(jd.jd() - 7 * weeks.nWeeks_);
	}

	/* Month addition/subtraction. */
	struct packaged_month
	{
		month_t nMonths_;
		packaged_month(month_t m) : nMonths_(m) {};
	};
	inline packaged_month months(month_t m) { return packaged_month(m); }
	
	/* Year addition/subtraction. */
	struct packaged_year
	{
		double nYears_;
		packaged_year(double y) : nYears_(y) { };
	};
	inline packaged_year years(double y) { return packaged_year(y); }
	
	inline Jd operator + (Jd const& jd, packaged_year years) {
		return Jd(jd.jd() + EARTH_ORBITAL_PERIOD_DAYS * years.nYears_);
	}
	inline Jd operator - (Jd const& jd, packaged_year years) {
		return Jd(jd.jd() - EARTH_ORBITAL_PERIOD_DAYS * years.nYears_);
	}

	inline jd_t operator - (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() - rhs.jd();
	}

	inline jd_t operator + (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() + rhs.jd();
	}

	inline Jd operator+(Jd const& lhs, jd_t rhs) {
		return Jd(lhs.jd() + rhs);
	}

	inline Jd operator-(Jd const& lhs, jd_t rhs) {
		return Jd(lhs.jd() - rhs);
	}

	// RELATIONAL OPERATORS
	inline bool operator == (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() == rhs.jd();
	}
	inline bool operator != (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() != rhs.jd();
	}

	inline bool operator < (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() < rhs.jd();
	}

	inline bool operator > (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() > rhs.jd();
	}

	inline bool operator <= (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() <= rhs.jd();
	}

	inline bool operator >= (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() >= rhs.jd();
	}

	// STREAM OPERATOR
	ostream& operator << (ostream& os, Jd const& jd);

	jdn_t const WTIMEOFDAY = Jd().jd();
	jdn_t const NOTIMEOFDAY = floor(Jd().jd() + 0.5) - 0.5;
}

#endif
