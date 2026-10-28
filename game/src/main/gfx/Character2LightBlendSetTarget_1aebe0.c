/* rgp:protos */
#define RGP_SELF_Character2LightBlendSetTarget_1aebe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/* ---- mechanical m2c draft (lane u31) -------------------------------------
   Produced by build/u31/gendraft.py from m2c --valid-syntax.  This is a
   STARTING POINT, not a match: every M2C_* macro below marks something m2c
   could not type or could not translate.  Replace them as the unit is worked.
   -------------------------------------------------------------------- */
typedef rg_u128 u128;
typedef rg_s128 s128;
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

/*rgp*/              /* extern */

void Character2LightBlendSetTarget_1aebe0(s8 *arg0, s32 arg1, s8 *arg2, s8 *arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 var_5;
    s8 *temp_4;

    M2C_FIELD(arg0, s128 *, 0x5F0) = (s128) M2C_FIELD(arg2, s128 *, 0);
    M2C_FIELD(arg0, s128 *, 0x600) = (s128) M2C_FIELD(arg2, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x610) = (s128) M2C_FIELD(arg2, s128 *, 0x20);
    M2C_FIELD(arg0, s128 *, 0x620) = (s128) M2C_FIELD(arg2, s128 *, 0x30);
    M2C_FIELD(arg0, s128 *, 0x6B0) = (s128) M2C_FIELD(arg3, s128 *, 0);
    M2C_FIELD(arg0, s128 *, 0x6C0) = (s128) M2C_FIELD(arg3, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x6D0) = (s128) M2C_FIELD(arg3, s128 *, 0x20);
    M2C_FIELD(arg0, s128 *, 0x6E0) = (s128) M2C_FIELD(arg3, s128 *, 0x30);
    sceVu0CopyVector(arg0 + 0x590, arg4);
    sceVu0CopyVector(arg0 + 0x5C0, arg5);
    M2C_FIELD(arg0, s32 *, 0x774) = arg1;
    if (M2C_FIELD(arg0, f32 *, 0x63C) == -1.0f) {
        M2C_FIELD(arg0, s128 *, 0x630) = (s128) M2C_FIELD(arg2, s128 *, 0);
        M2C_FIELD(arg0, s128 *, 0x640) = (s128) M2C_FIELD(arg2, s128 *, 0x10);
        M2C_FIELD(arg0, s128 *, 0x650) = (s128) M2C_FIELD(arg2, s128 *, 0x20);
        M2C_FIELD(arg0, s128 *, 0x660) = (s128) M2C_FIELD(arg2, s128 *, 0x30);
        M2C_FIELD(arg0, s128 *, 0x6F0) = (s128) M2C_FIELD(arg3, s128 *, 0);
        M2C_FIELD(arg0, s128 *, 0x700) = (s128) M2C_FIELD(arg3, s128 *, 0x10);
        M2C_FIELD(arg0, s128 *, 0x710) = (s128) M2C_FIELD(arg3, s128 *, 0x20);
        M2C_FIELD(arg0, s128 *, 0x720) = (s128) M2C_FIELD(arg3, s128 *, 0x30);
    }
    if ((arg6 != 0)) { if (M2C_FIELD(arg0, s32 *, 0x774) != M2C_FIELD(arg0, s32 *, 0x770)) {
        var_5 = 0;
        do {
            temp_4 = (s8 *)(arg0 + (var_5 * 0x10));
            var_5 += 1;
            M2C_FIELD(temp_4, f32 *, 0x670) = (f32) ((M2C_FIELD(temp_4, f32 *, 0x5F0) - M2C_FIELD(temp_4, f32 *, 0x630)) / M2C_FIELD(arg0, f32 *, 0x77C));
            M2C_FIELD(temp_4, f32 *, 0x674) = (f32) ((M2C_FIELD(temp_4, f32 *, 0x5F4) - M2C_FIELD(temp_4, f32 *, 0x634)) / M2C_FIELD(arg0, f32 *, 0x77C));
            M2C_FIELD(temp_4, f32 *, 0x678) = (f32) ((M2C_FIELD(temp_4, f32 *, 0x5F8) - M2C_FIELD(temp_4, f32 *, 0x638)) / M2C_FIELD(arg0, f32 *, 0x77C));
            M2C_FIELD(temp_4, f32 *, 0x730) = (f32) ((M2C_FIELD(temp_4, f32 *, 0x6B0) - M2C_FIELD(temp_4, f32 *, 0x6F0)) / M2C_FIELD(arg0, f32 *, 0x77C));
            M2C_FIELD(temp_4, f32 *, 0x734) = (f32) ((M2C_FIELD(temp_4, f32 *, 0x6B4) - M2C_FIELD(temp_4, f32 *, 0x6F4)) / M2C_FIELD(arg0, f32 *, 0x77C));
            M2C_FIELD(temp_4, f32 *, 0x738) = (f32) ((M2C_FIELD(temp_4, f32 *, 0x6B8) - M2C_FIELD(temp_4, f32 *, 0x6F8)) / M2C_FIELD(arg0, f32 *, 0x77C));
        } while (var_5 < 4);
        M2C_FIELD(arg0, f32 *, 0x5B0) = (f32) ((M2C_FIELD(arg0, f32 *, 0x590) - M2C_FIELD(arg0, f32 *, 0x5A0)) / M2C_FIELD(arg0, f32 *, 0x77C));
        M2C_FIELD(arg0, f32 *, 0x5B4) = (f32) ((M2C_FIELD(arg0, f32 *, 0x594) - M2C_FIELD(arg0, f32 *, 0x5A4)) / M2C_FIELD(arg0, f32 *, 0x77C));
        M2C_FIELD(arg0, f32 *, 0x5B8) = (f32) ((M2C_FIELD(arg0, f32 *, 0x598) - M2C_FIELD(arg0, f32 *, 0x5A8)) / M2C_FIELD(arg0, f32 *, 0x77C));
        M2C_FIELD(arg0, s32 *, 0x5BC) = 0;
        M2C_FIELD(arg0, f32 *, 0x5E0) = (f32) ((M2C_FIELD(arg0, f32 *, 0x5C0) - M2C_FIELD(arg0, f32 *, 0x5D0)) / M2C_FIELD(arg0, f32 *, 0x77C));
        M2C_FIELD(arg0, f32 *, 0x5E4) = (f32) ((M2C_FIELD(arg0, f32 *, 0x5C4) - M2C_FIELD(arg0, f32 *, 0x5D4)) / M2C_FIELD(arg0, f32 *, 0x77C));
        M2C_FIELD(arg0, f32 *, 0x5E8) = (f32) ((M2C_FIELD(arg0, f32 *, 0x5C8) - M2C_FIELD(arg0, f32 *, 0x5D8)) / M2C_FIELD(arg0, f32 *, 0x77C));
        M2C_FIELD(arg0, s32 *, 0x5EC) = 0;
        M2C_FIELD(arg0, s32 *, 0x778) = (s32) M2C_FIELD(arg0, f32 *, 0x77C);
        M2C_FIELD(arg0, s32 *, 0x770) = (s32) M2C_FIELD(arg0, s32 *, 0x774);
    } } else {
        M2C_FIELD(arg0, s32 *, 0x778) = 0;
        M2C_FIELD(arg0, s128 *, 0x630) = (s128) M2C_FIELD(arg2, s128 *, 0);
        M2C_FIELD(arg0, s128 *, 0x640) = (s128) M2C_FIELD(arg2, s128 *, 0x10);
        M2C_FIELD(arg0, s128 *, 0x650) = (s128) M2C_FIELD(arg2, s128 *, 0x20);
        M2C_FIELD(arg0, s128 *, 0x660) = (s128) M2C_FIELD(arg2, s128 *, 0x30);
        M2C_FIELD(arg0, s128 *, 0x6F0) = (s128) M2C_FIELD(arg3, s128 *, 0);
        M2C_FIELD(arg0, s128 *, 0x700) = (s128) M2C_FIELD(arg3, s128 *, 0x10);
        M2C_FIELD(arg0, s128 *, 0x710) = (s128) M2C_FIELD(arg3, s128 *, 0x20);
        M2C_FIELD(arg0, s128 *, 0x720) = (s128) M2C_FIELD(arg3, s128 *, 0x30);
        sceVu0CopyVector(arg0 + 0x5A0, arg4);
        sceVu0CopyVector(arg0 + 0x5D0, arg5);
    }
    M2C_FIELD(arg0, s32 *, 0x788) = 0;
}
