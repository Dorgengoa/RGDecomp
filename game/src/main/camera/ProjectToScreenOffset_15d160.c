/* rgp:protos */
#define RGP_SELF_ProjectToScreenOffset_15d160 1
#define RGP_SELF_base 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: uses the sp30/sp34/sp38/sp3C output-buffer pattern (same
 * family as ProjectDepth_15d0a0.c in this lane, which the array-instead-of-scalar
 * fix did NOT fully close -- see that file's park note) PLUS two more
 * M2C_ERROR accumulator sites (mula.s/msub.s, ps2-float-accumulator lever)
 * feeding arg0->unk0/unk4; 0 round trips spent this session. Needs
 * asm/matchings/main/ProjectToScreenOffset_15d160.s read by hand for the accumulator
 * operands. Not attempted. */
/* s49m: 29 bad (right length) */
#include "types.h"

typedef struct View {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 pad1C[0x8];
    f32 unk24;
    f32 unk28;
} View;

typedef struct S004810A4 {
    u8 pad0[0xF20];
    s32 unkF20;
} S004810A4;

/*rgp*/
extern S004810A4 *D_004810A4;

static inline s32 base(void)
{
    s32 r;
    if (D_004810A4 == NULL) {
        return 0;
    }
    r = D_004810A4->unkF20;
    r = (s32)(u32)r;
    return r;
}

s32 ProjectToScreenOffset_15d160(s32 *out, f32 *in)
{
    View *vw;
    s32 ok;
    f32 v[4] __attribute__((aligned(16)));
    View *view;
    f32 r;
    s32 lim;

    view = (View *)(base() + 0x14);
    MtxMulPoint_13c890(v, base() + 0x1C0, in);
    r = 1.0f / v[3];
    v[0] *= r;
    v[1] *= r;
    v[2] *= r;
    out[0] = 16.0f * v[0];
    out[1] = 16.0f * v[1];
    out[2] = v[2];
    out[3] = 0;
    vw = (View *)(base() + 0x14);
    lim = 0xFFF;
    if (v[0] < 0.0f || !(v[0] <= (f32)lim)) {
        ok = 0;
    } else if (v[1] < 0.0f || !(v[1] <= (f32)lim)) {
        ok = 0;
    } else if (v[3] < vw->unkC || !(v[3] <= vw->unk10)) {
        ok = 0;
    } else {
        ok = 1;
    }
    out[0] = (f32)out[0] - (16.0f * view->unk24 - 8.0f * view->unk14);
    out[1] = (f32)out[1] - (16.0f * view->unk28 - 8.0f * view->unk18);
    return ok;
}
