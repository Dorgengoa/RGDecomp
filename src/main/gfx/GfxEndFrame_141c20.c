#include "types.h"
#pragma optimization_level 3

typedef unsigned __int128 u128;

typedef struct G { u8 pad0[4]; s32 w; s32 h; u8 pad0C[0x18]; s32 i24; u8 pad28[4]; s32 i2C; } G;
typedef struct Slot { s32 on; s32 x; s32 y; s32 z; } Slot;
typedef union Pkt { u128 q; u32 w[4]; } Pkt;
typedef struct Buf { u8 pad[0x28]; s32 i28; s32 i2C; } Buf;
typedef struct Z { u32 z : 24; u32 s : 8; } Z;
typedef struct StoreImage { u8 pad[0x70]; } StoreImage;

typedef struct Self {
    s32 idx;            /* 0 */
    Pkt *pkt;           /* 4 */
    s32 *bufs[2];       /* 8 */
    u8 pad10[0x120];
    u8 o130[0x140];     /* 130 */
    G *g;               /* 270 */
    u8 pad274[0xF10 - 0x274];
    f32 fF10;           /* F10 */
    u8 padF14[4];
    s32 iF18;           /* F18 */
    s32 iF1C;           /* F1C */
    u8 padF20[0x36B0 - 0xF20];
    s32 i36B0;          /* 36B0 */
    u8 pad36B4[0x3CD0 - 0x36B4];
    Slot slots[4];      /* 3CD0 */
    u8 pad3D10[0x14];
    f32 f3D24;          /* 3D24 */
    f32 f3D28;          /* 3D28 */
    s32 i3D2C;          /* 3D2C */
} Self;

void sceGsSyncPath_109030(s32, s32);
void GsPktSetTextured_13e400(void *, s32);
void GsPktSetZWriteMask_13e430(void *, s32);
void GsPktSetZTest_13e450(void *, s32);
void GsPktEnableZTest_13e460(void *, s32);
void GsPktEnableAlphaTest_13e4d0(void *, s32);
void GsPktSetAlphaBlend_13e500(void *, s32);
void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
void GsPktSetXYZPixel_13f110(void *, s32, s32, s32);
void GsPktClose_13f5b0(void *);
void GsPktOpenPrim_13f730(void *, s32);
u32 GsPktEnd_13f790(void *);
void GsPktBegin_13f7e0(void *);
void GsPktInit_13f7f0(void *, void *, G *);
void GfxDrawPerfMeter_1431c0(Self *, f32, f32);
void GfxFlipBuffersMaybe_143650(Self *);
void MemStackAllocQw_14d950(Buf *, s32);
s32 DrawEnvWritePacket_157460(G *, s32);
u16 *DrawEnvGetZbufRegPtr_157760(G *);
void Vif1DmaHandlerShutdown_15dfb0(void);
void Vif1DmaStart_15e070(s32);
void FlushCache(s32);
void sceGsExecStoreImage(StoreImage *, void *);
void sceGsSetDefStoreImage(StoreImage *, s16, s16, s16, s16, s16, s16, s16);
extern const u128 D_0047DE40 __attribute__((section(".sdata")));
extern s32 D_004810B4;

#define T0_COUNT (*(volatile u32 *)0x10000000)

static inline f32 fmx(f32 a, f32 b) { return (a <= b) ? b : a; }
void GfxEndFrame_141c20(Self *self, s32 flag) {
    G *g;
    f32 div;
    f32 t0;
    f32 t1;
    s32 i;
    s32 w;
    s32 h;
    s32 bw;
    Slot *sl;
    s32 x;
    s32 y;
    s32 bp;
    StoreImage si;
    Z buf[0x400];
    s32 m;
    s32 k;
    s32 v;
    s32 *cur;
    u8 *o;
    u32 r;
    Buf *b;
    s32 a;
    Pkt *p;
    G *gg;
    Z *zp;

    if (self->iF18 == 0) return;
    g = self->g;
    div = (f32)g->i2C;
    t0 = (f32)T0_COUNT / div;
    Vif1DmaHandlerShutdown_15dfb0();
    self->iF1C = 0;
    i = 0;
    t1 = (f32)D_004810B4;
    (void)T0_COUNT;
    w = self->g->w;
    h = self->g->h;
    t1 = t1 / div;
    bw = w / 64;
    do {
        sl = &self->slots[i];
        if (self->slots[i].on != 0) {
            x = sl->x;
            if (x < 4 || x > w - 4) {
                sl->z = -1;
            } else {
                y = sl->y;
                if (y < 4 || y > h - 4) {
                    sl->z = -1;
                } else {
                    bp = *DrawEnvGetZbufRegPtr_157760(g) & 0x1FF;
                    sceGsSetDefStoreImage(&si, (bp << 11) / 64, bw, 0x30, x - 4, y - 4, 8, 8);
                    FlushCache(0);
                    sceGsExecStoreImage(&si, buf);
                    sceGsSyncPath_109030(0, 0);
                    k = 0;
                    zp = buf + k;
                    m = zp->z;
                    for (; k < 64; k++) {
                        v = (&zp[k])->z;
                        if (v < m) m = v;
                    }
                    sl->z = m;
                }
            }
        }
        i++;
    } while (i < 4);
    cur = self->bufs[self->idx];
    if (cur == 0) return;
    if (flag) {
        gg = self->g;
        GsPktInit_13f7f0(self->o130, cur ? (u8 *)cur + 8 : 0, gg);
        GsPktBegin_13f7e0(self->o130);
        o = self->o130;
        h = self->g->h;
        w = self->g->w;
        GsPktEnableZTest_13e460(o, 0);
        GsPktSetZTest_13e450(o, 0);
        GsPktEnableAlphaTest_13e4d0(o, 0);
        GsPktSetTextured_13e400(o, 0);
        GsPktSetAlphaBlend_13e500(o, 0);
        GsPktSetZWriteMask_13e430(o, 0);
        GsPktOpenPrim_13f730(o, 2);
        GsPktSetRGBAQ_13ee40(o, 1, 1, 1, 0);
        GsPktSetXYZPixel_13f110(o, 0, 0, 0);
        GsPktSetXYZPixel_13f110(o, w - 1, 0, 0);
        GsPktSetXYZPixel_13f110(o, w - 1, h - 1, 0);
        GsPktSetXYZPixel_13f110(o, 0, h - 1, 0);
        GsPktSetXYZPixel_13f110(o, 0, 0, 0);
        GsPktClose_13f5b0(o);
        r = GsPktEnd_13f790(o);
        if (r != 0) {
            self->pkt->q = D_0047DE40;
            self->pkt->w[1] = (u32)r & 0x0FFFFFFF;
            self->pkt++;
        }
        gg = self->g;
        b = self->bufs[self->idx] ? (Buf *)((u8 *)self->bufs[self->idx] + 8) : 0;
        if (b != 0) {
            a = b->i28 + b->i2C * 16;
            MemStackAllocQw_14d950(b, DrawEnvWritePacket_157460(gg, a));
            self->pkt->q = D_0047DE40;
            self->pkt->w[1] = (u32)a & 0x0FFFFFFF;
            self->pkt++;
        }
        self->f3D24 = 100.0f * t0 / (f32)g->i24;
        self->f3D28 = 100.0f * t1 / (f32)g->i24;
        GfxDrawPerfMeter_1431c0(self, self->f3D24, self->f3D28);
        GfxFlipBuffersMaybe_143650(self);
        t1 = (t1 > t0) ? t1 : t0;
        self->fF10 = t1;
        if (self->fF10 <= (f32)g->i24) self->fF10 = (f32)g->i24;
        if (!(self->fF10 <= 2.0f * (f32)g->i24)) self->fF10 = 2.0f * (f32)g->i24;
    }
    self->pkt->q = 0;
    self->pkt->w[0] = 0x70000003;
    self->pkt++;
    self->pkt->q = 0;
    self->pkt->w[0] = 0x13000000;
    self->pkt++;
    self->pkt->q = 0;
    self->pkt->w[0] = 0x07000000;
    self->pkt->w[1] = 0;
    self->pkt->w[2] = 0;
    self->pkt->w[3] = 0;
    self->pkt++;
    self->pkt->q = 0;
    self->pkt->w[0] = 0x80000000;
    if (self->i3D2C == 0) {
        self->iF1C = 1;
        Vif1DmaStart_15e070(*cur);
    }
    self->idx = (u8)((self->idx != 0) ^ 1);
    T0_COUNT = 0;
    self->iF18 = 0;
    self->i36B0 = 0;
}
