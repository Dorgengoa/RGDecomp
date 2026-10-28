/* rgp:protos */
#define RGP_SELF_GameSessionShutdown_1f5bf0 1
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

/*rgp*/                       /* extern */
/*rgp*/                      /* extern */
/*rgp*/                      /* extern */
M2C_UNK SysMsgPostMaybe_1c3560(M2C_UNK, M2C_UNK *);           /* extern */
/*rgp*/                             /* extern */
/*rgp*/                      /* extern */
/*rgp*/                             /* extern */

void GameSessionShutdown_1f5bf0(void) {
    M2C_UNK sp20[0x1C] __attribute__((aligned(16)));
    s8 *temp_2;

    ClearPad2Enabled_2882a0();
    LoaderShutdown_1cdfe0(((int)GetLoaderMgr_1f59d0()));
    StreamMgrCloseAllThunk_1d6740(((int)GetStreamMgr_207ea0()));
    OverlayLoad_1c3210(3);
    DrawCtxVif1HandlerStop_15dc40();
    if (SysGetNextMode_1c3990() != 1) {
        SysMsgInit_1c69e0(sp20);
        SysMsgPostMaybe_1c3560(1, sp20);
    }
    MenuResReleaseAll_204fe0();
    EventObjDataReset_2d1170();
    Nop_207f90();
    ObjRefTableClear_313c50(0, 0, 0, 0);
    MapAndMinimapInit_201460();
    CharaSystemsShutdown_1fb5d0();
    EffectMgrShutdownGlobal_2d88f0();
    SoundBankStopAll_1bad70(-1);
    SetCurrentScene_1f5bd0(0);
    PauseSysInit_2f65a0();
    LoadingIconReset_2ee920();
    temp_2 = (s8 *)(((int)GetMainStack_1c6dc0()));
    MemStackReset_14d830(temp_2);
    MemStackAlign64_14d8e0(temp_2);
    WorldDataRebuild_1feac0(1);
}
