/* rgp:protos */
#define RGP_SELF_DofWorkTexRegister_2f6a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN DofWorkTexRegister_2f6a30 -- one 0x31B surface sized from the current
   render target's DrawEnvGetWidth_1451e0 / DrawEnvGetHeight_1451d0. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern u8 D_00461D18[];

void DofWorkTexRegister_2f6a30(void)
{
    void *v;
    void *w;
    s32 cx;
    s32 cy;

    GameSceneDofSetOverridePreset_2f6ab0();
    v = GetDrawCtx_15de80();
    w = GetDrawCtxNameTable_15de40();
    cx = DrawEnvGetWidth_1451e0(v);
    cy = DrawEnvGetHeight_1451d0(v);
    NameTableAddEntry_159b70(w, 0x31B, D_00461D18, 0, cx, cy, 0x20, 0, (long long)(0), 0);
}
