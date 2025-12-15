#pragma once
#include <Arduino.h>

#define DEBUG 1
// Conditional definition for debugging if DEBUG is 1 then it will print to serial port.
// If DEBUG = 0 then the lines will be removed by the compiler.
#if DEBUG == 1
#define debug(x) Serial0.print(x)
#define debugln(x) Serial0.println(x)
#define debugf(fmt, ...) Serial0.print((fmt), ##__VA_ARGS__)
#define debugg(x, y, z) Serial0.printf(x, y, z)
#define debugh(x,y) Serial0.print(x,y)
#else
#define debug(x)
#define debugln(x)
#define debugh(x,y)
#define debugf(fmt, ...)
#define debugg(x, y, z)
#endif