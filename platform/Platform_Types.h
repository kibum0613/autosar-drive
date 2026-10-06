/* Minimal AUTOSAR Platform_Types.h for host (x86-64) build and test.
 * Replace with the BSW vendor's file when integrating on a real ECU. */
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#include <stdint.h>

#define CPU_TYPE_8    8
#define CPU_TYPE_16   16
#define CPU_TYPE_32   32
#define CPU_TYPE_64   64
#define CPU_TYPE      CPU_TYPE_64

#ifndef TRUE
#define TRUE  1U
#endif
#ifndef FALSE
#define FALSE 0U
#endif

typedef unsigned char boolean;
typedef int8_t        sint8;
typedef uint8_t       uint8;
typedef int16_t       sint16;
typedef uint16_t      uint16;
typedef int32_t       sint32;
typedef uint32_t      uint32;
typedef int64_t       sint64;
typedef uint64_t      uint64;
typedef float         float32;
typedef double        float64;

#endif /* PLATFORM_TYPES_H */
