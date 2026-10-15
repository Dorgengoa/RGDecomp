#include "types.h"

typedef unsigned int u128 __attribute__((mode(TI)));

union Vec4 {
    u128 q;
    struct { f32 x, y, z, w; } f;
};

struct Unit {
    u8 pad0[0x180];
    Vec4 pos;           /* +0x180 */
    u8 pad190[0x7F4];
    s8 flag984;         /* +0x984 */
    s8 active;          /* +0x985 */
    u8 name[1];         /* +0x986 */
};

struct Slot {
    Unit *unit;
    f32 dist;
};

struct CamBase { u8 pad0[0xC0]; };
class Cam : public CamBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void GetPos(Vec4 *);
};

extern "C" {
s32 BitArrayTest_384320(void *, s32);
s32 GetDrawCtxNameTable_15de40(void);
s16 *NameTableFindByName_159fb0(s32, void *, s32);
s32 GetDrawCtx_15de80(void);
Cam *GetCurrentSceneCamera_389d40(void);
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
void Qsort_132d08(void *, s32, s32, void *);
f32 Sinf_128fd0(f32);
void DrawListAddTexLoad_1418c0(s32, s16, f32);
s32 DrawListBeginPrim_141b00(s32);
void GsPktSetup2DState_3892a0(s32);
f32 MenuObjGetMarkerHeight_387170(Unit *);
s32 ProjectToScreen_15d340(s32 *, Vec4 *);
s32 MenuObjInsectIsAdult_386c90(Unit *);
s32 MenuObjInsectGetSex_386cf0(Unit *);
s32 MenuObjInsectGetSatiety_386c00(Unit *);
s32 MenuObjInsectSatietyUnderCap_386bd0(Unit *);
void GsPktSetTexFilter_13e3d0(s32, s32);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktSetTexture_13ec00(s32, s16 *);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
void GsPktClose_13f5b0(s32);
void DrawListEndPrim_141a20(s32);
s32 InsectCageMarkerCompareByDist_388ea0(const void *, const void *);
}
extern s32 D_0048335C;
extern s8 D_004833F8;
extern u8 D_00463F40[];
extern u8 *D_004832AC;
extern f32 D_004832E0;
extern s16 D_0047FCA0[2][2];
extern s16 D_0047FCA8[2][2];

extern "C" void InsectCageUnitMarkersDraw_3888e0(void)
{
    Vec4 cam;
    Slot tbl[5];
    Vec4 v;
    Vec4 pos;
    s32 scr[4];
    s32 alpha;
    s32 c;
    s16 *res;
    s32 g;
    s32 count;
    s32 i;
    Unit *p;
    s32 w;
    s32 k;
    Unit *e;
    s32 a;
    s32 b;
    s32 x;
    s32 y;
    s32 u0;
    s32 u1;
    s32 y2;
    f32 r;

    if (BitArrayTest_384320(&D_0048335C, 1) == 0) {
        return;
    }
    if (D_004833F8 == 0) {
        return;
    }
    res = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00463F40, -1);
    if (res == 0) {
        return;
    }
    g = GetDrawCtx_15de80();
    GetCurrentSceneCamera_389d40()->GetPos(&cam);
    count = 0;
    for (i = 0; i < 5; i++) {
        tbl[i].unit = 0;
        tbl[i].dist = 0;
        p = (Unit *)D_004832AC;
        p = (Unit *)((u8 *)p + i * 0x9D0);
        if (p->active != 0) {
            tbl[i].unit = p;
            v.q = p->pos.q;
            tbl[i].dist = VecDistance_13d3d0(&v, &cam);
            count++;
        }
    }
    if (count <= 0) {
        return;
    }
    Qsort_132d08(tbl, count, 8, (void *)InsectCageMarkerCompareByDist_388ea0);
    alpha = (s32)(64.0f * Sinf_128fd0(D_004832E0)) + 0x80;
    DrawListAddTexLoad_1418c0(g, *res, 1.0f);
    w = DrawListBeginPrim_141b00(g);
    GsPktSetup2DState_3892a0(w);
    k = 4;
    do {
        e = tbl[k].unit;
        if (e == 0 || e->active == 0 || BitArrayTest_384320(e->name, 7) != 0) {
            continue;
        }
        pos.q = e->pos.q;
        pos.f.y = pos.f.y + MenuObjGetMarkerHeight_387170(e);
        if (e->flag984 != 0) {
            pos.f.y = pos.f.y + 1.0f;
        }
        if (ProjectToScreen_15d340(scr, &pos) == 0) {
            continue;
        }
        a = MenuObjInsectIsAdult_386c90(e);
        b = MenuObjInsectGetSex_386cf0(e);
        c = MenuObjInsectGetSatiety_386c00(e);
        x = scr[0] - 0x150;
        y = scr[1] - 0xB0;
        if (D_004833F8 == 1) {
            GsPktSetTexFilter_13e3d0(w, 1);
            GsPktOpenPrim_13f730(w, 6);
            GsPktSetTexture_13ec00(w, res);
            u0 = D_0047FCA8[b][0];
            u1 = D_0047FCA8[b][1];
            GsPktSetRGBAQ_13ee40(w, 0x80, 0x80, 0x80, 0x80);
            GsPktSetUV_13ed60(w, u0, u1);
            GsPktSetXYZ_13ef10(w, x, y, 0);
            GsPktSetUV_13ed60(w, u0 + 0x2A, u1 + 0x16);
            GsPktSetXYZ_13ef10(w, x + 0x2A0, y + 0x160, 0);
            u0 = D_0047FCA0[a][0];
            u1 = D_0047FCA0[a][1];
            GsPktSetUV_13ed60(w, u0, u1);
            GsPktSetXYZ_13ef10(w, x, y + 0x140, 0);
            GsPktSetUV_13ed60(w, u0 + 0x2A, u1 + 0x16);
            GsPktSetXYZ_13ef10(w, x + 0x2A0, y + 0x2A0, 0);
            GsPktClose_13f5b0(w);
        } else if (D_004833F8 == 2) {
            x = (u32)x - 0x40;
            GsPktSetTexFilter_13e3d0(w, 1);
            GsPktOpenPrim_13f730(w, 6);
            GsPktSetTexture_13ec00(w, res);
            if (MenuObjInsectSatietyUnderCap_386bd0(e) != 0) {
                GsPktSetRGBAQ_13ee40(w, (s32)(100.0f * Sinf_128fd0(D_004832E0)) + 0x80, 0x80, 0x80, 0x80);
            } else {
                GsPktSetRGBAQ_13ee40(w, 0x80, 0x80, 0x80, 0x80);
            }
            GsPktSetUV_13ed60(w, 0x54, 0x22);
            GsPktSetXYZ_13ef10(w, x, y, 0);
            GsPktSetUV_13ed60(w, 0x86, 0x34);
            GsPktSetXYZ_13ef10(w, x + 0x320, y + 0x120, 0);
            GsPktSetUV_13ed60(w, 0xA8, 0xAE);
            GsPktSetXYZ_13ef10(w, x, y + 0x120, 0);
            GsPktSetUV_13ed60(w, 0xDA, 0xB8);
            GsPktSetXYZ_13ef10(w, x + 0x320, y + 0x1C0, 0);
            if (MenuObjInsectSatietyUnderCap_386bd0(e) != 0) {
                GsPktSetRGBAQ_13ee40(w, 0x80, 0x80, 0x80, alpha);
            }
            x = (u32)x + 0x20;
            y2 = y + 0x140;
            r = (f32)c / 100.0f;
            if (1.0f <= r) {
                r = 1.0f;
            }
            GsPktSetUV_13ed60(w, 0xAA, 0xBC);
            GsPktSetXYZ_13ef10(w, x, y2, 0);
            GsPktSetUV_13ed60(w, 0xD8, 0xC2);
            GsPktSetXYZ_13ef10(w, x + ((s32)(47.0f * r) << 4), y2 + 0x60, 0);
            GsPktClose_13f5b0(w);
        }
    } while (--k >= 0);
    DrawListEndPrim_141a20(g);
}
