#ifndef __JULIAN_HPP__
#define __JULIAN_HPP__
#include "khronos/def.hpp"
#include <cmath>

namespace khronos{
	jd_t const JULIAN_EPOCH = 1721423.5;

	class Julian : public Calendar
	{
		void from_jd(jd_t jd) { jd_to_julian(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return julian_to_jd(year_, month_, day_, hour_, minute_, second_); }

		string getMonthName()
		{
			array<string, 13> names = { "", "January", "February", "March",
				"April", "May", "June", "July", "August", "September", "October",
				"November", "December" };
			return names[month_];
		}

		string getWeekDay()
		{
			array<string, 7> names = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
			return names[day_of_week(Jd(to_jd()))];
		}

		string formatYear()
		{
			string y;
			if (year_ < 0)

				y = std::to_string(abs(year_) + 1) + " BC";
			else
				y = std::to_string(year_) + " AD";
			return y;
		}

		string formatTime()
		{
			int adjustedHour;
			string ampm;

			if (hour_ == 0)
			{
				adjustedHour = (hour_ + 12);
				ampm = " am";
			}
			else if (hour_ > 12)
			{
				adjustedHour = (hour_ - 12);
				ampm = " pm";
			}
			else if (hour_ == 12)
			{
				adjustedHour = hour_;
				ampm = " pm";
			}
			else if (hour_ < 12)
			{
				adjustedHour = hour_;
				ampm = " am";
			}
			ostringstream stringStream;
			stringStream << adjustedHour << ":" << setw(2) << setfill('0') << minute_ << ":" << setw(2) << setfill('0') << second_ << ampm;
			string copyOfStr = stringStream.str();
			return copyOfStr;
		}
	public:
		// default constructor
		Julian();
		// Constructors
		Julian(year_t y, month_t m, day_t d) :Calendar(y, m, d) {}
		Julian(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s);

		Julian(jd_t const& jd) { from_jd(jd); }
		Julian(Jd const& jd) { from_jd(jd.jd()); }

		string to_string()
		{
			string d = std::to_string(day_);
			string h = std::to_string(hour_);
			string m = std::to_string(minute_);
			string s = std::to_string(second_);

			return  (getWeekDay() + ", " + getMonthName() + " " + d + " " + formatYear() + ", " + formatTime());
		}

		operator Jd () const { return Jd(to_jd()); }


		Julian& operator = (Jd const& jd)
		{
			from_jd(jd.jd());
			return *this;
		}

		~Julian() {}
	};

	
	inline Julian operator + (Julian const& dt, packaged_month pm) {
		long long year = static_cast<long long>(dt.year());
		long long month = static_cast<long long>(dt.month());
		int day = static_cast<int>(dt.day());

		long long y = year + pm.nMonths_ / 12;
		long long m = month + pm.nMonths_ % 12;
		long long adjust = (m - 1) / 12 + (m - 12) / 12;
		y = y + adjust;
		m = m - adjust * 12;

		year_t newYear = static_cast<year_t>(y);
		month_t newMonth = static_cast<month_t>(m);
		int d = min(day, gregorian_days_in_month(newMonth, is_gregorian_leapyear(newYear)));
		day_t newDay = static_cast<day_t>(d);
		return Julian(newYear, newMonth, newDay, dt.hour(), dt.minute(), dt.second());
	}

	inline Julian operator - (Julian const& dt, packaged_month pm) {
		long long year = static_cast<long long>(dt.year());
		long long month = static_cast<long long>(dt.month());
		int day = static_cast<int>(dt.day());

		long long y = year - pm.nMonths_ / 12;
		long long m = month - pm.nMonths_ % 12;
		long long adjust = (m - 1) / 12 + (m - 12) / 12;
		y = y - adjust;
		m = m + adjust * 12;

		year_t newYear = static_cast<year_t>(y);
		month_t newMonth = static_cast<month_t>(m);
		int d = min(day, gregorian_days_in_month(newMonth, is_julian_leapyear(newYear)));
		day_t newDay = static_cast<day_t>(d);
		return Julian(newYear, newMonth, newDay, dt.hour(), dt.minute(), dt.second());
	}

	inline Julian operator + (Julian const& g, packaged_year years)
	{
		year_t y = g.year() + static_cast<year_t>(years.nYears_);
		month_t m = g.month();
		day_t d = g.day();

		if (m == February && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Julian(y, m, d, g.hour(), g.minute(), g.second());
	}
	inline Julian operator - (Julian const& g, packaged_year years) {
		year_t y = g.year() - static_cast<year_t>(years.nYears_);
		month_t m = g.month();
		day_t d = g.day();

		if (m == February && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Julian(y, m, d, g.hour(), g.minute(), g.second());
	}

	std::ostream& operator << (std::ostream& os, Julian const& g);

}
#endif
