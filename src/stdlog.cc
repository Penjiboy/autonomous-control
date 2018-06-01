#include "stdlog.h"

#include <iostream>

void StdLog::info(string msg) {
	cout << "[INFO] " << msg << "\n";
}

void StdLog::warn(string msg) {
	cout << "[WARNING] " << msg << "\n";
}

void StdLog::err(string msg) {
	cout << "[ERROR] " << msg << "\n";
}
