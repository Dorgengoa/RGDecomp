#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
#pragma opt_propagation off


typedef unsigned __int128 u128;
typedef __int128 s128;
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK(x) (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

s32 BtlEffCollectListRefsMaybe_3f9c60(s32, u8 *, s32, s32, s32);
s32 ArrayAddUnique_3f9c00(s32, s32, s32, s32);               /* extern */

s32 BtlEffRowCollectRefsMaybe_3f9d00(s32 arg0, const u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {




    s32 var_3;


    s32 var_2_2 = (s32)(arg4);
    u8 * var_18 = (u8 *)(arg1);
    s32 var_17 = (s32)(arg2);
    s32 var_16 = (s32)(arg3);
    if (var_18 == NULL) {
        return var_2_2;
    }
    s32 var_2 = (s32)(BtlEffCollectListRefsMaybe_3f9c60((s32)(arg0),(u8 *)( M2C_FIELD(var_18, u8 **, 8)),(s32)( arg2),(s32)( arg3),(s32)( arg4)));
    s32 var_19 = (s32)(0);
    do {
        var_3 = (s32)(var_19 * 4);
        var_3 = (s32)((s32) (var_18 + var_3));
        var_2 = (s32)(ArrayAddUnique_3f9c00((s32)(M2C_FIELD(var_3, s32 *, 0x10)),(s32)( var_17),(s32)( var_16),(s32)( var_2)));
        var_19 += 1;
        var_3 = (s32)(var_19 < 3);
    } while (var_3 != 0);
    return ArrayAddUnique_3f9c00((s32)(M2C_FIELD(var_18, s32 *, 0x20)),(s32)( var_17),(s32)( var_16),(s32)( var_2));
}

}
