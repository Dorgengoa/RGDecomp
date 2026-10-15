#include "types.h"

typedef unsigned __int128 u128;

typedef struct GifTag {
    u64 NLOOP : 15;
    u64 EOP : 1;
    u64 pad16 : 16;
    u64 id : 14;
    u64 PRE : 1;
    u64 PRIM : 11;
    u64 FLG : 2;
    u64 NREG : 4;
    u64 REGS0 : 4;
    u64 REGS1 : 4;
    u64 REGS2 : 4;
    u64 REGS3 : 4;
    u64 REGS4 : 4;
    u64 REGS5 : 4;
    u64 REGS6 : 4;
    u64 REGS7 : 4;
    u64 REGS8 : 4;
    u64 REGS9 : 4;
    u64 REGS10 : 4;
    u64 REGS11 : 4;
    u64 REGS12 : 4;
    u64 REGS13 : 4;
    u64 REGS14 : 4;
    u64 REGS15 : 4;
} GifTag;

typedef struct Chcr {
    u64 DIR : 1;
    u64 pad1 : 1;
    u64 MOD : 2;
    u64 ASP : 2;
    u64 TTE : 1;
    u64 TIE : 1;
    u64 STR : 1;
    u64 pad9 : 7;
    u64 TAG : 16;
    u64 pad32 : 32;
} Chcr;

typedef struct Pk { s32 i0; s32 i4; u8 pad[8]; } Pk;

typedef struct Tex {
    s16 id;         /* 00 */
    s16 w;          /* 02 */
    s16 h;          /* 04 */
    s16 bpp;        /* 06 */
    char name[0x20];/* 08 */
    u8 pad28[0xA];
    u8 count;       /* 32 */
    u8 pad33;
    s16 cbp;        /* 34 */
    u8 pad36[2];
    u64 tex0;       /* 38 */
    u64 tex1;       /* 40 */
    u8 pad48[0x20];
} Tex;

typedef struct Hdr { u8 pad0[8]; s32 i8; u16 uC; u8 padE[5]; u8 kind; } Hdr;
typedef struct Img { u8 pad0[0x10]; Hdr hdr; u16 w; u16 h; } Img;
typedef struct G { u8 pad[0x178]; s32 i178; s32 i17C; } G;
typedef struct Ctx { u8 pad[0x270]; G *g; } Ctx;

#define SET_TEX0(tbp, tbw, psm, tw, th, tcc, tfx, cbp, cpsm, csm, csa, cld) \
    ((u64)(tbp) | ((u64)(tbw) << 14) | ((u64)(psm) << 20) | ((u64)(tw) << 26) | \
     ((u64)(th) << 30) | ((u64)(tcc) << 34) | ((u64)(tfx) << 35) | ((u64)(cbp) << 37) | \
     ((u64)(cpsm) << 51) | ((u64)(csm) << 55) | ((u64)(csa) << 56) | ((u64)(cld) << 61))

void sceGsSyncPath_109030(s32, s32);
void sceDmaSend_10a040(Chcr *, s32);
void sceGifPkInit_10a400(Pk *, u128 *);
void sceGifPkReset_10a410(Pk *);
void sceGifPkTerminate_10a420(Pk *);
s32 DrawEnvGetHeight_1451d0(Ctx *);
s32 DrawEnvGetWidth_1451e0(Ctx *);
u16 *DrawEnvGetZbufRegPtr_157760(G *);
void TexSetClutIndex_15a5b0(Tex *, s32);
void NameTableNodeReset_15ada0(Tex *);
void FlushCache(s32);
Chcr *sceDmaGetChan(s32);
void sceGifPkAddGsAD(Pk *, s32, u64);
void sceGifPkCloseGifTag(Pk *);
void sceGifPkCnt(Pk *, s32, s32, s32);
void sceGifPkEnd(Pk *, s32, s32, s32);
void sceGifPkOpenGifTag(Pk *, u128);
void sceGifPkRefLoadImage(Pk *, u16, u8, s32, void *, s32, s32, s32, s32, s32);
char *strcpy(char *, const char *);
extern char D_00458B38[];
extern Ctx *D_004810A4;
extern Tex D_00495CD0[];
extern Tex D_00495DA0[];

void FixedTexUploadImpl_15d680(s32 slot, Img *img, u8 *pal, s32 n, u8 flag) {
    Ctx *ctx;
    G *g;
    s32 maxw;
    s32 maxh;
    s32 w;
    s32 h;
    Hdr *hdr;
    s32 kind;
    s32 stride;
    s32 v;
    s32 i;
    s32 tw;
    s32 th;
    s32 p;
    s32 bpp;
    s32 psm;
    Tex *tex;
    u8 *data;
    u8 *clut;
    u8 *src;
    u128 *buf;
    s32 base;
    s32 cbp;
    Chcr *ch;
    u128 raw[0x64];
    Pk pk;
    union { u128 q; GifTag t; } tag;

    ctx = D_004810A4;
    g = ctx->g;
    maxw = DrawEnvGetWidth_1451e0(ctx);
    maxh = DrawEnvGetHeight_1451d0(ctx);
    w = img->w;
    h = img->h;
    hdr = &img->hdr;
    if (w > maxw) return;
    if (h > maxh) return;
    kind = hdr->kind;
    if (kind == 5) {
        if (slot != 0) return;
        if (n > 4) n = 4;
        stride = 0x400;
    } else if (kind == 4) {
        if (slot < 0 || slot >= 2) return;
        if (n > 16) n = 0x10;
        stride = 0x40;
    } else {
        return;
    }
    if (n == 0) n = 1;
    p = w;
    tw = 0;
    while (p >= 2) { p /= 2; tw++; }
    p = 1;
    for (i = 0; i < tw; i++) p *= 2;
    v = h;
    th = 0;
    while (v >= 2) { v /= 2; th++; }
    p = 1;
    for (i = 0; i < th; i++) p *= 2;
    if (h != p) th++;
    bpp = 8;
    psm = 0x1B;
    switch (kind) {
    case 5:
        goto c5;
    case 4:
        bpp = 4;
        if (slot) psm = 0x2C;
        else psm = 0x24;
        goto c5;
    }
    return;
c5:
    tex = &D_00495CD0[slot];
    if (!flag) tex = &D_00495DA0[slot];
    NameTableNodeReset_15ada0(tex);
    data = (u8 *)hdr + hdr->uC;
    clut = data + hdr->i8;
    if (pal != 0) clut = pal;
    buf = raw;
    if ((s32)buf % 4 != 0) buf += 4 - (s32)buf % 4;
    strcpy(tex->name, D_00458B38);
    tex->w = w;
    tex->h = h;
    tex->bpp = bpp;
    tex->id = 0;
    if (flag) {
        base = (*DrawEnvGetZbufRegPtr_157760(g) & 0x1FF) << 5;
        cbp = g->i178 + slot * 16;
    } else {
        base = g->i17C << 5;
        cbp = g->i178 + (slot + 2) * 16;
    }
    tex->tex0 = SET_TEX0(base, 8, psm, 9, th, 1, 0, cbp, 0, 0, 0, 1);
    tex->tex1 = 0x261;
    sceGifPkInit_10a400(&pk, buf);
    ch = sceDmaGetChan(2);
    ch->TTE = 1;
    sceGifPkReset_10a410(&pk);
    sceGifPkRefLoadImage(&pk, base, psm, 8, data, bpp * (w * h) / 16, 0, 0, w, h);
    tex->cbp = cbp;
    tex->count = n;
    for (i = 0; i < n; i++) {
        src = clut + stride * i;
        if (psm == 0x1B) {
            sceGifPkRefLoadImage(&pk, cbp, 0, 1, src, 0x40, 0, 0, 0x10, 0x10);
            cbp += 4;
        } else {
            sceGifPkRefLoadImage(&pk, cbp, 0, 1, src, 4, 0, 0, 8, 2);
            cbp += 1;
        }
    }
    sceGifPkCnt(&pk, 0, 0, 0);
    TexSetClutIndex_15a5b0(tex, 0);
    tag.q = 0;
    tag.t.EOP = 1;
    tag.t.NREG = 1;
    tag.t.REGS0 = 0xE;
    sceGifPkOpenGifTag(&pk, tag.q);
    sceGifPkAddGsAD(&pk, 0x3F, 0);
    sceGifPkCloseGifTag(&pk);
    sceGifPkEnd(&pk, 0, 0, 0);
    sceGifPkTerminate_10a420(&pk);
    FlushCache(0);
    ch->TTE = 1;
    if (data != 0) sceDmaSend_10a040(ch, pk.i4);
    sceGsSyncPath_109030(0, 0);
}
