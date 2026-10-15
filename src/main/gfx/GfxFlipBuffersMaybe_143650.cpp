#include "types.h"

typedef unsigned __int128 u128;

typedef struct GsFrame {
    u64 FBP:9;
    u64 p0:7;
    u64 FBW:6;
    u64 p1:2;
    u64 PSM:6;
    u64 p2:2;
    u64 FBMSK:32;
} GsFrame;

typedef struct GsZbuf {
    u64 ZBP:9;
    u64 p0:15;
    u64 PSM:4;
    u64 p1:4;
    u64 ZMSK:1;
    u64 p2:31;
} GsZbuf;

typedef struct GsXy {
    u64 OFX:16;
    u64 p0:16;
    u64 OFY:16;
    u64 p1:16;
} GsXy;

typedef struct GsSc {
    u64 SCAX0:11;
    u64 p0:5;
    u64 SCAX1:11;
    u64 p1:5;
    u64 SCAY0:11;
    u64 p2:5;
    u64 SCAY1:11;
    u64 p3:5;
} GsSc;

typedef struct GsTex0 {
    u64 TBP0:14;
    u64 TBW:6;
    u64 PSM:6;
    u64 TW:4;
    u64 TH:4;
    u64 TCC:1;
    u64 TFX:2;
    u64 CBP:14;
    u64 CPSM:4;
    u64 CSM:1;
    u64 CSA:5;
    u64 CLD:3;
} GsTex0;

typedef struct GsTex1 {
    u64 LCM:1;
    u64 p0:1;
    u64 MXL:3;
    u64 MMAG:1;
    u64 MMIN:3;
    u64 MTBA:1;
    u64 p1:9;
    u64 L:2;
    u64 p2:11;
    u64 K:12;
    u64 p3:20;
} GsTex1;

typedef struct Dispfb {
    u32 FBP:9;
    u32 FBW:6;
    u32 PSM:5;
    u32 p0:12;
    u32 DBX:11;
    u32 DBY:11;
    u32 p1:10;
} Dispfb;

typedef struct Env40 {
    u32 pmode[2];
    u32 smode2[2];
    Dispfb dispfb;      /* 0x54 */
    u32 display[2];
    u32 bgcolor[2];
} Env40;

typedef struct GifTag {
    u64 a;
    u64 b;
} GifTag;

typedef struct Regs {
    GsFrame frame;      /* 0x80 */
    u64 frameaddr;
    GsZbuf zbuf;        /* 0x90 */
    u64 zbufaddr;
    GsXy xyoffset;      /* 0xA0 */
    u64 xyoffsetaddr;
    GsSc scissor;       /* 0xB0 */
    u64 scissoraddr;
    u64 r[8];           /* 0xC0 */
} Regs;

typedef struct Clear {
    u64 r[12];
} Clear;

typedef struct DrawEnv {
    GifTag tag;         /* 0x70 */
    Regs r;             /* 0x80 */
} DrawEnv;

typedef struct F2 {
    f32 a, b;
} F2;

typedef struct F4 {
    f32 x, y, z, w;
} F4;

typedef struct Db {
    s32 f0;
    s32 w;              /* 0x04 */
    s32 h;              /* 0x08 */
    s32 cx;             /* 0x0C */
    s32 cy;             /* 0x10 */
    s32 vw;             /* 0x14 */
    s32 vh;             /* 0x18 */
    s32 f1C;
    s32 f20;
    s32 wait;           /* 0x24 */
    s32 sync;           /* 0x28 */
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    F2 f3C;
    Env40 env;          /* 0x44 */
    GifTag tag;         /* 0x70 */
    Regs r;             /* 0x80 */
    Clear clear;        /* 0x100 */
    F4 col;             /* 0x160 */
    s32 f170;
    s32 f174;
    s32 f178;
    s32 f17C;
    s32 f180;
    s32 f184;
    s32 f188;
} Db;

typedef struct Tex {
    u8 pad[0x38];
    GsTex0 tex0;        /* 0x38 */
    GsTex1 tex1;        /* 0x40 */
    u8 pad48[0x28];
} Tex;

typedef struct Pk {
    u32 w[4];
} Pk;

typedef struct Obj {
    u8 pad0[0x270];
    Db *db;             /* 0x270 */
    u8 pad274[0xF00 - 0x274];
    s32 last;           /* 0xF00 */
    s32 late;           /* 0xF04 */
    u8 padF08[0xC];
    s32 dirty;          /* 0xF14 */
    s32 padF18;
    s32 busy;           /* 0xF1C */
    u8 padF20[0x3D2C - 0xF20];
    s32 skip;           /* 0x3D2C */
} Obj;

extern "C" {
s32 sceDmaGetChan(s32);
s32 GetVsyncCount_15df00(void);
void WaitVsyncCount_15de90(s32, s32);
void FlushCache(s32);
void sceGsPutDrawEnv(void *);
void NameTableNodeCtor_15ae50(Tex *);
void DrawEnvGetFrameTexDesc_144cc0(Obj *, Tex *);
void sceGifPkInit_10a400(Pk *, void *);
void sceGifPkReset_10a410(Pk *);
void sceGifPkCnt(Pk *, s32, s32, s32);
void sceGifPkOpenGifTag(Pk *, u128);
void sceGifPkAddGsAD(Pk *, s32, u64);
void sceGifPkCloseGifTag(Pk *);
void sceGifPkEnd(Pk *, s32, s32, s32);
void sceGifPkTerminate_10a420(Pk *);
void sceDmaSync_10a2e0(s32, s32, s32);
void sceDmaSend_10a040(s32, void *);
void SyncDCache(void *, void *);
void GsDbufPutEnv_144150(Obj *);
extern u64 D_0047DE30;
extern u64 D_0047DE38;
extern u8 D_00490600[];
extern s32 D_00481080;
extern s32 D_00481084;
extern s32 D_00481088;
extern s32 D_0048108C;

}

#pragma optimization_level 3
#pragma opt_dead_assignments off
extern "C" void GfxFlipBuffersMaybe_143650(Obj *o)
{
    s32 ch;
    Db *d2;
    s32 u;
    s32 now;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 hx;
    s32 hy;
    Db *db;
    s32 hh;
    u64 v0;
    u64 v1;
    u64 vh;
    s32 t;
    s32 vw;
    s32 cx;
    s32 cy;
    u64 *p64;

    db = o->db;
    ch = sceDmaGetChan(2);
    now = GetVsyncCount_15df00();
    o->late = 0;
    if (now - o->last >= db->wait) {
        o->late = 1;
    }
    if (o->skip == 0) {
        if (o->late != 0 && db->sync != 0) {
            WaitVsyncCount_15de90(now, 1);
        } else {
            WaitVsyncCount_15de90(o->last, db->wait);
        }
    }
    o->last = GetVsyncCount_15df00();
    o->busy = 1;
    u64 tag[2] = { 0x1000000000008000, 0xE };
    Pk pk;
    Db da;
    Tex ta;
    Db dbb;
    Tex tb;
    if (db->h == db->vh) {
        da = *db;
        da.r.frame.FBP = db->env.dispfb.FBP;
        da.r.frame.PSM = db->env.dispfb.PSM;
        da.r.zbuf.ZMSK = 1;
        FlushCache(0);
        sceGsPutDrawEnv(&da.tag);
        NameTableNodeCtor_15ae50(&ta);
        DrawEnvGetFrameTexDesc_144cc0(o, &ta);
        ta.tex1.MMAG = 0;
        ta.tex1.MMIN = 0;
        ta.tex0.TFX = 1;
        d2 = o->db;
        hx = -(d2->h / 2);
        hy = -(d2->w / 2);
        x1 = hx + d2->h;
        y1 = hy + d2->w;
        *(volatile u32 *)0x10000000;
        x0 = hy + d2->cx;
        y0 = y1 + d2->cx;
        u = hx + d2->cy;
        hh = x1 + d2->cy;
        if (D_00481080 != y0 - x0 || D_00481084 != hh - u) {
            D_00481080 = y0 - x0;
            D_00481084 = t = hh - u;
            sceGifPkInit_10a400(&pk, D_00490600);
            sceGifPkReset_10a410(&pk);
            sceGifPkCnt(&pk, 0, 0, 0);
            sceGifPkOpenGifTag(&pk, *(u128 *)&tag[0]);
            sceGifPkAddGsAD(&pk, 0x42, 0x64 | ((u64)0x80 << 32));
            sceGifPkAddGsAD(&pk, 0x47, 0x20002);
            sceGifPkAddGsAD(&pk, 0x3B, 0x80 | ((u64)0x80 << 32));
            sceGifPkAddGsAD(&pk, 0x6, *(u64 *)&ta.tex0);
            sceGifPkAddGsAD(&pk, 0x14, *(u64 *)&ta.tex1);
            sceGifPkAddGsAD(&pk, 0x1B, 0x110);
            sceGifPkAddGsAD(&pk, 0x0, 6);
            sceGifPkAddGsAD(&pk, 0x1, ((u64)0x8080 << 16) | 0x8080);
            v0 = (u64)(u << 4) << 16;
            vh = (u64)(t << 4) << 16;
            v1 = (u64)(hh << 4) << 16;
            for (u = 0; x0 < y0; x0 += 16, u += 16) {
                sceGifPkAddGsAD(&pk, 0x3, u << 4);
                sceGifPkAddGsAD(&pk, 0x5, (x0 << 4) | v0);
                sceGifPkAddGsAD(&pk, 0x3, ((u + 16) << 4) | vh);
                sceGifPkAddGsAD(&pk, 0x5, ((x0 + 16) << 4) | v1);
            }
            sceGifPkCloseGifTag(&pk);
            sceGifPkEnd(&pk, 0, 0, 0);
            sceGifPkTerminate_10a420(&pk);
            FlushCache(0);
        }
        sceDmaSync_10a2e0(ch, 0, 0);
        sceDmaSend_10a040(ch, D_00490600);
        SyncDCache(db, (u8 *)db + 0x190);
        sceDmaSync_10a2e0(ch, 0, 0);
        sceGsPutDrawEnv(&db->tag);
        sceDmaSync_10a2e0(ch, 0, 0);
    } else {
        dbb = *db;
        dbb.r.frame.FBP = db->env.dispfb.FBP;
        dbb.r.frame.PSM = db->env.dispfb.PSM;
        dbb.r.zbuf.ZMSK = 1;
        FlushCache(0);
        sceGsPutDrawEnv(&dbb.tag);
        NameTableNodeCtor_15ae50(&tb);
        DrawEnvGetFrameTexDesc_144cc0(o, &tb);
        tb.tex1.MMAG = 1;
        tb.tex1.MMIN = 1;
        tb.tex0.TFX = 1;
        d2 = o->db;
        vw = db->vw;
        u = db->w;
        cx = d2->cx;
        cy = d2->cy;
        hh = db->h;
        x0 = cx - vw / 2;
        x1 = cx + vw / 2;
        y0 = cy - db->vh / 2;
        y1 = cy + db->vh / 2;
        *(volatile u32 *)0x10000000;
        if (D_00481080 != u || D_00481084 != hh || D_00481088 != db->vw || D_0048108C != db->vh) {
            D_00481080 = u;
            D_00481084 = hh;
            D_00481088 = db->vw;
            D_0048108C = db->vh;
            sceGifPkInit_10a400(&pk, D_00490600);
            sceGifPkReset_10a410(&pk);
            sceGifPkCnt(&pk, 0, 0, 0);
            sceGifPkOpenGifTag(&pk, *(u128 *)&tag[0]);
            y0 <<= 4;
            x0 <<= 4;
            sceGifPkAddGsAD(&pk, 0x18, x0 | ((u64)y0 << 32));
            sceGifPkAddGsAD(&pk, 0x40, ((u64)db->vw << 16) | ((u64)db->vh << 48));
            sceGifPkAddGsAD(&pk, 0x42, 0x64 | ((u64)0x80 << 32));
            sceGifPkAddGsAD(&pk, 0x47, 0x20002);
            sceGifPkAddGsAD(&pk, 0x3B, 0x80 | ((u64)0x80 << 32));
            sceGifPkAddGsAD(&pk, 0x6, *(u64 *)&tb.tex0);
            sceGifPkAddGsAD(&pk, 0x14, *(u64 *)&tb.tex1);
            sceGifPkAddGsAD(&pk, 0x1B, 0x110);
            sceGifPkAddGsAD(&pk, 0x0, 6);
            sceGifPkAddGsAD(&pk, 0x1, ((u64)0x8080 << 16) | 0x8080);
            sceGifPkAddGsAD(&pk, 0x3, 0);
            sceGifPkAddGsAD(&pk, 0x5, x0 | ((u64)y0 << 16));
            sceGifPkAddGsAD(&pk, 0x3, (u << 4) | ((u64)(hh << 4) << 16));
            sceGifPkAddGsAD(&pk, 0x5, (x1 << 4) | ((u64)(y1 << 4) << 16));
            sceGifPkAddGsAD(&pk, 0x3F, 0);
            p64 = (u64 *)((u32)&dbb.r.scissor);
            sceGifPkAddGsAD(&pk, 0x40, *p64);
            p64 = (u64 *)((u32)&dbb.r.xyoffset);
            sceGifPkAddGsAD(&pk, 0x18, *p64);
            sceGifPkCloseGifTag(&pk);
            sceGifPkEnd(&pk, 0, 0, 0);
            sceGifPkTerminate_10a420(&pk);
            FlushCache(0);
        }
        sceDmaSync_10a2e0(ch, 0, 0);
        sceDmaSend_10a040(ch, D_00490600);
        SyncDCache(db, (u8 *)db + 0x190);
        sceDmaSync_10a2e0(ch, 0, 0);
        sceGsPutDrawEnv(&db->tag);
        sceDmaSync_10a2e0(ch, 0, 0);
    }
    if (o->dirty != 0) {
        GsDbufPutEnv_144150(o);
        o->dirty = 0;
    }
    o->busy = 0;
}
