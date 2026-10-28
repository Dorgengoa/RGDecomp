/* rgp:protos */
#define RGP_SELF_MenuWinUpdate_26bfe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1FC __attribute__((section(".sdata")));

typedef struct {
    s32 n0;
    u8 pad4[0x3C];
    Vec4 v40;
    Vec4 v50;
    u8 pad60[0x30];
    Vec4 v90;
    Vec4 vA0;
    s32 nB0;
    s32 nB4;
    u8 padB8[0xC];
    s32 nC4;
    s32 nC8;
    f32 fCC;
} O26b;

void MenuWinUpdate_26bfe0(O26b *p, s32 arg1)
{
    Vec4 t40 __attribute__((aligned(16)));
    Vec4 t30 __attribute__((aligned(16)));
    f32 v;
    f32 d;

    if (p->nB0 > 0) {
        if (p->nB0 == 1) {
            p->v40 = p->v90;
        } else {
            VecSub_13be40(&t40, &p->v90, &p->v40);
            VecScale_13be00(&t40, &t40, 1.0f / (f32)p->nB0);
            VecAdd_13be20(&p->v40, &p->v40, &t40);
        }
        p->nB0--;
    }
    if (p->nB4 > 0) {
        if (p->nB0 == 1) {
            p->v40 = p->vA0;
        } else {
            VecSub_13be40(&t30, &p->vA0, &p->v50);
            VecScale_13be00(&t30, &t30, 1.0f / (f32)p->nB4);
            VecAdd_13be20(&p->v50, &p->v50, &t30);
        }
        p->nB4--;
    }
    if (p->n0 == 1) {
        if (p->nC4 != 0) {
            if (GetPauseStep_2f6660() == 0) {
                p->fCC = p->fCC + D_0047D1FC / (f32)p->nC8;
                if (!(p->fCC <= D_0047D1FC)) {
                    p->fCC = 0.0f;
                }
            }
            v = 128.0f * Sinf_128fd0(p->fCC);
            p->v50.w = v;
            if (v < 64.0f) {
                p->v50.w = 0.0f;
            } else {
                p->v50.w = 128.0f;
            }
        }
        MenuWinDraw_26b840(p, arg1);
    }
}
