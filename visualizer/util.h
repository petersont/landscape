
#ifndef _UTIL_
#define _UTIL_

#include <stdlib.h>
#include <sys/time.h>

#include <string>
#include <vector>

double doubleTime();
double clamp(double x, double m, double M);
double sCurve(double x);
std::string readFile(const std::string& fullpath);
std::vector<std::string> components(const std::string& path, char separator);
int stringToInt(const std::string& s);
double stringToFloat(const std::string& s);
bool charInString(char c, const char* s);
std::string flattenWhitespace(const std::string& ins);

#endif
