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

M2C_UNK MemStackReset_14d830(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_3f6560(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysPurposeLoad_3f6630(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysPurposeLoad_3f6700(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_3f6800(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_3fd2d0(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_3fd380(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_3ff390(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_3ff440(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_405c70(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_405d20(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_406c80(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_406ce0(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_408230(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysPurposeLoad_4082c0(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_408370(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_40b320(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_40b380(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_410b00(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_410b60(s32);                          /* extern */
M2C_UNK WorldSubsysPurposeLoad_424610(s32, s32, M2C_UNK, s8 *);    /* extern */
M2C_UNK WorldSubsysRelease_424670(s32);                          /* extern */

s32 WorldDataMgrSelectPurpose_3f05f0(s8 *arg0, s32 arg1) {
    s32 temp_17;
    s32 temp_4;
    s8 *temp_16;

    temp_16 = (s8 *)(M2C_FIELD(arg0, s8 **, 0x28));
    if (temp_16 == NULL) {
        return 0;
    }
    temp_17 = M2C_FIELD(temp_16, s32 *, 0x10);
    if (temp_17 == 0) {
        return 0;
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0x24);
    if (temp_4 == 0) {
        return 0;
    }
    if ((arg1 == 1) || (arg1 < 0)) {
        MemStackReset_14d830(temp_4);
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0x88);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 0) {
            WorldSubsysPurposeLoad_410b00(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_410b60(temp_4);
        }
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0x8C);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 1) {
            WorldSubsysPurposeLoad_4082c0(temp_4, temp_17, 0, arg0);
        } else if (M2C_FIELD(temp_16, s16 *, 0) == 8) {
            WorldSubsysPurposeLoad_408230(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_408370(temp_4);
        }
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0x94);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 2) {
            WorldSubsysPurposeLoad_3fd2d0(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_3fd380(temp_4);
        }
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0x90);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 3) {
            WorldSubsysPurposeLoad_406c80(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_406ce0(temp_4);
        }
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0x98);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 4) {
            WorldSubsysPurposeLoad_3ff390(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_3ff440(temp_4);
        }
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0x9C);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 5) {
            WorldSubsysPurposeLoad_3f6700(temp_4, temp_17, 0, arg0);
        } else if (M2C_FIELD(temp_16, s16 *, 0) == 4) {
            WorldSubsysPurposeLoad_3f6630(temp_4, temp_17, 0, arg0);
        } else if (M2C_FIELD(temp_16, s16 *, 0) == 6) {
            WorldSubsysPurposeLoad_3f6560(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_3f6800(temp_4);
        }
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0xA0);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 6) {
            WorldSubsysPurposeLoad_40b320(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_40b380(temp_4);
        }
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0xA4);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 7) {
            WorldSubsysPurposeLoad_405c70(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_405d20(temp_4);
        }
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0xA8);
    if (temp_4 != 0) {
        if (M2C_FIELD(temp_16, s16 *, 0) == 8) {
            WorldSubsysPurposeLoad_424610(temp_4, temp_17, 0, arg0);
        } else {
            WorldSubsysRelease_424670(temp_4);
        }
    }
    return 1;
}
