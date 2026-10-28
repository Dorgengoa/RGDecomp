/* rgp:protos */
#define RGP_SELF_CBlurTexClearMaybe_179020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x3BA0];
    s32 unk3BA0;
} Obj0Ctx;

typedef struct {
    s16 pad0[1];
    s16 unk2;
    s16 unk4;
} Elem0Ret;

typedef struct {
    s32 unk0;
    u8 pad4[0x68 - 0x4];
    s32 unk68;
    s32 unk6C;
} Obj0Arg0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CBlurTexClearMaybe_179020(Obj0Arg0 *arg0)
{
    Obj0Ctx *ctx;
    s32 k;
    Elem0Ret *a;
    Elem0Ret *b;
    s32 x;
    s32 y;
    s32 h;

    if (arg0->unk0 == 0) {
        return;
    }
    ctx = ((Obj0Ctx *)GetDrawCtx_15de80());
    k = ctx->unk3BA0;
    a = ((Elem0Ret *)NameTableFindByName_159fb0(k, (u8 *)arg0 + 8, -1));
    b = ((Elem0Ret *)NameTableFindByName_159fb0(k, (u8 *)arg0 + 0x28, -1));
    if (a == NULL || b == NULL) {
        return;
    }
    {
        x = a->unk2;
        y = a->unk4;
        DrawEnvPush_144830(ctx);
        DrawEnvSetFrameFromDesc_144fe0(ctx, a, 0);
        DrawListAddEnv_1421d0(ctx);
        h = ((s32)DrawListBeginPrim_141b00(ctx));
        GsPktDisableTests_13f9e0(h);
        if ((arg0->unk68 == 0) && (arg0->unk6C == 0)) {
            GsPktSetFrameMask_13e420(h, 2);
        }
        arg0->unk68 = 0;
        GsPktOpenPrim_13f730(h, 6);
        GsPktSetTexture_13ec00(h, a);
        GsPktSetRGBAQ_13ee40(h, 0, 0, 0, 0);
        GsPktSetXYZPixel_13f110(h, 0, 0, 0);
        GsPktSetXYZPixel_13f110(h, x, y, 0);
        GsPktClose_13f5b0(h);
        DrawListEndPrim_141a20(ctx);
        DrawEnvPop_144800(ctx);
        DrawListAddEnv_1421d0(ctx);
    }
}
