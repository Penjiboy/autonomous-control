#ifndef NLOG_H
#define NLOG_H

#include <cstdint>
#include <string>

using namespace std;

// A null log endpoint which ignores all passed log messages.
class NLog {
public:
	void info(string msg) {}
	void warn(string msg) {}
	void err(string msg) {}
};

#endif
