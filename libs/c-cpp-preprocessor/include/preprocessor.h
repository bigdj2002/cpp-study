#pragma once

#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#define EMPTY

#define CHECK1(x, ...) if (!(x)) { printf(__VA_ARGS__); }
#define CHECK2(x, ...) if ((x)) { printf(__VA_ARGS__); }
#define CHECK3(...) { printf(__VA_ARGS__); }

#if __GNU__

#else
#define printlog1(fmt, ...) printlog1_(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define printlog2(fmt, args...) printlog2_(fmt, ##args)
#endif


int preprocessor_example();