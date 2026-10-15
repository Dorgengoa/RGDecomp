#include "types.h"

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

s32 ParseFlagNames_1ca940(s32, M2C_UNK *, M2C_UNK);          /* extern */
extern u8 D_0044C8A0[0x400];

s32 ScriptParseIntStrArgs_23de60(s32 *arg0, s8 **arg1, s32 *arg2, s32 arg3) {
    s32 var_21;
    s32 var_2;
    s8 *var_20;

    if ((arg3 != 0) && (arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    var_21 = -1;
    var_20 = (s8 *)(NULL);
    if (arg3 > 0) {
        if (*arg2 == 0) {
            var_2 = ParseFlagNames_1ca940(ScriptArgGetStr_23fba0(arg2), &(*(M2C_UNK *)D_0044C8A0), 0);
        } else {
            var_2 = ScriptArgGetInt_23fc00(arg2);
        }
        var_21 = var_2;
    }
    if (arg3 > 1) {
        var_20 = (s8 *)(StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg2 + 2)));
    }
    if (arg0 != NULL) {
        *arg0 = var_21;
    }
    if (arg1 != NULL) {
        *arg1 = var_20;
    }
    return 1;
}
