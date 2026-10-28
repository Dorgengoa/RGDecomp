/* rgp:protos */
#define RGP_SELF_DynGravityCmd_1674a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T1674A0 { u8 pad000[0x10C]; s32 f10C; };

extern struct T1674A0 *D_00481154;
/*rgp*/

s32 DynGravityCmd_1674a0(s32 a0)
{
    VariantReadVec3_15f6c0((u8 *)D_00481154 + 0x100, a0);
    D_00481154->f10C = 0;
    return 1;
}
