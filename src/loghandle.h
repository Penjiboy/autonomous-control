#ifndef LOGHANDLE_H
#define LOGHANDLE_H

#include <cstdint>
#include <string>

using namespace std;

class LogHandle {
public:
	void info(string msg);
	void warn(string msg);
	void err(string msg);
};

#endif
