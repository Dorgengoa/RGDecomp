#include "types.h"
#pragma divbyzerocheck on
#pragma opt_propagation off

typedef unsigned __int128 u128;

typedef struct Tex {
    u8 pad0[0x4];
    s16 unk4;
    u8 pad6[0x32];
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 rest : 38;
} Tex;

typedef struct Pkt {
    u8 pad0[0x28];
    s32 base;
    s32 count;
} Pkt;

typedef struct Rect {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
} Rect;

typedef struct Ctx {
    s32 idx;
    u32 *tag;
    s32 lists[74];
    u8 draw[0x140];
    u8 *work;
} Ctx;

extern void GsPktSetOriginMode_13e2f0(void *, s32);
extern void GsPktSetTextured_13e400(void *, s32);
extern void GsPktSetZWriteMask_13e430(void *, s32);
extern void GsPktSetZTest_13e450(void *, s32);
extern void GsPktEnableZTest_13e460(void *, s32);
extern void GsPktEnableAlphaTest_13e4d0(void *, s32);
extern void GsPktSetAlphaBlend_13e500(void *, s32);
extern void GsPktSetTexture_13ec00(void *, s32);
extern void GsPktSetUVFixed_13ed90(void *, s32, s32);
extern void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
extern void GsPktSetXYZ_13ef10(void *, s32, s32, s32);
extern void GsPktClose_13f5b0(void *);
extern void GsPktOpenPrim_13f730(void *, s32);
extern void *GsPktEnd_13f790(void *);
extern void GsPktBegin_13f7e0(void *);
extern void GsPktInit_13f7f0(void *, Pkt *, u32);
extern void DrawEnvPush_144830(void);
extern void MemStackAllocQw_14d950(Pkt *, s32);
extern s32 DrawEnvWritePacket_157460(u32, s32);
extern void DrawEnvSetFrame_1575e0(u32, u32, s32, s32, u64, s32);
extern const u128 D_0047DE40 __attribute__((section(".sdata")));

static inline Pkt *curpkt(Ctx *c) { s32 l = c->lists[c->idx]; Pkt *p; if (l != 0) p = (Pkt *)(l + 8); else p = 0; return p; }
#define PUTTAG(c, a) { *(u128 *)(c)->tag = D_0047DE40; (c)->tag[1] = (a) & 0x0FFFFFFF; (c)->tag += 4; }
static inline void closepkt(Ctx *c, Pkt *p, u32 w) { if (p != 0) { s32 e = p->base + p->count * 16; MemStackAllocQw_14d950(p, DrawEnvWritePacket_157460(w, e)); PUTTAG(c, e); } }
#define FLUSH(c) closepkt(c, curpkt(c), (u32)(c)->work)

static inline void tagif(Ctx *c, void *r) { if (r != 0) PUTTAG(c, (s32)r); }
static inline void wrapwork(Ctx *c) { if (c->work > (u8 *)c + 0x280) c->work -= 0x190; }
static inline void beginpkt(Ctx *c, Pkt *p, u32 w) { GsPktInit_13f7f0(c->draw, p, w); }
static inline void settex(Ctx *c, Tex *tex) { if (tex != 0) DrawEnvSetFrame_1575e0((u32)c->work, (u32)tex->tbp0 >> 5, tex->tbw << 6, tex->unk4, tex->psm, 0); }

void GfxBlitTexRect_141000(Ctx *self, s32 arg1, Rect *src, Tex *tex, Rect *dst) {
    void *draw;
    s32 w2;
    s32 w4;
    s32 m;
    s32 n;
    s32 i;
    void *r;
    Pkt *q;


    if (arg1 == 0 || tex == 0) return;
    DrawEnvPush_144830();
    settex(self, tex);
    FLUSH(self);
    beginpkt(self, curpkt(self), (u32)self->work);
    GsPktBegin_13f7e0(self->draw);
    draw = self->draw;
    GsPktSetOriginMode_13e2f0(draw, 0);
    GsPktEnableZTest_13e460(draw, 0);
    GsPktSetZWriteMask_13e430(draw, 1);
    GsPktSetZTest_13e450(draw, 0);
    GsPktSetAlphaBlend_13e500(draw, 0);
    GsPktEnableAlphaTest_13e4d0(draw, 0);
    GsPktSetTextured_13e400(draw, 0);
    GsPktSetTextured_13e400(draw, 1);
    GsPktOpenPrim_13f730(draw, 6);
    GsPktSetRGBAQ_13ee40(draw, 0x80, 0x80, 0x80, 0x80);
    GsPktSetTexture_13ec00(draw, arg1);
    w2 = src->y1 - src->y0;
    w4 = dst->y1 - dst->y0;
    if (w4 < w2) {
        m = w2;
    } else {
        m = w4;
    }
    n = m / 512;
    if (m % 512 != 0) {
        n++;
    }
    for (i = 0; i < n; i++) {
        s32 a = src->y0 + w2 * (i + 1) / n;
        s32 b = dst->y0 + w4 * i / n;
        s32 c = dst->y0 + w4 * (i + 1) / n;
        GsPktSetUVFixed_13ed90(draw, src->y0 + w2 * i / n, src->x0);
        GsPktSetXYZ_13ef10(draw, b, dst->x0, 0);
        GsPktSetUVFixed_13ed90(draw, a, src->x1);
        GsPktSetXYZ_13ef10(draw, c, dst->x1, 0);
    }
    GsPktClose_13f5b0(draw);
    r = GsPktEnd_13f790(self->draw);
    tagif(self, r);
    FLUSH(self);
    wrapwork(self);
    FLUSH(self);
}
