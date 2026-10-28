#include "types.h"

typedef struct W64 {
    u32 lo;
    u32 hi;
} W64;

typedef struct Dispfb {
    __extension__ unsigned int FBP:9;
    unsigned int FBW:6;
    unsigned int PSM:5;
    unsigned int p0:12;
    unsigned int  : 0, DBX:11;
    unsigned int DBY:11;
    unsigned int p1:10;
} __attribute__((aligned(4))) Dispfb;

typedef struct Display {
    __extension__ unsigned int DX:12;
    unsigned int DY:11;
    unsigned int MAGH:4;
    unsigned int MAGV:2;
    unsigned int p0:3;
    unsigned int  : 0, DW:12;
    unsigned int DH:11;
    unsigned int p1:9;
} __attribute__((aligned(4))) Display;

typedef struct DispEnv {
    W64 pmode;
    W64 smode2;
    W64 dispfb;
    W64 display;
    W64 bgcolor;
} DispEnv;

typedef struct GifTag {
    u64 lo;
    u64 hi;
} GifTag;

typedef struct Frame {
    __extension__ unsigned short FBP:9;
    unsigned short p0:7;
    unsigned char FBW:6;
    unsigned char p1:2;
    unsigned char  : 0, PSM:6;
    unsigned char p2:2;
    unsigned int FBMSK:32;
} __attribute__((aligned(8))) Frame;

typedef struct Zbuf {
    __extension__ unsigned int ZBP:9;
    unsigned int p0:15;
    unsigned int PSM:4;
    unsigned int p1:4;
    unsigned int  : 0, ZMSK:1;
    unsigned int p2:31;
} __attribute__((aligned(8))) Zbuf;

typedef struct DrawEnv1 {
    u64 frame1;
    u64 frame1addr;
    u64 zbuf1;
    u64 zbuf1addr;
    u64 xyoffset1;
    u64 xyoffset1addr;
    u64 scissor1;
    u64 scissor1addr;
    u64 prmodecont;
    u64 prmodecontaddr;
    u64 colclamp;
    u64 colclampaddr;
    u64 dthe;
    u64 dtheaddr;
    u64 test1;
    u64 test1addr;
} DrawEnv1;

typedef struct Rgbaq {
    u8 R;
    u8 G;
    u8 B;
    u8 A;
    f32 Q;
} Rgbaq;

typedef struct Clear {
    u64 testa;
    u64 testaaddr;
    u64 prim;
    u64 primaddr;
    Rgbaq rgbaq;
    u64 rgbaqaddr;
    u64 xyz2a;
    u64 xyz2aaddr;
    u64 xyz2b;
    u64 xyz2baddr;
    u64 testb;
    u64 testbaddr;
} Clear;

typedef struct DBuff {
    DispEnv disp[2];
    GifTag giftag0;
    DrawEnv1 draw0;
    Clear clear0;
    GifTag giftag1;
    DrawEnv1 draw1;
    Clear clear1;
} DBuff;

typedef struct Gfx {
    s32 mode;
    s32 w;
    s32 h;
    u8 padC[8];
    s32 w2;
    s32 h2;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 psm;
    s32 zpsm;
    s32 m38;
    u8 pad3C[8];
    DispEnv disp;
    GifTag giftag;
    DrawEnv1 draw;
    Clear clear;
    f32 m160;
    f32 m164;
    f32 m168;
    s32 m16C;
    s32 m170;
    s32 m174;
    s32 m178;
    s32 m17C;
    s32 m180;
    s32 m184;
    s32 m188;
} Gfx;

typedef struct Obj1451 {
    u8 pad0[0x270];
    Gfx *gfx;
    u8 pad274[0xF10 - 0x274];
    f32 mF10;
} Obj1451;

extern "C" void sceGsResetGraph_108110(s16, s16, s16, s16);
extern "C" void sceGsSetDefDispEnv_1083c8(DBuff *, s16, s16, s16, s16, s16);
extern "C" void sceGsSyncPath_109030(s32, s32);
extern "C" void GsDbufPutEnv_144150(Obj1451 *);
extern "C" void DrawEnvSetCenter_157560(Gfx *, s32, s32);
extern "C" void DrawEnvSetFrame_1575e0(Gfx *, s32, s32, s32, s32, s32);
extern "C" void FlushCache(s32);
extern "C" void sceGsSetDefDBuff(DBuff *, s16, s16, s16, s16, s16, s16);
extern "C" void sceGsSetDefDrawEnv(DrawEnv1 *, s16, s16, s16, s16, s16);
extern "C" void sceGsSwapDBuff(DBuff *, s32);
extern "C" void sceGsSyncV(s32);

extern "C" { static s32 GsCalcBufferBlocks_140db0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 temp_2;
    s32 temp_4;
    s32 temp_6;
    s32 temp_6_2;
    s32 var_2;
    s32 var_2_2;
    s32 var_3;
    s32 var_3_2;
    s32 var_4;
    s32 var_5;
    s32 var_6;
    s32 var_6_2;

    var_4 = arg0;
    var_5 = arg1;
    var_2_2 = 0;
    switch (arg2) {
    case 0x0:
    case 0x1:
    case 0x30:
    case 0x31:
        var_2_2 = 0x20;
        temp_6 = var_4 % 64;
        if (temp_6 != 0) {
            var_4 += 0x20 - temp_6;
        }
        var_6 = var_5 & 0x1F;
        if ((var_5 < 0) && (var_6 != 0)) {
            var_6 -= 0x20;
        }
        if (var_6 != 0) {
            var_3 = 0x20 - var_6;
            var_5 += var_3;
        }
        break;
    case 0x2:
    case 0xA:
    case 0x32:
    case 0x3A:
        var_2_2 = 0x10;
        temp_6_2 = var_4 % 64;
        if (temp_6_2 != 0) {
            var_4 += 0x20 - temp_6_2;
        }
        var_6_2 = var_5 & 0x3F;
        if ((var_5 < 0) && (var_6_2 != 0)) {
            var_6_2 -= 0x40;
        }
        if (var_6_2 != 0) {
            var_3 = 0x40 - var_6_2;
            var_5 += var_3;
        }
        break;
    }
    temp_2 = var_2_2 * (var_4 * var_5);
    var_3_2 = temp_2 >> 3;
    if (temp_2 < 0) {
        var_3_2 = (s32)(temp_2 + 7) >> 3;
    }
    var_2 = var_3_2 >> 8;
    if (var_3_2 < 0) {
        var_2 = (s32)(var_3_2 + 0xFF) >> 8;
    }
    temp_4 = var_2 % 32;
    if (temp_4 != 0) {
        var_2 += 0x20 - temp_4;
    }
    return var_2;
}
}

extern "C" void NameTableNodeReset_15ada0(void *);

typedef struct Tex0_a {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
} Tex0_a;

typedef struct Node_a {
    u8 pad0[2];
    s16 w;
    s16 h;
    s16 bpp;
    u8 pad8[0x20];
    u16 size;
    u8 pad2A[2];
    s32 size2;
    s16 f30;
    u8 pad32[6];
    Tex0_a tex0;
    u64 f40;
} Node_a;

typedef struct Hdr_a {
    __extension__ unsigned int tbp : 9;
    unsigned int tbw : 6;
    unsigned int psm : 5;
    unsigned int rest : 12;
} __attribute__((aligned(4))) Hdr_a;

typedef struct Img_a {
    u8 pad0[0x14];
    s32 w;
    s32 h;
    u8 pad1C[0x38];
    Hdr_a hdr;
} Img_a;

typedef struct Obj_a {
    u8 pad[0x270];
    Img_a *img;
} Obj_a;


extern "C" void DrawEnvGetDispFbTexDesc_144a00(Obj_a *o, Node_a *node)
{
    Img_a *img;
    s32 w;
    s32 h;
    Hdr_a *hdr;
    s32 bpp;
    s32 n;
    s32 m;
    s32 t;
    s32 i;
    s32 p;

    img = o->img;
    NameTableNodeReset_15ada0(node);
    w = img->w;
    h = img->h;
    node->w = w;
    node->h = h;
    hdr = &img->hdr;
    switch (hdr->psm) {
    case 0: bpp = 32; break;
    case 1: bpp = 24; break;
    case 2: bpp = 16; break;
    case 0xA: bpp = 16; break;
    case 0x13: bpp = 8; break;
    case 0x14: bpp = 4; break;
    case 0x30: bpp = 32; break;
    case 0x31: bpp = 24; break;
    case 0x32: bpp = 16; break;
    case 0x3A: bpp = 16; break;
    default: bpp = 32; break;
    }
    node->bpp = bpp;
    node->size = GsCalcBufferBlocks_140db0(w, h, hdr->psm);
    node->size2 = node->size;
    node->f30 = 0;
    *(u64 *)&node->tex0 = 0;
    node->tex0.tbp0 = hdr->tbp << 5;
    node->tex0.tbw = hdr->tbw;
    node->tex0.psm = hdr->psm;
    n = 0;
    m = 0;
    for (t = w; t > 1; t >>= 1) n++;
    for (p = 1, i = 0; i < n; i++) p <<= 1;
    if (w != p) n++;
    for (t = h; t > 1; t >>= 1) m++;
    for (p = 1, i = 0; i < m; i++) p <<= 1;
    if (h != p) m++;
    node->tex0.tw = n;
    node->tex0.th = m;
    node->tex0.tcc = 1;
    node->tex0.tfx = 0;
    node->f40 = 0x261;
}

typedef struct Tex0_c {
    u64 tbp0 : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
} Tex0_c;

typedef struct Node_c {
    u8 pad0[2];
    s16 w;
    s16 h;
    s16 bpp;
    u8 pad8[0x20];
    u16 size;
    u8 pad2A[2];
    s32 size2;
    s16 f30;
    u8 pad32[6];
    Tex0_c tex0;
    u64 f40;
} Node_c;

typedef struct Hdr_c {
    __extension__ unsigned short tbp : 9;
    unsigned short pad : 7;
    unsigned char tbw : 6;
    unsigned char pad2 : 2;
    unsigned char  : 0, psm : 6;
    unsigned char pad3 : 2;
} __attribute__((aligned(2))) Hdr_c;

typedef struct Img_c {
    s32 f0;
    s32 w;
    s32 h;
    u8 pad[0x74];
    Hdr_c hdr;
} Img_c;

typedef struct Obj_c {
    u8 pad[0x270];
    Img_c *img;
} Obj_c;


extern "C" void DrawEnvGetFrameTexDesc_144cc0(Obj_c *o, Node_c *node)
{
    Img_c *img;
    s32 w;
    s32 h;
    Hdr_c *hdr;
    s32 bpp;
    s32 n;
    s32 m;
    s32 t;
    s32 i;
    s32 p;

    img = o->img;
    NameTableNodeReset_15ada0(node);
    w = img->w;
    h = img->h;
    node->w = w;
    node->h = h;
    hdr = &img->hdr;
    switch (hdr->psm) {
    case 0: bpp = 32; break;
    case 1: bpp = 24; break;
    case 2: bpp = 16; break;
    case 0xA: bpp = 16; break;
    case 0x13: bpp = 8; break;
    case 0x14: bpp = 4; break;
    case 0x30: bpp = 32; break;
    case 0x31: bpp = 24; break;
    case 0x32: bpp = 16; break;
    case 0x3A: bpp = 16; break;
    default: bpp = 32; break;
    }
    node->bpp = bpp;
    node->size = GsCalcBufferBlocks_140db0(w, h, hdr->psm);
    node->size2 = node->size;
    node->f30 = 0;
    *(u64 *)&node->tex0 = 0;
    node->tex0.tbp0 = hdr->tbp << 5;
    node->tex0.tbw = hdr->tbw;
    node->tex0.psm = hdr->psm;
    n = 0;
    m = 0;
    for (t = w; t > 1; t >>= 1) n++;
    for (p = 1, i = 0; i < n; i++) p <<= 1;
    if (w != p) n++;
    for (t = h; t > 1; t >>= 1) m++;
    for (p = 1, i = 0; i < m; i++) p <<= 1;
    if (h != p) m++;
    node->tex0.tw = n;
    node->tex0.th = m;
    node->tex0.tcc = 1;
    node->tex0.tfx = 0;
    node->f40 = 0x261;
}

extern "C" s32 GfxSetVideoMode_1451f0(Obj1451 *o, s32 mode)
{
    DBuff db __attribute__((aligned(16)));
    s32 a;
    bool flag;
    s32 inter;
    s32 omode;
    s32 ff;
    DBuff *dbp;
    Gfx *p;

    flag = false;
    inter = 1;
    omode = 2;
    p = o->gfx;
    ff = 0;
    p->mode = mode;
    switch (mode) {
    case 6:
        omode = 0x50;
    case 2:
        p->w = 0x200;
        p->h = 0x1C0;
        break;
    case 7:
        omode = 0x50;
    case 3:
        p->w = 0x280;
        p->h = 0x1A0;
        break;
    case 8:
        omode = 0x50;
    case 4:
        p->w = 0x280;
        p->h = 0x1C0;
        break;
    case 9:
        p->w = 0x200;
        p->h = 0x1A0;
        omode = 3;
        break;
    case 10:
        p->w = 0x200;
        p->h = 0x1C0;
        omode = 3;
        break;
    case 12:
        p->w = 0x280;
        p->h = 0x1A0;
        omode = 3;
        break;
    case 13:
        p->w = 0x280;
        p->h = 0x1C0;
        omode = 3;
        break;
    case 11:
        p->w = 0x200;
        p->h = 0x1E0;
        omode = 3;
        break;
    case 14:
        p->w = 0x280;
        p->h = 0x1E0;
        omode = 3;
        break;
    case 17:
        omode = 3;
    case 15:
        p->w = 0x200;
        flag = true;
        p->h = 0x1C0;
        p->w2 = 0x200;
        p->h2 = 0x200;
        break;
    case 18:
        omode = 3;
    case 16:
        p->w = 0x200;
        flag = true;
        p->h = 0x1E0;
        p->w2 = 0x200;
        p->h2 = 0x200;
        break;
    case 5:
        omode = 0x50;
    default:
        p->w = 0x200;
        p->h = 0x1A0;
        p->mode = 1;
        break;
    }
    p->m1C = 1;
    p->m24 = 2;
    p->m28 = 0;
    if (omode == 3) {
        p->m2C = 0x13A;
    } else {
        p->m2C = 0x106;
    }
    o->mF10 = (f32)p->m24;
    if (omode == 0x50) {
        inter = 0;
        ff = 1;
        p->m2C = p->m2C * 2;
    }
    if (!flag) {
        p->w2 = p->w;
        p->h2 = p->h;
    }
    p->m20 = 0x1C0;
    if (omode == 3) {
        p->m20 = 0x200;
    }
    p->psm = 0;
    p->zpsm = 1;
    p->m38 = 0x31;
    DrawEnvSetCenter_157560(p, 0, 0);
    dbp = &db;
    sceGsSyncV(0);
    sceGsResetGraph_108110(0, inter, omode, ff);
    sceGsSetDefDBuff(dbp, p->psm, p->w, p->h, 3, p->zpsm, 0);
    sceGsSetDefDispEnv_1083c8(dbp, p->zpsm, p->w2, p->h2, 0, 0);
    sceGsSetDefDrawEnv(&db.draw0, p->psm, p->w, p->h, 3, p->m38);
    ((Frame *)&db.draw0.frame1)->FBP = 0;
    a = GsCalcBufferBlocks_140db0(p->w, p->h, p->psm) / 32;
    inter = GsCalcBufferBlocks_140db0(p->w2, p->h2, p->zpsm) / 32;
    ff = GsCalcBufferBlocks_140db0(p->w, p->h, p->m38) / 32;
    ((Dispfb *)&db.disp[0].dispfb)->FBP = a;
    ((Zbuf *)&db.draw0.zbuf1)->ZBP = ((Dispfb *)&db.disp[0].dispfb)->FBP + inter;
    if (omode == 0x50) {
        ((Display *)&dbp->disp[0].display)->DY += (0x1E0 - p->h) / 2;
    } else if (p->h2 > 0xF0 && p->h2 <= 0x1C0) {
        ((Display *)&dbp->disp[0].display)->DY += (0x1C0 - p->h2) / 2;
    } else if (p->h2 <= 0x1E0) {
        ((Display *)&dbp->disp[0].display)->DY += (0x1E0 - p->h2) / 2;
    }
    p->m170 = (((Zbuf *)&dbp->draw0.zbuf1)->ZBP + ff) << 5;
    p->m174 = 0x3FC0;
    p->m178 = 0x3FC0;
    dbp->disp[1] = dbp->disp[0];
    dbp->draw1 = dbp->draw0;
    dbp->clear0.rgbaq.R = dbp->clear0.rgbaq.G = dbp->clear0.rgbaq.B = 0x40;
    dbp->clear0.rgbaq.A = 0;
    dbp->clear0.rgbaq.Q = 1.0f;
    p->m160 = 64.0f;
    p->m164 = 64.0f;
    p->m168 = 64.0f;
    p->m16C = 0;
    sceGsSyncPath_109030(0, 0);
    FlushCache(0);
    sceGsSwapDBuff(dbp, 0);
    p->disp = dbp->disp[0];
    p->giftag = dbp->giftag0;
    p->draw = dbp->draw0;
    p->clear = dbp->clear0;
    DrawEnvSetFrame_1575e0(p, ((Frame *)&p->draw.frame1)->FBP, p->w, p->h, ((Frame *)&p->draw.frame1)->PSM, 0);
    p->m17C = ((Dispfb *)&p->disp.dispfb)->FBP;
    p->m180 = inter;
    p->m184 = ((Dispfb *)&p->disp.dispfb)->PSM;
    p->m188 = ff;
    GsDbufPutEnv_144150(o);
    return p->mode;
}
