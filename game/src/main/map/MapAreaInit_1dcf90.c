/* rgp:protos */
#define RGP_SELF_MapAreaInit_1dcf90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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

extern f32 D_0047D1EC __attribute__((section(".sdata")));
extern f32 D_0047D1F0 __attribute__((section(".sdata")));

void MapAreaInit_1dcf90(s8 *arg0) {
    s32 var_16;
    s32 var_5;
    s8 *temp_4;

    MapDataInit_1e7c50(arg0);
    MapRecTableInit_1dd9b0(arg0 + 0x54);
    NopThunk_1ed090();
    LoadHandleResetThunk_1ccc10((s32) (arg0 + 0xA8));
    MapDataSetType_1e7430(arg0, 2U);
    M2C_FIELD(arg0, s16 *, 0xE4) = 0;
    MapIdIndexReset_1dde60(arg0 + 0xFC);
    MapIdIndexReset_1dde60(arg0 + 0x10C);
    M2C_FIELD(arg0, s16 *, 0x11C) = 0x7FFF;
    M2C_FIELD(arg0, s16 *, 0x11E) = -1;
    var_16 = 0;
    M2C_FIELD(arg0, f32 *, 0x120) = (f32) D_0047D1EC;
    M2C_FIELD(arg0, f32 *, 0x124) = (f32) D_0047D1F0;
    M2C_FIELD(arg0, s32 *, 0xE8) = 0;
    M2C_FIELD(arg0, s32 *, 0xEC) = 0;
    M2C_FIELD(arg0, s32 *, 0xF0) = 0;
    M2C_FIELD(arg0, s32 *, 0xF4) = 0;
    M2C_FIELD(arg0, s32 *, 0xF8) = 0;
    do {
        MapAreaTreasureBoxSlotReset_1de8f0(arg0 + (var_16 * 0xC) + 0xB4);
        var_16 += 1;
    } while (var_16 < 4);
    var_5 = 0;
    do {
        temp_4 = (s8 *)(arg0 + (var_5 * 4));
        var_5 += 1;
        M2C_FIELD(temp_4, s32 *, 0x128) = 0;
        M2C_FIELD(temp_4, s32 *, 0x178) = 0;
    } while (var_5 < 0x14);
    M2C_FIELD(arg0, s16 *, 0x1C8) = 0;
    M2C_FIELD(arg0, s16 *, 0x1CA) = 0;
}
