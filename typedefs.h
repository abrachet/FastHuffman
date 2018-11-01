#pragma once

#include <sys/types.h>
#include <stddef.h>

typedef unsigned long long u64;
typedef unsigned int       u32;
typedef unsigned short     u16;
typedef unsigned char      u8;

typedef signed long long   i64;
typedef signed int         i32;
typedef signed short       i16;
typedef signed char        i8;

typedef i64 register_t;

#ifdef HUGE_COUNT
typedef u64 count_t;
#elif defined SMALL_COUNT
typedef u16 count_t;
#elif defined TINY_COUNT
typedef u8 count_t;
#else
typedef u32 count_t;
#endif


#ifdef UTFTT //UTF-32
typedef u32 offset_t;
#elif defined UTFST //UTF-16
typedef u16 offset_t;
#else //ASCII UTF-8
#define VEC_SIZE (128) //255 possible addresses
typedef u8 offset_t;
#endif 



typedef u64 ascii_vector_t __attribute__((vector_size(1024)));
typedef u64 utf8_vector_t __attribute__((vector_size(1024)));
typedef count_t vector_t __attribute__((vector_size(512)));

