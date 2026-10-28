/* rgp:protos */
#define RGP_SELF_EvTargetSetInitNamed_336ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T336ab0 {
    u8  pad00[0x108];
    f32 f108;
    f32 f10C;
    f32 f110;
    s16 f114;
} T336ab0;

/*rgp*/
/*rgp*/
/*rgp*/

void EvTargetSetInitNamed_336ab0(T336ab0 *o, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                  s32 a6, s32 a7, f32 x, f32 y, f32 z, s32 a8, s32 a9)
{
    EvTargetSetReset_336bb0(o);
    o->f114 = (s16)a1;
    TargetRefSetMapNode_2e6370(o, a2, a3, 0.0f);
    TargetRefSetMapNode_2e6370((u8 *)o + 0x30, a4, a5, 0.0f);
    TargetRefSetMapObj_2e6470((u8 *)o + 0x60, a6, a7, 0.0f);
    TargetRefSetMapObj_2e6470((u8 *)o + 0x90, a8, a9, 0.0f);
    o->f108 = x;
    o->f10C = y;
    o->f110 = z;
}
