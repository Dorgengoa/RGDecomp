/* rgp:protos */
#define RGP_SELF_ResGroupLoadByKind_42b840 1
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

/*rgp*/           /* extern */
/*rgp*/ /* extern */
extern s32 D_00480284;
extern s32 D_004802DC;
extern s32 D_004802E0;
extern s32 D_004802E4;
extern s32 D_004802E8;
extern s32 D_004802EC;
extern s32 D_004802F0;
extern s32 D_004802F4;
extern s32 D_004802F8;
extern s32 D_004802FC;
extern s32 D_00480300;
extern s32 D_00480304;
extern s32 D_00480308;
extern s32 D_0048030C;
extern s32 D_00480310;
extern s32 D_00480314;
extern s32 D_00480318;

s32 ResGroupLoadByKind_42b840(s32 arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4) {
    if ((arg1 != 1) && (arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    switch (arg2) {
    case 0:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x2D80);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_00480284);
        break;
    case 1:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x480);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802DC);
        break;
    case 5:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x1400);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_0048030C);
        break;
    case 2:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x1400);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_00480304);
        break;
    case 4:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0xC80);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802F8);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802FC);
        break;
    case 3:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0xC80);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_00480310);
        break;
    case 8:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x200);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802E0);
        break;
    case 9:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x200);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802E4);
        break;
    case 7:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x300);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802EC);
        break;
    case 11:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x300);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802F4);
        break;
    case 10:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x500);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802F0);
        break;
    case 12:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x500);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_00480308);
        break;
    case 13:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0xA00);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_00480300);
        break;
    case 6:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x1400);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802E8);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_004802FC);
        break;
    case 14:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0xA00);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_00480314);
        break;
    case 15:
        ResGroupStackInit_42c600(arg0, arg3, arg1, 0, 0x1400);
        ResGroupRunScriptFromArchive_42bf70(arg0, arg1, arg4, D_00480318);
        break;
    }
    return 1;
}
