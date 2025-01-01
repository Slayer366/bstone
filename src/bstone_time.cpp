/*
BStone: A Source port of
Blake Stone: Aliens of Gold and Blake Stone: Planet Strike

Copyright (c) 1992-2013 Apogee Entertainment, LLC
Copyright (c) 2013-2021 Boris I. Bendovsky (bibendovsky@hotmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/


#include "bstone_time.h"

#if _WIN32
#include <windows.h>
#else
#include <time.h>
#endif // _WIN32

#include <string>

#include "bstone_exception.h"
#include "bstone_string_helper.h"


namespace bstone
{


class LocalDateTimeException :
	public Exception
{
public:
	explicit LocalDateTimeException(
		const char* message)
		:
		Exception{std::string{"MAKE_LOCAL_DATE_TIME"} + message}
	{
	}
}; // LocalDateTimeException

class LocalDateTimeStringException :
	public Exception
{
public:
	explicit LocalDateTimeStringException(
		const char* message)
		:
		Exception{std::string{"MAKE_LOCAL_DATE_TIME_STRING"} + message}
	{
	}
}; // LocalDateTimeStringException


DateTime make_local_date_time()
{
#if _WIN32
	SYSTEMTIME win32_date_time;

	::GetLocalTime(&win32_date_time);

	auto date_time = DateTime{};
	date_time.year = win32_date_time.wYear;
	date_time.month = win32_date_time.wMonth;
	date_time.day = win32_date_time.wDay;
	date_time.hours = win32_date_time.wHour;
	date_time.minutes = win32_date_time.wMinute;
	date_time.seconds = win32_date_time.wSecond;
	date_time.milliseconds = win32_date_time.wMilliseconds;

	return date_time;
#else
	struct ::timespec posix_tp;

	const auto clock_gettime_result = ::clock_gettime(CLOCK_REALTIME, &posix_tp);

	if (clock_gettime_result != 0)
	{
		throw LocalDateTimeException{"Failed to get clock time."};
	}

	struct ::tm posix_tm;

	const auto localtime_r_result = ::localtime_r(&posix_tp.tv_sec, &posix_tm);

	if (!localtime_r_result)
	{
		throw LocalDateTimeException{"Failed to get local time."};
	}

	const auto milliseconds = static_cast<int>(posix_tp.tv_nsec / 1'000'000);

	auto date_time = DateTime{};
	date_time.year = 1'900 + posix_tm.tm_year;
	date_time.month = 1 + posix_tm.tm_mon;
	date_time.day = posix_tm.tm_mday;
	date_time.hours = posix_tm.tm_hour;
	date_time.minutes = posix_tm.tm_min;
	date_time.seconds = posix_tm.tm_sec;
	date_time.milliseconds = milliseconds;

	return date_time;
#endif // _WIN32
}


// YYYYMMDD_hhmmss_sss
std::string make_local_date_time_string_screenshot_file_name(
	const DateTime& date_time)
{
	auto date_time_string = std::string{};
	date_time_string.reserve(19);
	date_time_string += StringHelper::make_left_padded_with_zero(date_time.year, 4);
	date_time_string += StringHelper::make_left_padded_with_zero(date_time.month, 2);
	date_time_string += StringHelper::make_left_padded_with_zero(date_time.day, 2);
	date_time_string += '_';
	date_time_string += StringHelper::make_left_padded_with_zero(date_time.hours, 2);
	date_time_string += StringHelper::make_left_padded_with_zero(date_time.minutes, 2);
	date_time_string += StringHelper::make_left_padded_with_zero(date_time.seconds, 2);
	date_time_string += '_';
	date_time_string += StringHelper::make_left_padded_with_zero(date_time.milliseconds, 3);

	return date_time_string;
}

std::string make_local_date_time_string(
	const DateTime& date_time,
	DateTimeStringFormat format)
{
	switch (format)
	{
		case DateTimeStringFormat::screenshot_file_name:
			return make_local_date_time_string_screenshot_file_name(date_time);

		default:
			throw LocalDateTimeStringException{"Unsupported format."};
	}
}


} // bstone
