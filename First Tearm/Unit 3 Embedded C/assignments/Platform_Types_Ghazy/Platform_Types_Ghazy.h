/*
 * Platform_Types_Ghazy.h
 *
 *  Created on: Jul 23, 2024
 *      Author: Abdallah Ghazy
 */
#include <stdbool.h>
#include <stdint.h>

#ifndef PLATFORM_TYPES_GHAZY_H_
#define PLATFORM_TYPES_GHAZY_H_

#ifndef _Bool
#define _Bool unsigned char
#endif

#ifndef CPU_TYPE
#define CPU_TYPE CPU_TYPE_32
#endif


#ifndef CPU_BIT_ORDER
#define CPU_BIT_ORDER MSB_FIRST
#endif

#ifndef CPU_BYTE_ORDER
#define CPU_BYTE_ORDER  HIGH_BYTE_FIRST
#endif

#ifndef False
#define False (boolean)false
#endif

#ifndef True
#define True (boolean)true
#endif

typedef _Bool                      boolean;
typedef signed char                int8_t;
typedef unsigned char              uint8_t;
typedef char                       char_t;
typedef signed short               int16_t;
typedef unsigned short             uint16_t;
typedef signed int                 int32_t;
typedef unsigned int               uint32_t;
typedef signed long long int       int64_t;
typedef unsigned long long int     uint64_t;

typedef int8_t         		sint8;
typedef uint8_t       		uint8;
typedef int16_t        		sint16;
typedef uint16_t      		uint16;
typedef int32_t         	sint32;
typedef uint32_t       		uint32;
typedef int64_t  			sint64;
typedef uint64_t  			uint64;

typedef uint_least8_t       uint8_least;
typedef uint_least16_t      uint16_least;
typedef uint_least32_t      uint32_least;
typedef int_least8_t        sint8_least;
typedef int_least16_t       sint16_least;
typedef int_least32_t       sint32_least;
typedef float               float32;
typedef double              float64;

typedef volatile int8_t     vint8_t;
typedef volatile uint8_t    vuint8_t;

typedef volatile int16_t    vint16_t;
typedef volatile uint16_t   vuint16_t;

typedef volatile int32_t    vint32_t;
typedef volatile uint32_t   vuint32_t;

typedef volatile int64_t    vint64_t;
typedef volatile uint64_t   vuint64_t;






#endif /* PLATFORM_TYPES_GHAZY_H_ */
