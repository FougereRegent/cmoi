#ifndef TYPES_H
#define TYPES_H
#include <cmath>
#include <cstdint>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;

typedef char byte;

#if defined(__x86_64__) || defined(_M_X64)
typedef int64_t int64;
typedef uint64_t uint64;
#else
typedef int32_t int64;
typedef uint32_t uint64;
#endif

#endif // !
