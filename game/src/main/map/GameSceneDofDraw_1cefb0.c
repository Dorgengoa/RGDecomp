/* rgp:protos */
#define RGP_SELF_GameSceneDofDraw_1cefb0 1
#include "port/game_protos.h"
#line 1
#pragma opt_dead_assignments off
#include "types.h"

typedef struct { f32 x; f32 y; f32 z; } V3c;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern V3c D_0047E2F0 __attribute__((section(".sdata")));

typedef struct {
    u8 pad0[0x434c];
    s32 unk434C;
    u8 pad4350[0x1618];
    s32 unk5968;
    s32 unk596C;
    f32 unk5970;
    f32 unk5974;
    f32 unk5978;
    f32 unk597C;
} T1cefb0_arg0;

void GameSceneDofDraw_1cefb0(T1cefb0_arg0 *arg0, s32 arg1, s32 arg2)
{
    V3c col __attribute__((aligned(16)));
    f32 lv[4] __attribute__((aligned(16)));
    f32 f;
    f32 m;
    s32 i;
    s32 idx;
    s32 mode;
    s32 h;
    u8 *e;
    u8 *t;

    h = ((s32)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), arg1, arg2));
    if (h == 0) {
        return;
    }
    ObjRecGetLiveObject_1c5250(arg0, arg0->unk434C);
    e = ((u8 *)ObjRecGetLiveObject_1c5250(arg0, arg0->unk434C));
    if (e == NULL) {
        return;
    }
    t = e + 0x70;
    if (*(s32 *)(e + 0x224) == 0) {
        return;
    }
    TimeOfDayPhaseWeights_18d630(e, lv);
    f = 0.0f;
    if (*(s32 *)(t + 0x1B8) != 0) {
        for (i = 0; i < 4; i++) {
            if (*(s32 *)(t + i * 4 + 0x1BC) != 0) {
                if (f > lv[i]) {
                    m = f;
                } else {
                    m = lv[i];
                }
                f = m;
            }
        }
    } else {
        idx = 0;
        if (e != NULL) {
            idx = TimeOfDayPhase_18d890(e);
        }
        if (((s32 *)(t + 0x1BC))[idx] != 0) {
            f = 1.0f;
        }
    }
    *(V3c *)&col = D_0047E2F0;
    for (i = 0; i < 2; i++) {
        if (*(f32 *)(t + i * 4 + 0x1CC) != 0.0f) {
            ((f32 *)&col)[i] = *(f32 *)(t + i * 4 + 0x1CC);
        }
    }
    mode = 1;
    if (arg0->unk5968 != 0) {
        f = arg0->unk5970;
        mode = arg0->unk596C;
        col.x = arg0->unk5974;
        col.y = arg0->unk5978;
        col.z = arg0->unk597C;
    }
    if (f <= 0.0f) {
        return;
    }
    DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), arg2, 1.0f);
    DofFilterDrawMaybe_17d150(mode, (f32 *)&col, h, f);
}
