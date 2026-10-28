/* rgp:protos */
#define RGP_SELF_MenuInsectCageEnterState_2a8d90 1
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
extern s8 *D_0048235C;
extern s8 *D_00482360;
extern s8 *D_00482364;
extern s8 *D_00482374;
extern s8 *D_004823D4;
extern s8 D_00482504;

s32 MenuInsectCageEnterState_2a8d90(s32 pd0, s32 arg1) {
    s8 *temp_2;
    s8 *temp_2_2;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x27, 0);
        MenuFadeSetColor_29ff90(D_00482374, 0U, 0U, 0U);
        MenuFadeStartToColor_2a0040(D_00482374);
        D_00482504 = 0;
    }
    switch (D_00482504) {                           /* irregular */
    case 0:
        if (MenuFadeStep_29ffd0(D_00482374, 1.0f) == 1) {
            MenuSetWidgetGroupVisible_2a8ab0(0);
            UiSetWidgetsVisibleById_291110(D_00482360, 3, 0, 1);
            FieldViewResTeardown_202f40();
            WorldDataRequestKind_3f0960(((int)GetWorldDataMgr_1fedf0()), 5);
            D_00482504 += 1;
        }
        break;
    case 1:
        if (WorldDataMgrNoRequestPending_3eef10(((int)GetWorldDataMgr_1fedf0())) & 0xFF) {
            InsectCageMenuOpen_38b9a0();
            D_00482504 += 1;
        }
        break;
    case 2:
        if (InsectCageMenuLoadRes_38b280() != 0) {
            InsectCageSoundLoad_38b230();
            D_00482504 += 1;
        }
        break;
    case 3:
        if ((InsectCageSoundInit_38b1e0() & 0xFF) == 1) {
            temp_2 = (s8 *)(GetCurrentScene_1f5be0());
            M2C_FIELD(temp_2, s32 *, 0x4348) = (s32) M2C_FIELD(temp_2, s32 *, 0x4344);
            M2C_FIELD(temp_2, s32 *, 0x4344) = 4;
            temp_2_2 = (s8 *)(GetCurrentScene_1f5be0());
            D_004823D4 = (s8 *)(((int)ObjRecGetLiveObject_1c3bc0(temp_2_2, M2C_FIELD(temp_2_2, s32 *, 0x4344))));
            M2C_FIELD(D_00482374, s16 *, 0x46) = 1;
            StateMachineSetState_28ede0(D_0048235C, 0xAB, 0);
            D_00482504 = 0;
        }
        break;
    }
    return 1;
}
