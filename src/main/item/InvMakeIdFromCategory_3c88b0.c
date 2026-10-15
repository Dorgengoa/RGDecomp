#include "types.h"
#pragma optimization_level 2
#pragma schedule on

/* ---- mechanical m2c draft (lane u31) -------------------------------------
   Produced by build/u31/gendraft.py from m2c --valid-syntax.  This is a
   STARTING POINT, not a match: every M2C_* macro below marks something m2c
   could not type or could not translate.  Replace them as the unit is worked.
   -------------------------------------------------------------------- */
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

extern u8 D_004659E8[0x400];
extern u8 D_004659F0[0x400];
extern u8 D_004659F8[0x400];
extern u8 D_00465A00[0x400];
extern u8 D_00465A08[0x400];
extern u8 D_00465A18[0x400];
extern u8 D_00465A20[0x400];
extern u8 D_00465A28[0x400];
extern u8 D_00465A30[0x400];
extern u8 D_00465A38[0x400];
extern u8 D_00465A48[0x400];
extern u8 D_00465A50[0x400];
extern u8 D_00465A60[0x400];
extern u8 D_00465A70[0x400];
extern u8 D_00465A78[0x400];
extern u8 D_00465A88[0x400];
extern u8 D_00465A90[0x400];
extern u8 D_00465AA0[0x400];
extern u8 D_00465AA8[0x400];
extern u8 D_00465AB8[0x400];
extern u8 D_00465AC0[0x400];
extern u8 D_00465AD0[0x400];
extern u8 D_00465AE0[0x400];
extern u8 D_00465AE8[0x400];
extern u8 D_00465AF8[0x400];
extern u8 D_00465B00[0x400];
extern u8 D_00465B10[0x400];
extern u8 D_00465B18[0x400];
extern u8 D_00465B20[0x400];
extern u8 D_00465B28[0x400];
extern u8 D_00465B30[0x400];

s32 InvMakeIdFromCategory_3c88b0(s32 pd0, u32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_6;
    s32 var_7;
    s32 var_8;
    u32 var_5;

    var_5 = arg1;
    var_6 = arg2;
    var_7 = arg3;
    var_8 = arg4;
    if (var_5 == 0xA) {
        if (!(var_6 < (*(s32 *)D_004659E8))) {
            var_6 -= (*(s32 *)D_004659E8);
            var_5 = 1;
        } else {
            var_5 = 0;
        }
    }
    switch (var_5) {
    case 0:
        if (var_6 < 0) {
            var_6 = 0;
        } else {
            if (var_6 >= (*(s32 *)D_004659E8)) {
                var_6 = (*(s32 *)D_004659E8) - 1;
            }
        }
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_004659F0)) {
                var_7 = (*(s32 *)D_004659F0) - 1;
            }
        }
        if (var_8 < 0) {
            var_8 = 0;
        } else {
            if (var_8 >= (*(s32 *)D_004659F8)) {
                var_8 = (*(s32 *)D_004659F8) - 1;
            }
        }
        return var_7 + ((*(s32 *)D_00465A08) + (var_6 * (*(s32 *)D_00465A00)) + (var_8 * (*(s32 *)D_004659F0)));
    case 1:
        if (var_6 < 0) {
            var_6 = 0;
        } else {
            if (var_6 >= (*(s32 *)D_00465A18)) {
                var_6 = (*(s32 *)D_00465A18) - 1;
            }
        }
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465A20)) {
                var_7 = (*(s32 *)D_00465A20) - 1;
            }
        }
        if (var_8 < 0) {
            var_8 = 0;
        } else {
            if (var_8 >= (*(s32 *)D_00465A28)) {
                var_8 = (*(s32 *)D_00465A28) - 1;
            }
        }
        return var_7 + ((*(s32 *)D_00465A38) + (var_6 * (*(s32 *)D_00465A30)) + (var_8 * (*(s32 *)D_00465A20)));
    case 2:
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465A48)) {
                var_7 = (*(s32 *)D_00465A48) - 1;
            }
        }
        if (var_8 < 0) {
            var_8 = 0;
        } else {
            if (var_8 >= (*(s32 *)D_00465A50)) {
                var_8 = (*(s32 *)D_00465A50) - 1;
            }
        }
        return var_7 + ((*(s32 *)D_00465A60) + (var_8 * (*(s32 *)D_00465A48)));
    case 3:
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465A70)) {
                var_7 = (*(s32 *)D_00465A70) - 1;
            }
        }
        return (*(s32 *)D_00465A78) + var_7;
    case 4:
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465A88)) {
                var_7 = (*(s32 *)D_00465A88) - 1;
            }
        }
        return (*(s32 *)D_00465A90) + var_7;
    case 5:
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465AA0)) {
                var_7 = (*(s32 *)D_00465AA0) - 1;
            }
        }
        return (*(s32 *)D_00465AA8) + var_7;
    case 6:
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465AB8)) {
                var_7 = (*(s32 *)D_00465AB8) - 1;
            }
        }
        if (var_8 < 0) {
            var_8 = 0;
        } else {
            if (var_8 >= (*(s32 *)D_00465AC0)) {
                var_8 = (*(s32 *)D_00465AC0) - 1;
            }
        }
        return var_7 + ((*(s32 *)D_00465AD0) + (var_8 * (*(s32 *)D_00465AB8)));
    case 7:
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465AE0)) {
                var_7 = (*(s32 *)D_00465AE0) - 1;
            }
        }
        return (*(s32 *)D_00465AE8) + var_7;
    case 8:
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465AF8)) {
                var_7 = (*(s32 *)D_00465AF8) - 1;
            }
        }
        return (*(s32 *)D_00465B00) + var_7;
    case 9:
        if (var_6 < 0) {
            var_6 = 0;
        } else {
            if (var_6 >= (*(s32 *)D_00465B10)) {
                var_6 = (*(s32 *)D_00465B10) - 1;
            }
        }
        if (var_7 < 0) {
            var_7 = 0;
        } else {
            if (var_7 >= (*(s32 *)D_00465B18)) {
                var_7 = (*(s32 *)D_00465B18) - 1;
            }
        }
        if (var_8 < 0) {
            var_8 = 0;
        } else {
            if (var_8 >= (*(s32 *)D_00465B20)) {
                var_8 = (*(s32 *)D_00465B20) - 1;
            }
        }
        return var_7 + ((*(s32 *)D_00465B30) + (var_6 * (*(s32 *)D_00465B28)) + (var_8 * (*(s32 *)D_00465B18)));
    default:
        return -1;
    }
}
