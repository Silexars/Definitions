#pragma once

#include "Architecture.h"

#include <stdint.h>

typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;

typedef int8_t      int8;
typedef int16_t     int16;
typedef int32_t     int32;
typedef int64_t     int64;

typedef uintptr_t Handle;

// float16
typedef float               float32;
typedef double              float64;

#if TARGET_WORD >= 128
typedef unsigned __int128   uint128;
typedef __int128            int128;
typedef __float128          float128;
#endif

#if TARGET_WORD >= 256
typedef unsigned __int256   uint256;
typedef __int256            int256;
typedef __float256          float256;
#endif

#ifndef __cplusplus
typedef uint8 bool;
#endif

typedef uint8 u8;
typedef uint16 u16;
typedef uint32 u32;
typedef uint64 u64;

typedef int8 i8;
typedef int16 i16;
typedef int32 i32;
typedef int64 i64;

typedef float32 f32;
typedef float64 f64;

#include "Types/any.h"
#include "Types/any_args.h"
#include "Types/any_function.h"
#include "Types/any_method.h"
