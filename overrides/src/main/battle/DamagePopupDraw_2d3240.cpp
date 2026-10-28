/* rg-override: replaces game/src/main/battle/DamagePopupDraw_2d3240.cpp sha256 149f936d51a95615515d5c7d6b1669d766c9ed90096f74b7634039297454a1ed
 * why: widescreen stage 2 (docs/WIDESCREEN.md "Stage 2", world-anchored text): each damage number / damage sprite is squeezed about its projected point (rg_layout_about_*; no-op at 4:3) */
#include "types.h"
/* rg-override: widescreen stage 2 world-anchored text (src/settings/rg_layout.h) */
extern "C" void rg_layout_about_begin(float ax, int screen_px);
extern "C" void rg_layout_about_end(void);
#include "vec.h"

class Cam {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;     
         
         
         
         
      void f32() { VCM0(void, 0x88); }   
      
    void GetPos(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); } /* 0xA4 */
};

typedef struct Pop {
    f32 pos[4];         /* 0x00 */
    f32 col[3];         /* 0x10 */
    f32 x1C;            /* 0x1C */
    u8 pad20[8];
    f32 x28;            /* 0x28 */
    s16 x2C;            /* 0x2C */
    s16 x2E;            /* 0x2E */
    s32 x30;            /* 0x30 */
    u8 pad34[4];
    s32 x38;            /* 0x38 */
    u8 x3C;             /* 0x3C */
} Pop;

typedef struct Ent {
    s32 key;
    s32 u;
    s32 v;
    s32 w;
    s32 h;
} Ent;

typedef struct Tbl {
    Ent e[5];
} Tbl;

typedef struct Sys {
    u8 pad0[0x4344];
    s32 x4344;
} Sys;

extern "C" {
void Sprintf_1343b8(char *, char *, s32);
f32 VecDistSq_13d360(Vec4 *, Pop *);
void GsPktSetTexture_13ec00(s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetRGBAQVec_13edd0(s32, f32 *);
void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
s32 DrawEnvGetTop_1450c0(s32);
s32 DrawEnvGetLeft_1450f0(s32);
s32 DrawEnvGetHeight_1451d0(s32);
s32 DrawEnvGetWidth_1451e0(s32);
s32 NameTableFindByName_159fb0(s32, char *, s32);
s32 ProjectToScreen_15d340(s32 *, Pop *);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
Cam *ObjRecGetLiveObject_1c3bc0(Sys *, s32);
Sys *GetCurrentScene_1f5be0(void);
void memset(void *, s32, s32);
void sceVu0CopyVector(Vec4 *, Pop *);
char *strcpy(char *, char *);
s32 strlen(char *);
extern Ent D_004518D0[5];
extern char D_004615E8[];
extern char D_004615F0[];
extern char D_00461600[];
void DamagePopupDraw_2d3240(Pop *p, s32 pk, s32 tex, u8 flags, f32 dist);
}

#define INVIEW(X, Y, X2, Y2, FAIL)     {         s32 t_ = (Y) / 16;         s32 r_ = (X2) / 16;         s32 b_ = (Y2) / 16;         s32 l_ = (X) / 16;         if (!(l_ < x0 + w)) FAIL;         if (!(t_ < y0 + h)) FAIL;         if (!(x0 < r_)) FAIL;         if (!(y0 < b_)) FAIL;     }

#pragma push
#pragma optimization_level 3
extern "C" void DamagePopupDraw_2d3240(Pop *p, s32 pk, s32 tex, u8 flags, f32 dist)
{
    char str[16] __attribute__((aligned(16)));
    Vec4 v __attribute__((aligned(16)));
    s32 pos[4] __attribute__((aligned(16)));
    char name[0x18] __attribute__((aligned(16)));
    Vec4 cam __attribute__((aligned(16)));
    Tbl tbl __attribute__((aligned(16)));
    char *sp;
    s32 len;
    Sys *sys;
    s32 ctx;
    s32 x0;
    s32 y0;
    s32 w;
    s32 h;
    s32 t;
    u8 i;
    Ent *e;
    s32 u0;
    s32 v0;
    s32 w0;
    s32 h0;
    s32 k;
    s32 big;
    s32 small;
    s32 cw;
    s32 ch;
    s32 dx;
    s32 dy;
    s32 total;
    s32 d;
    s32 col;
    s32 uu;
    s32 vv;
    s32 rg_ax; /* rg-override: projected X (12.4) = the number's anchor */

    if (!(p->x3C & 1)) {
        return;
    }
    if (p->x2E > p->x2C) {
        return;
    }
    if (p->x1C <= 0.0f) {
        return;
    }
    sys = GetCurrentScene_1f5be0();
    Sprintf_1343b8(str, D_004615E8, p->x30);
    len = strlen(str);
    sceVu0CopyVector(&v, p);
    ctx = GetDrawCtxNameTable_15de40();
    if (tex == 0) {
        memset(name, 0, 0x18);
        if (flags & 2) {
            strcpy(name, D_004615F0);
        } else {
            strcpy(name, D_00461600);
        }
        tex = NameTableFindByName_159fb0(ctx, name, 0x32B);
    }
    ObjRecGetLiveObject_1c3bc0(sys, sys->x4344)->GetPos(&cam);
    if (!(dist <= 0.0f)) {
        if (!(VecDistSq_13d360(&cam, p) <= dist)) {
            return;
        }
    }
    ctx = GetDrawCtx_15de80();
    x0 = DrawEnvGetLeft_1450f0(ctx);
    y0 = DrawEnvGetTop_1450c0(ctx);
    w = DrawEnvGetWidth_1451e0(ctx);
    h = DrawEnvGetHeight_1451d0(ctx);
    t = p->x38;
    if (t == 3) {
        goto tbl;
    }
    if (t == 4) {
        goto tbl;
    }
    if (t == 5) {
        goto tbl;
    }
    if (t == 6) {
    tbl:
        tbl = *(Tbl *)&D_004518D0;
        if (ProjectToScreen_15d340(pos, p) == 0) {
            return;
        }
        for (i = 0; tbl.e[i].key > 0; i++) {
            if (p->x38 != tbl.e[i].key) {
                continue;
            }
            dx = 0;
            dy = 0;
            INVIEW(pos[0], pos[1], pos[0] + dx, pos[1] + dy, return);
            rg_layout_about_begin((float)pos[0], 0);
            GsPktOpenPrim_13f730(pk, 6);
            GsPktSetTexture_13ec00(pk, tex);
            GsPktSetRGBAQVec_13edd0(pk, p->col);
            GsPktSetUV_13ed60(pk, tbl.e[i].u, tbl.e[i].v);
            GsPktSetXYZ_13ef10(pk, pos[0], pos[1], 0);
            GsPktSetUV_13ed60(pk, tbl.e[i].u + tbl.e[i].w, tbl.e[i].v + tbl.e[i].h);
            GsPktSetXYZ_13ef10(pk, pos[0] + (tbl.e[i].w << 4), pos[1] + (tbl.e[i].h << 4), 0);
            GsPktClose_13f5b0(pk);
            rg_layout_about_end();
            return;
        }
        return;
    }
    if (p->x30 < 0) {
        return;
    }
    sp = str;
    cw = (s32)(12.0f * p->x28);
    ch = (s32)(17.0f * p->x28);
    big = flags & 1;
    small = flags & 2;
    for (k = 0; k < len; k++, sp++) {
        if (ProjectToScreen_15d340(pos, p) == 0) {
            continue;
        }
        rg_ax = pos[0];
        d = *sp - 0x20;
        col = d % 16;
        vv = 0x5A;
        uu = col * 12;
        if (big) {
            uu++;
            vv = 0x5B;
        }
        if (small) {
            vv = 0;
            uu = col * 20;
            if (big) {
                uu++;
            }
        }
        pos[0] -= len * cw << 3;
        pos[0] += k * cw << 4;
        INVIEW(pos[0], pos[1], pos[0] + (cw << 4), pos[1] + (ch << 4), continue);
        rg_layout_about_begin((float)rg_ax, 0);
        GsPktOpenPrim_13f730(pk, 6);
        GsPktSetTexture_13ec00(pk, tex);
        GsPktSetRGBAQVec_13edd0(pk, p->col);
        GsPktSetUV_13ed60(pk, uu, vv);
        GsPktSetXYZ_13ef10(pk, pos[0], pos[1], 0);
        if (small) {
            if (big) {
                GsPktSetUV_13ed60(pk, uu + 0x13, vv + 0x19);
            } else {
                GsPktSetUV_13ed60(pk, uu + 0x14, vv + 0x1A);
            }
        } else {
            if (big) {
                GsPktSetUV_13ed60(pk, uu + 0xB, vv + 0x10);
            } else {
                GsPktSetUV_13ed60(pk, uu + 0xC, vv + 0x11);
            }
        }
        GsPktSetXYZ_13ef10(pk, pos[0] + (cw << 4), pos[1] + (ch << 4), 0);
        GsPktClose_13f5b0(pk);
        rg_layout_about_end();
    }
}
#pragma pop
