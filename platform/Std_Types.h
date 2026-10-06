/* Minimal AUTOSAR Std_Types.h (host build). */
#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Platform_Types.h"
#include "Compiler.h"

typedef uint8 Std_ReturnType;

#ifndef E_OK
#define E_OK     0x00U
#endif
#ifndef E_NOT_OK
#define E_NOT_OK 0x01U
#endif

#define STD_HIGH 0x01U
#define STD_LOW  0x00U
#define STD_ON   0x01U
#define STD_OFF  0x00U

#endif /* STD_TYPES_H */
