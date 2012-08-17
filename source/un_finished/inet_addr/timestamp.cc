#include "timestamp.h"


#include <stdio.h>


//#include <boost/static_assert.hpp>

#ifdef _MSC_VER
#define snprintf	_snprintf
//#define gmtime_r(const_time_t,out_tm)
#else

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#undef __STDC_FORMAT_MACROS

#endif // _MSC_VER


//BOOST_STATIC_ASSERT(sizeof(Timestamp) == sizeof(int64_t));

namespace base
{


Timestamp::Timestamp(int64_t microseconds)
  : microSecondsSinceEpoch_(microseconds)
{
}

std::string Timestamp::toString() const
{
  char buf[32] = {0};
  int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
  int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;

#ifdef _MSC_VER
  snprintf(buf, sizeof(buf)-1, "%I64d.%06I64d", seconds, microseconds);
#else
  snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
#endif // _MSC_VER

  return std::string(buf);
}

std::string Timestamp::toFormattedString() const
{
	char buf[32] = {0};
	struct tm tm_time;
#ifdef _MSC_VER

	__time64_t seconds = static_cast<__time64_t>(microSecondsSinceEpoch_);
	int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);

	_gmtime64_s(&tm_time,&seconds);
#else
  time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
  int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
  gmtime_r(&seconds, &tm_time);
#endif // _MSC_VER

  snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
      tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
      tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
      microseconds);

  return std::string(buf);
}

std::string Timestamp::toPathString() const
{
	char buf[32] = {0};
	struct tm tm_time;
#ifdef _MSC_VER

	__time64_t seconds = static_cast<__time64_t>(microSecondsSinceEpoch_);
	int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);

	_gmtime64_s(&tm_time,&seconds);
#else
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
	int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
	gmtime_r(&seconds, &tm_time);
#endif // _MSC_VER

	snprintf(buf, sizeof(buf), "%4d%02d%02d_%02d%02d%02d_%06d",
		tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
		tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
		microseconds);

	return std::string(buf);
}

Timestamp Timestamp::now()
{
#ifdef _MSC_VER
	int64_t seconds = 0;
	_time64( &seconds );
    
	return Timestamp(seconds);
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int64_t seconds = tv.tv_sec;
	return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
#endif // _MSC_VER
}

Timestamp Timestamp::invalid()
{
  return Timestamp();
}


};//base
