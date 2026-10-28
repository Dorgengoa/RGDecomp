/* rgp:protos */
#define RGP_SELF_EffectCreateByName_2e1020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Out002E1020;

typedef struct {
    u8 pad0[0x407C];
    s32 unk407C;
} Ctx002E1020;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Key002E1020;

typedef struct {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    volatile s32 unkC;
    s32 unk10;
} R002E1020;

/*rgp*/
/*rgp*/
/*rgp*/

void EffectCreateByName_2e1020(Out002E1020 *ret, Ctx002E1020 *ctx, s32 arg2, s32 arg3) {
    struct {Key002E1020 k;u8 pad[4];R002E1020 r;} local;
    s32 x,y,z;
    s16 w;
    Out002E1020 a __attribute__((aligned(16)));
    Out002E1020 b __attribute__((aligned(16)));
    s32 *p;
    s32 t;

    t = ctx->unk407C + 1;
    ctx->unk407C = t;
    if (t > 1000000000) {
        ctx->unk407C = 0;
    }
    p = ((s32 *)EffectResFindByName_2e2f10(ctx, arg2));
    if (p != NULL) {
        local.k.unk8 = 0;
        local.k.unk4 = *p;
        EffectResCreateHandle_2e0f10(&a, ctx, &local.k);
        y=a.unk8;z=a.unk10;x=ctx->unk407C;w=a.unk0;
        ret->unk0=w;
        ret->unk4 = x;
        ret->unk8 = y;
        local.r.unkC = ret->unkC = a.unkC;
        ret->unk10 = z;
    } else {
        EffectEntryCreateHandle_2de930(&b, (u8 *)ctx + 0x1674, arg2, arg3, ctx->unk407C);
        y=b.unk8;z=b.unk10;x=ctx->unk407C;w=b.unk0;
        ret->unk0=w;
        ret->unk4 = x;
        ret->unk8 = y;
        local.r.unkC = ret->unkC = b.unkC;
        ret->unk10 = z;
    }
}
