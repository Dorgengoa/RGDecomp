/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3

typedef rg_u128 u128;

struct Vec4 {
    f32 x, y, z, w;
};

struct IVec4 {
    s32 x, y, z, w;
};

class Chk {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v150() { VCM0(void, 0x150); }
    
    
    
    
    
    
    
    void v170() { VCM0(void, 0x170); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Ok() { return VCM0(s32, 0x410); }
};

class Stat {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Hp() { return VCM0(s32, 0xF0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 MaxHp(s32 a0) { return VCM(s32, (void *, s32), 0x128, a0); }
};

class Pc {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    char * Name() { return VCM0(char *, 0x60); }
};

struct Hit {
    u8 pad[0x10];
    f32 x10;
};

struct Ent {
    u8 pad0[4];
    char *name;          /* 0x04 */
    s16 kind;            /* 0x08 */
    u8 padA[0x3E];
    u32 flags;           /* 0x48 */
};

struct Self {
    u8 pad0[0x80];
    u8 st[0x20];         /* 0x80 */
    u8 padA0[0xA0];
    s32 f140;            /* 0x140 */
    u8 pad144[0x14];
    s32 tex;             /* 0x158 */
};

struct C8 {
    u64 v;
};

extern "C" {
s32 GetSysTextStyle_313570(void);
s32 GetDrawCtx_15de80(void);
void TextStyleGetRgba_26f2a0(C8 *, s32);
void TextStyleGetGradRgba_26f200(C8 *, s32);
s32 TextStyleGetFontType_26ede0(s32);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void TextStyleInitPreset_26c540(s32, s32);
void TextStyleSetZEnable_26e420(s32, s32);
void TextStyleSetFontType_26edf0(s32, s32);
s32 ScreenMarkerGetId_31c030(Self *, s32);
s32 GetCurrentScene_1f5be0(void);
u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
u8 *ModelGetRootFrame_1511a0(u8 *);
void FrameGetWorldPos_148f30(u8 *, Vec4 *);
f32 ModelObjGetScaledHeight_23b110(u8 *);
f32 ScreenMarkerGetHeightOffset_31a8e0(Self *);
s32 ProjectToScreenOffset_15d160(IVec4 *, Vec4 *);
s32 ScreenMarkerProjectObj_31aad0(Self *, s32);
void ScreenMarkerSetTimer_31bf90(Self *, s32, s32);
u8 ScreenMarkerGetFlag_31c010(Self *, s32);
void ScreenMarkerSetFlag_31bf70(Self *, s32, s32);
void ScreenMarkerSetId_31bfb0(Self *, s32, s32);
void ScreenMarkerRestartById_31a9b0(Self *, s32);
void ScreenMarkerAdd_31ae50(Self *, s32, s32);
Hit *ObjGetNthAttachPointPos_1ade20(u8 *, s32, s32, Vec4 *);
s32 GetGameData_1fede0(void);
Pc *ActorFindById_3eb8d0(s32, s32);
Stat * ActorCastToUnitBase_3b87f0(Pc *, int, int, int);
Chk * ActorCastToUnit_3b8770(Stat *, int, int, int);
s32 GetNpcObjTable_312860(void);
Ent *NpcObjFindDefById_2fb490(s32, s32);
void TextStyleSetRgba_26f280(s32, s32, s32, s32, s32);
void TextStyleSetGradRgba_26f1e0(s32, s32, s32, s32, s32);
s32 ScreenMarkerGetFadeOut_31bff0(Self *, s32);
s32 ScreenMarkerGetFadeIn_31bfd0(Self *, s32);
f32 ScreenMarkerGetMasterAlpha_31aeb0(Self *);
void TextStyleSetAlpha_26dd40(s32, s32);
void ScreenMarkerSetFadeIn_31bf30(Self *, s32, s32);
s32 strlen(const char *);
void FontMeasureString_26daf0(s32, char *, s32 *, s32 *);
s32 TextStyleGetZ_26e430(s32);
void TextStyleSetZ_26e440(s32, s32);
void FontDrawText_26cdc0(s32, char *, s32, s32);
void TextStyleSetRgbaQuad_26f250(s32, C8);
void TextStyleSetGradRgbaQuad_26f1b0(s32, C8);
s32 GetDrawCtxNameTable_15de40(void);
s32 NameTableFindByName_159fb0(s32, void *, s32);
s32 DrawEnvGetWidth_1451e0(s32);
s32 DrawEnvGetHeight_1451d0(s32);
s32 DrawListBeginPrim_141b00(s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetAlphaTestFunc_13e4c0(s32, s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktSetZTest_13e450(s32, s32);
void GsPktSetGouraud_13e3b0(s32, s32);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetTexFilter_13e3d0(s32, s32);
void GsPktSetAntialias_13e390(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetUseUV_13e3e0(s32, s32);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktSetTexture_13ec00(s32, s32);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetXYZPixelVec_13ef70(s32, IVec4 *);
void GsPktClose_13f5b0(s32);
void DrawListEndPrim_141a20(s32);
extern f32 D_0045B080[];
extern f32 D_0047D82C;
extern u8 D_004623D8[];
extern f32 D_0047F2B0[4];
}

#define ZERO16(v) { u8 *p_ = (u8 *)&(v); u32 n_ = 0x10; if (p_) { while (n_) { *p_ = 0; n_--; p_++; } } }

static inline void Red(s32 font) {
    TextStyleSetRgba_26f280(font, 0xF0, 0x5A, 0x18, 0x80);
    TextStyleSetGradRgba_26f1e0(font, 0x80, 0x40, 0x40, 0x80);
}

static inline void Box(IVec4 *hi, IVec4 *lo, s16 *po, s16 *ph, s32 *pk) {
    s32 x = *po;
    s32 y = *ph;
    s32 z = *pk;
    hi->x = x - 2;
    hi->y = y - 3;
    hi->z = z;
    ZERO16(*lo);
    lo->z = z;
    lo->x = x + 16;
    lo->y = y + 15;
}
static inline void Box2(IVec4 *hi, IVec4 *lo, s32 x, s32 y, s32 z) {
    hi->x = x - 2;
    hi->y = y - 3;
    hi->z = z;
    ZERO16(*lo);
    lo->z = z;
    lo->x = x + 16;
    lo->y = y + 15;
}
extern "C" void ScreenMarkerDrawAll_31af50(Self *self) {
    s32 w3CC;
    s32 w3C8;
    C8 sv1 __attribute__((aligned(16)));
    C8 sv2 __attribute__((aligned(16)));
    C8 c1 __attribute__((aligned(16)));
    C8 c2 __attribute__((aligned(16)));
    s32 ord[32] __attribute__((aligned(16)));
    s32 key[32] __attribute__((aligned(16)));
    s16 ofs[32] __attribute__((aligned(16)));
    s16 hgt[32] __attribute__((aligned(16)));
    u8 flg[32] __attribute__((aligned(16)));
    f32 scl[32] __attribute__((aligned(16)));
    Vec4 v170 __attribute__((aligned(16)));
    IVec4 s160 __attribute__((aligned(16)));
    Vec4 v150 __attribute__((aligned(16)));
    IVec4 s140 __attribute__((aligned(16)));
    s32 sv10C;
    s32 q;
    s32 v;
    s32 sx;
    u32 slot;
    s32 font;
    s32 fnt;
    s32 mgr;
    s32 i;
    s32 j;
    s32 k;
    s32 id;
    s32 sw;
    s32 t;
    s32 a;
    s32 b;
    char *str;
    s32 y;
    s32 half;
    s32 old;
    s32 W;
    s32 H;
    s32 c;
    s32 u;
    s32 sz;
    u8 f;
    u32 fl;
    s16 *ph;
    s16 *po;
    s32 *pk;
    s32 vx;
    s32 vy;
    s32 vz;
    s32 *pa;
    s32 *pb;
    Vec4 *pc2;
    u8 *o;
    s32 m;
    u8 *pf;
    Hit *hit;
    Pc *pc;
    Stat *st;
    Chk *ck;
    Ent *e;
    s32 hp;
    f32 f20;
    f32 sc;
    f32 f21;
    f32 g;

    if (self->f140 == 0) return;
    font = GetSysTextStyle_313570();
    fnt = font;
    mgr = GetDrawCtx_15de80();
    if (font == 0) return;
    if (mgr == 0) return;
    TextStyleGetRgba_26f2a0(&c1, font);
    sv1 = c1;
    TextStyleGetGradRgba_26f200(&c2, font);
    sv2 = c2;
    sv10C = ((signed char)TextStyleGetFontType_26ede0(font));
    DrawListAddTexLoad_1418c0(mgr, 0x338, 1.0f);
    TextStyleInitPreset_26c540(font, 1);
    TextStyleSetZEnable_26e420(font, 1);
    TextStyleSetFontType_26edf0(font, 0);
    for (i = 0; i < 32; i++) {
        ord[i] = i;
        key[i] = -1;
        ofs[i] = 0;
        flg[i] = 0;
        scl[i] = 1.0f;
        hgt[i] = 0;
    }
    for (i = 0; i < 32; i++) {
        id = (s16)((short)ScreenMarkerGetId_31c030(self, i));
        if (id == -1) continue;
        o = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id);
        if (o != 0) {
            FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(o), &v170);
            f20 = ModelObjGetScaledHeight_23b110(o);
            v170.y = v170.y + (f20 + ScreenMarkerGetHeightOffset_31a8e0(self));
        }
        ProjectToScreenOffset_15d160(&s160, &v170);
        s160.x /= 16;
        s160.y /= 16;
        s160.z /= 16;
        if (ScreenMarkerProjectObj_31aad0(self, id) == 0) {
            ScreenMarkerSetTimer_31bf90(self, i, 0);
            self->st[i] |= 0x80;
            if (ScreenMarkerGetFlag_31c010(self, i) == 2) {
                ScreenMarkerSetFlag_31bf70(self, i, 0);
                ScreenMarkerSetId_31bfb0(self, i, -1);
            }
        } else {
            pf = &self->st[i];
            if (*pf & 0x80) {
                ScreenMarkerRestartById_31a9b0(self, id);
                *pf &= 0x7F;
            } else if (ScreenMarkerGetFlag_31c010(self, i) == 2) {
                ScreenMarkerSetFlag_31bf70(self, i, 0);
                ScreenMarkerAdd_31ae50(self, id, 0);
            }
        }
        ord[i] = i;
        key[i] = s160.z;
    }
    do {
        sw = 0;
        for (m = 0; m < 31; m++) {
            pa = &key[m];
            pb = pa + 1;
            if (*pa > *pb) {
                t = *pa;
                *pa = *pb;
                sw = 1;
                *pb = t;
                t = ord[m];
                ord[m] = ord[m + 1];
                ord[m + 1] = t;
            }
        }
    } while (sw);
    f20 = D_0047D82C * (f32)D_0045B080[0];
    for (m = 0; m < 32; m++) {
        pf = &flg[m];
        *pf = 0;
        slot = ord[m];
        id = (s16)((short)ScreenMarkerGetId_31c030(self, slot));
        if (id == -1) continue;
        w3CC = 0;
        str = 0;
        w3C8 = 0;
        o = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id);
        if (o == 0) continue;
        hit = ObjGetNthAttachPointPos_1ade20(o, 0x96, 0, &v150);
        if (hit != 0) {
            v150.y = v150.y + hit->x10 * f20;
            if (ProjectToScreenOffset_15d160(&s140, &v150) == 0) continue;
            s140.x /= 16;
            y = s140.y / 16;
            s140.y = y;
            sx = s140.x;
            sz = s140.z;
        } else {
            FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(o), &v150);
            v150.y = v150.y + ModelObjGetScaledHeight_23b110(o);
            if (ProjectToScreenOffset_15d160(&s140, &v150) == 0) continue;
            s140.x /= 16;
            s140.y /= 16;
            y = s140.y - 24;
            sx = s140.x;
            sz = s140.z;
        }
        if ((id >= 0 && id < 12) || (id >= 0x80 && id < 0x9C)) {
            t = GetGameData_1fede0();
            if (t == 0) continue;
            pc = ActorFindById_3eb8d0(t, id);
            if (pc == 0) continue;
            st = ActorCastToUnitBase_3b87f0(pc, 0, 0, 0);
            if (st == 0) continue;
            hp = st->Hp();
            t = st->MaxHp(1);
            if (!((f32)hp / (f32)t <= 0.0f)) str = pc->Name();
            if (!(id < 0x80) && id < 0x9C) {
                ck = ActorCastToUnit_3b8770(st, 0, 0, 0);
                if (ck != 0 && ck->Ok() == 0) str = 0;
            }
        } else if (id >= 0xC0 && id < 0xE0) {
            t = GetNpcObjTable_312860();
            if (t != 0) {
                e = NpcObjFindDefById_2fb490(t, id);
                if (e != 0) {
                    str = e->name;
                    if (e->kind & 6) y -= 40;
                    *pf |= 1;
                    fl = e->flags;
                    if (fl & 2) *pf |= 2;
                    if (fl & 4) *pf |= 4;
                    if (fl & 8) *pf |= 8;
                    if (fl & 0x10) *pf |= 0x10;
                    if (fl & 0x20) *pf |= 0x20;
                }
            }
        }
        if (id >= 0 && id < 12) {
            TextStyleSetRgba_26f280(font, 0x20, 0x20, 0x80, 0x80);
            TextStyleSetGradRgba_26f1e0(font, 0x60, 0x80, 0x80, 0x80);
        } else if (!(id < 0x80)) {
            TextStyleSetRgba_26f280(font, 0xF0, 0x5A, 0x18, 0x80);
            TextStyleSetGradRgba_26f1e0(font, 0x80, 0x40, 0x40, 0x80);
        } else {
            TextStyleSetRgba_26f280(fnt, 0xF0, 0x5A, 0x18, 0x80);
            TextStyleSetGradRgba_26f1e0(fnt, 0x80, 0x40, 0x40, 0x80);
        }
        a = (s16)((short)ScreenMarkerGetFadeOut_31bff0(self, ord[m]));
        b = (s16)((short)ScreenMarkerGetFadeIn_31bfd0(self, ord[m]));
        if (b != -1) {
            g = ScreenMarkerGetMasterAlpha_31aeb0(self);
            sc = 128.0f * ((15.0f - (f32)b) / 15.0f) * g;
            TextStyleSetAlpha_26dd40(font, (s32)sc);
            if (b <= 0) {
                ScreenMarkerSetFadeIn_31bf30(self, ord[(u32)m], -1);
                ScreenMarkerSetTimer_31bf90(self, ord[(u32)m], 0x5A);
            }
        } else if (a != -1) {
            f21 = (f32)a / 15.0f;
            sc = 128.0f * f21 * ScreenMarkerGetMasterAlpha_31aeb0(self);
            TextStyleSetAlpha_26dd40(font, (s32)sc);
            if (!f21) ScreenMarkerSetFlag_31bf70(self, slot, 0);
        } else {
            sc = 128.0f * ScreenMarkerGetMasterAlpha_31aeb0(self);
            TextStyleSetAlpha_26dd40(font, (s32)sc);
        }
        scl[m] = sc;
        if (str == 0) continue;
        strlen(str);
        FontMeasureString_26daf0(font, str, &w3CC, &w3C8);
        half = w3CC / 2;
        if (ScreenMarkerGetFlag_31c010(self, slot) != 1) continue;
        old = TextStyleGetZ_26e430(font);
        TextStyleSetZ_26e440(font, sz);
        half = sx - half;
        FontDrawText_26cdc0(font, str, half, y);
        TextStyleSetZ_26e440(font, old);
        ofs[m] = half - 16;
        key[m] = sz;
        hgt[m] = y;
    }
    TextStyleSetRgbaQuad_26f250(font, sv1);
    TextStyleSetGradRgbaQuad_26f1b0(font, sv2);
    TextStyleSetFontType_26edf0(font, sv10C);
    self->tex = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_004623D8, 0x338);
    DrawListAddTexLoad_1418c0(mgr, 0x338, 1.0f);
    W = DrawEnvGetWidth_1451e0(mgr);
    H = DrawEnvGetHeight_1451d0(mgr);
    for (q = 0; q < 32; q++) {
        pf = &flg[q];
        fl = *pf;
        if (fl == 0) continue;
        f = fl;
        if (!(f & 1)) continue;
        c = DrawListBeginPrim_141b00(mgr);
        GsPktSetAlphaBlend_13e500(c, 1);
        GsPktSetBlendMode_13e4f0(c, 1);
        GsPktEnableAlphaTest_13e4d0(c, 1);
        GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
        GsPktEnableZTest_13e460(c, 1);
        GsPktSetZTest_13e450(c, 2);
        GsPktSetGouraud_13e3b0(c, 1);
        GsPktSetOriginMode_13e2f0(c, 0);
        GsPktSetTexFilter_13e3d0(c, 0);
        GsPktSetAntialias_13e390(c, 0);
        GsPktSetZWriteMask_13e430(c, 0);
        GsPktSetTextured_13e400(c, 1);
        GsPktSetUseUV_13e3e0(c, 1);
        if (f & 0x3E) {
            u = 0x4E;
            t = 0xE0;
            if (f & 2) {
                u = 0x86;
                t = 0x14;
            }
            if (f & 4) {
                u = 0x74;
                t = 0x14;
            }
            if (f & 8) {
                u = 0x98;
                t = 0x14;
            }
            if (f & 0x10) {
                u = 0xAA;
                t = 0x14;
            }
            if (f & 0x20) {
                u = 0x86;
                t = 0x14;
            }
            {
            IVec4 hi __attribute__((aligned(16))) = {0};
            po = (s16 *)(s32)&ofs[q];
            ph = (s16 *)(s32)&hgt[q];
            vx = *po;
            vy = *ph;
            hi.x = vx - 2;
            hi.y = vy - 3;
            pk = (s32 *)(s32)&key[q];
            vz = *pk;
            hi.z = vz;
            {
            IVec4 lo __attribute__((aligned(16))) = {0};
            lo.z = vz;
            lo.x = vx + 16;
            lo.y = vy + 15;
            {
            Vec4 col __attribute__((aligned(16))) = *(Vec4 *)D_0047F2B0;
            pc2 = &col;
            sc = scl[q];
            if (lo.x >= 0 && lo.y >= 0 && hi.x < W && hi.y < H) {
                GsPktOpenPrim_13f730(c, 6);
                GsPktSetTexture_13ec00(c, self->tex);
                GsPktSetRGBAQ_13ee40(c, (s32)col.x, (s32)col.y, (s32)col.z, (s32)sc);
                GsPktSetUV_13ed60(c, (s16)u, (s16)t);
                GsPktSetXYZPixelVec_13ef70(c, &hi);
                GsPktSetUV_13ed60(c, (s16)u + 0x12, (s16)t + 0x12);
                GsPktSetXYZPixelVec_13ef70(c, &lo);
                GsPktClose_13f5b0(c);
            }
            }
            }
            }
        }
        DrawListEndPrim_141a20(mgr);
    }
}
