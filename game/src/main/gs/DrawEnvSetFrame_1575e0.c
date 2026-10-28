/* rgp:protos */
#define RGP_SELF_DrawEnvSetFrame_1575e0 1
#define RGP_SELF_setFrame 1
#define RGP_SELF_setXy 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct { __extension__ unsigned short FBP:9; unsigned short p0:7; unsigned char FBW:6; unsigned char p1:2; unsigned char  : 0, PSM:6; unsigned char p2:2; unsigned int FBMSK:32; } __attribute__((aligned(8))) GsFrame1575e0;
typedef struct { __extension__ unsigned short OFX:16; unsigned short  : 0, p0:16; unsigned short  : 0, OFY:16; unsigned short  : 0, p1:16; } __attribute__((aligned(8))) GsXyoffset1575e0;
typedef struct { __extension__ unsigned short SCAX0:11; unsigned short p0:5; unsigned short  : 0, SCAX1:11; unsigned short p1:5; unsigned short  : 0, SCAY0:11; unsigned short p2:5; unsigned short  : 0, SCAY1:11; unsigned short p3:5; } __attribute__((aligned(8))) GsScissor1575e0;
typedef struct { __extension__ unsigned long long DTHE:1; unsigned long long p0:63; } __attribute__((aligned(8))) GsDthe1575e0;

typedef struct S1575e0 {
    s32 pad0;
    s32 w;
    s32 h;
    s32 cx;
    s32 cy;
    u8 pad14[0x1C];
    s32 psm;
    u8 pad34[0x4C];
    GsFrame1575e0 frame;
    u64 frameAddr;
    u64 r90;
    u64 r98;
    GsXyoffset1575e0 xyoffset;
    u64 xyoffsetAddr;
    GsScissor1575e0 scissor;
    u64 scissorAddr;
    GsDthe1575e0 dthe;
    u64 dtheAddr;
} S1575e0;

static inline void setFrame(GsFrame1575e0 *f, s32 fbp, s32 fbw, s32 psm, s32 msk)
{
    f->FBP = fbp;
    f->FBW = fbw;
    f->PSM = psm;
    f->FBMSK = msk;
}

static inline void setXy(GsXyoffset1575e0 *xy, s32 x, s32 y)
{
    xy->OFX = x;
    xy->OFY = y;
}

void DrawEnvSetFrame_1575e0(S1575e0 *p, s32 fbp, s32 w, s32 h, s32 psm, s32 fbmsk)
{
    s32 aw;
    GsFrame1575e0 *f;
    GsXyoffset1575e0 *xy;

    p->w = w;
    aw = w;
    p->h = h;
    p->psm = psm;
    if (aw % 64 != 0) {
        aw += 64 - aw % 64;
    }
    f = &p->frame;
    xy = &p->xyoffset;
    p->frame.FBP = fbp;
    f->FBW = aw / 64;
    f->PSM = psm;
    f->FBMSK = fbmsk;
    xy->OFX = (p->cx - w / 2) << 4;
    xy->OFY = (p->cy - h / 2) << 4;
    p->scissor.SCAX0 = 0;
    p->scissor.SCAX1 = w - 1;
    p->scissor.SCAY0 = 0;
    p->scissor.SCAY1 = h - 1;
    p->dthe.DTHE = 0;
}
