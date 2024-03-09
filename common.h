#ifndef _NITRO_COMMON_H
#define _NITRO_COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>

typedef float f32;
typedef double f64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef size_t usize;
typedef ptrdiff_t ssize;

#define NITRO_MAX(a, b) ({\
      __typeof__(a) _a = (a);\
      __typeof__(b) _b = (b);\
      _a > _b ? _a : _b	     \
	})

#define NITRO_MIN(a, b) ({\
      __typeof__(a) _a = (a);\
      __typeof__(b) _b = (b);\
      _a < _b ? _a : _b\
	})

#define NITRO_ARRAYSIZE(array) (sizeof(array) / sizeof(array[0]))

#endif // _NITRO_COMMON_H
