#ifndef STDLOG_H
#define STDLOG_H

#include <cstdint>
#include <string>

using namespace std;

class StdLog {
public:
	void info(string msg);
	void warn(string msg);
	void err(string msg);
};

#endif
