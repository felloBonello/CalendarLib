#ifndef __ISLAMIC_HPP__
#define __ISLAMIC_HPP__

#include "khronos/def.hpp"
#include "khronos/julian_day.hpp"
#include <string>
#include <array>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iomanip>


namespace khronos
{
	// constants
	jd_t const ISLAMIC_EPOCH = 1948439.5;

	enum islamic_month_codes {
		Muharram = 1, Safar, RabialAwwal,
		RabiathThani, JumadaIUla, JumadatTania, Rajab, Shaban, Ramadan, Shawwal,
		DhulQadah, DhulHijja
	};

	// define it inline so that way it will do a code replacement in the 
	// gregorian_to_jd function in that .cpp file
	bool is_islamic_leapyear(year_t year);

	// conversion functions
	jd_t islamic_to_jd(year_t year, month_t month, day_t day);
	jd_t islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_islamic(jdn_t jdn, year_t &year, month_t &month, day_t &day);
	void jd_to_islamic(jdn_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);


	// Gregorian Class derives from our base calendar class
	class Islamic : public Calendar
	{
		void from_jd(jd_t jd) { jd_to_islamic(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return islamic_to_jd(year_, month_, day_, hour_, minute_, second_); }

		string getMonthName()
		{
			array<string, 13> names = { "", "Muharram", "Safar", "Rabi'al-Awwal",
				"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
				"Dhu I-Qa'da", "Dhu I-Hijja" };
			return names[month_];
		}

		string getWeekDay()
		{
			array<string, 7> names = { "alth-thalatha", "al-'ahad", "al-'arb`a'", "al-'ithnayn", "al-jum`a", "as-sabt", "al-khamis" };
			return names[day_of_week(Jd(to_jd()))];
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
		Islamic();
		// Constructors
		Islamic(year_t y, month_t m, day_t d) :Calendar(y, m, d) {}
		Islamic(year_t y, month_t m, day_t d, hour_t h, minute_t mi, second_t s);
		Islamic(Jd const& jd) { from_jd(jd.jd()); }
		// implicit operator
		// Allows Jd jd = g;
		operator Jd () const { return Jd(to_jd()); }
		// Assignment operator converts from Jd type to Gregorian type
		string to_string()
		{
			string d = std::to_string(day_);
			string y = std::to_string(year_);

			return  (getWeekDay() + ", " + getMonthName() + " " + d + " " + y + ", " + formatTime());
		}

		Islamic& operator = (Jd const& jd)
		{
			from_jd(jd.jd());
			return *this;
		}

		~Islamic() {}
	};

	inline string islamic_month_name(month_t i)
	{
		array<string, 13> names = { "", "Muharram", "Safar", "Rabi'al-Awwal",
			"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
			"Dhu I-Qa'da", "Dhu I-Hijja" };
		return names[i];
	}

	inline int islamic_days_in_month(month_t m, bool isLeapYear)
	{
		int num = 0;
		if (isLeapYear && m == 12)
			num = 30;
		else
			num = (m % 2 == 0) ? (29) : (30);
		return num;
	}

	inline Islamic operator + (Islamic const& dt, packaged_month pm) {
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
		int d = min(day, islamic_days_in_month(newMonth, is_islamic_leapyear(newYear)));
		day_t newDay = static_cast<day_t>(d);
		return Islamic(newYear, newMonth, newDay, dt.hour(), dt.minute(), dt.second());
	}

	inline Islamic operator - (Islamic const& dt, packaged_month pm) {
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
		int d = min(day, islamic_days_in_month(newMonth, is_islamic_leapyear(newYear)));
		day_t newDay = static_cast<day_t>(d);
		return Islamic(newYear, newMonth, newDay, dt.hour(), dt.minute(), dt.second());
	}

	inline Islamic operator + (Islamic const& g, packaged_year years)
	{
		year_t y = g.year() + static_cast<year_t>(years.nYears_);
		month_t m = g.month();
		day_t d = g.day();

		if (m == 12 && d == 30 && !is_islamic_leapyear(y)) 
			d = 29;

		return Islamic(y, m, d, g.hour(), g.minute(), g.second());
	}
	inline Islamic operator - (Islamic const& g, packaged_year years) {
		year_t y = g.year() - static_cast<year_t>(years.nYears_);
		month_t m = g.month();
		day_t d = g.day();

		if (m == 12 && d == 30 && !is_islamic_leapyear(y))
			d = 29;

		return Islamic(y, m, d, g.hour(), g.minute(), g.second());
	}

	std::ostream& operator << (std::ostream& os, Islamic const& g);

}


#endif
