#ifndef __TYPES_H__
#define __TYPES_H__

// a. Not having these types is triggering; read note b
#include <stdbool.h>
#include <stdint.h>

// b. I need these types for my own sanity
typedef int_fast8_t i8;
typedef int_fast16_t i16;
typedef int_fast32_t i32;
typedef int_fast64_t i64;

typedef uint_fast8_t u8;
typedef uint_fast16_t u16;
typedef uint_fast32_t u32;
typedef uint_fast64_t u64;

#endif // __TYPES_H__
