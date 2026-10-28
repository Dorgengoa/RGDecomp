/* rgp:protos */
#define RGP_SELF_ActInfoAbltStart_23d2e0 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044C870[0x400];
extern s32 D_00481E80;
extern s32 D_00481E84;
extern u8 D_004BCE6C[0x400];
extern s16 D_004BCE92[0x10];

s32 ActInfoAbltStart_23d2e0(s8 *arg0, s32 arg1) {
    s32 v;
    s8 *p;
    s32 t;

    if (arg1 != 1 && arg1 != 2 && arg1 != 3) {
        return 0;
    }
    if (*(s32 *)D_004BCE6C == 0 || D_004BCE92[0] >= 0x20) {
        return 1;
    }
    v = 0;
    p = (s8 *)(*(s32 *)D_004BCE6C + D_004BCE92[0] * 0xC);
    if (arg1 > 1) {
        v = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(arg0 + 8), D_0044C870, 0);
    }
    ActInfoAbltInit_22ee00(p, ((s32)StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0))), D_00481E80 + D_00481E84 * 8, 0, v);
    return 1;
}
