#include <iostream>
#include <sstream>
#include <time.h>
#include <iomanip>

enum TLogLevel {logERROR, logWARNING, logINFO};

template <typename OutputPolicy>
class Log
{
public:
   Log();
   virtual ~Log();
   std::ostringstream& Get(TLogLevel level = logINFO);
protected:
   std::ostringstream os;
private:
   Log(const Log&);
   void NowTime();
   Log& operator =(const Log&);
private:
   TLogLevel messageLevel;
};

/*
#include <windows.h>
template <typename OutputPolicy>
void Log<OutputPolicy>::NowTime()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	os.fill('0');
	os << std::setw(2) << st.wDay << "-" << std::setw(2) << st.wMonth << "-" << std::setw(4) << st.wYear << " ";
	os << std::setw(2) << st.wHour << ":" << std::setw(2) << st.wMinute << ":" << std::setw(2) << st.wSecond;
	os << "." << std::setw(3) << st.wMilliseconds;
} 
*/
void Log::NowTime()
{
	time_t now;
	time(&now);
	struct tm *st;
	st = localtime(&now);
	struct timeval *tv;
	gettimeofday(&tv, NULL);
	int ms = tv->tv_usec / 1000;

	os.fill('0');
	os << std::setw(2) << st->tm_mday << "-" << std::setw(2) << st->tm_mon << "-" << std::setw(4) << st->tm_year + 1700 << " ";
	os << std::setw(2) << st->tm_hour << ":" << std::setw(2) << st->tm_min << ":" << std::setw(2) << st->tm_sec;
	os << "." << std::setw(3) << ms;
}

std::string ToString(TLogLevel level)
{
	switch(level)
	{
		case logINFO: return "INFO";
		case logERROR: return "ERROR";
		case logWARNING: return "WARNING";
	}
	return "UNKNOWN";
}

template <typename OutputPolicy>
std::ostringstream& Log<OutputPolicy>::Get(TLogLevel level)
{
	os << "- ";
	NowTime();
	os << "\t" << ToString(level) << "\t";
	messageLevel = level;
	return os;
}

template <typename OutputPolicy>
Log<OutputPolicy>::Log() {}


template <typename OutputPolicy>
Log<OutputPolicy>::~Log()
{
	OutputPolicy::Output(os.str());
}

class Output2FILE // implementation of OutputPolicy
{
public:
	static FILE*& Stream();
	static void Output(const std::string& msg);
};

inline FILE*& Output2FILE::Stream()
{
	static FILE* pStream = stderr;
	return pStream;
}
inline void Output2FILE::Output(const std::string& msg)
{
	FILE* pStream = Stream();
	if (pStream)
	{
		fprintf(pStream, "%s\n", msg.c_str());
		fflush(pStream);
	}
}

typedef Log<Output2FILE> FILELog;
#define LOG(level) FILELog().Get(level)

