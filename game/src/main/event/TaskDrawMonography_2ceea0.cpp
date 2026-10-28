/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    f32 m[16];
} M2CEEA0;

typedef struct {
    f32 a[4];
    f32 b[4];
    f32 c[4];
    f32 d;
    f32 pad[3];
} E1_2CEEA0;

typedef struct {
    f32 p[4];
    f32 d;
    f32 pad[3];
} E2_2CEEA0;

class Cam2CEEA0 {
    u8 pad[0xC0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f39(void * a0) { VCM(void, (void *, void *), 0xA4, a0); }
};

class Pl2CEEA0 {
    u8 pad[0x1B0];
public:
    VC_VPTR_MEMBER;
    
    
    
    void f4(f32 a0) { VCM(void, (void *, f32), 0x18, a0); }
    
    
    void f7() { VCM0(void, 0x24); }
};

extern "C" {
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetUseUV_13e3e0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetFrameMask_13e420(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetSTVec_13ecc0(s32, void *);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZVecI_13eeb0(s32, void *);
extern void GsPktSetXYZf_13f060(s32, f32, f32, f32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern void ModelSetScale_150ff0(Pl2CEEA0 *, void *);
extern void ModelSetRot_151080(Pl2CEEA0 *, void *);
extern void ModelSetPos_151110(Pl2CEEA0 *, void *);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern Cam2CEEA0 *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
extern s32 CameraProjectToScreenStq_1c8f10(void *, void *, void *, f32, f32);
extern f32 VecDistSq_1cb3c0(void *, void *);
extern void MatMul_1cb700(void *, void *, void *);
extern void MatMulPointXyz_1cb780(void *, void *, f32, f32, f32);
extern void VecCopy_1cbe30(void *, void *);
extern void MatIdentity_1cbe40(void *);
extern u8 *GetCurrentScene_1f5be0(void);
extern Pl2CEEA0 *GetMonographyObj_1fdae0(void);
extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjGetPos_2e7640(s32, void *);
extern void EventObjGetRot_2e7670(s32, void *);
extern void EventObjGetScale_2e7690(s32, void *);
extern s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
extern s32 EvObjGetXform_2f9c90(u8 *);
extern s32 EvObjFlagBit30Clear_2f9cc0(u8 *);
extern f32 ObjTypeMonographGetTouchTimer_372a80(u8 *);
extern u8 *DListGetHead_42ea60(s32);
extern u8 *DListGetNext_42eb30(u8 *);
extern f32 D_00451890[];
extern u8 D_00461550[];
extern s32 D_00482634;
}

extern "C" void TaskDrawMonography_2ceea0(void) {
    E1_2CEEA0 a1[64] __attribute__((aligned(16)));
    f32 cv[4] __attribute__((aligned(16)));
    E2_2CEEA0 a2[64] __attribute__((aligned(16)));
    M2CEEA0 mtx __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(f32[12])) + (0x30 + sizeof(f32[4])) + (0x40)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(f32[12]) <= (0x30) && (0x0) >= 0 ? 1 : -1];
    
    f32 uv[4][4] __attribute__((aligned(16)));
    f32 pos[4][4] __attribute__((aligned(16)));
    f32 out[4][4] __attribute__((aligned(16)));
    s32 sc;
    s32 n;
    u8 *g;
    u8 *it;
    u8 *it2;
    u8 *e;
    s32 m;
    E1_2CEEA0 *p1;
    Pl2CEEA0 *pl;
    s32 i;
    s32 k;
    u8 *e2;
    E2_2CEEA0 *p2;
    f32 f;
    f32 *pd;
    s32 mgr;
    s32 tl;
    s32 tex;
    s32 c;
    s32 i3;
    s32 j;
    f32 d;
    f32 t;
    f32 q;
    f32 one;
    f32 r;
    f32 nr;
    s32 al;

    if (D_00482634 > 0) {
        D_00482634--;
        return;
    }
    sc = GetEventObjMgr_2d1960();
    n = 0;
    g = GetCurrentScene_1f5be0();
    ObjRecGetLiveObject_1c3bc0(g, *(s32 *)(g + 0x4344))->f39(cv);
    it = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(sc, 5));
    while (it != 0) {
        e = it + 0x10;
        it = DListGetNext_42eb30(it);
        if (EvObjFlagBit30Clear_2f9cc0(e) == 0) {
            continue;
        }
        if (*(u32 *)(e + 0xD0) & 0x200000) {
            continue;
        }
        m = EvObjGetXform_2f9c90(e);
        p1 = &a1[n];
        EventObjGetPos_2e7640(m, p1->a);
        EventObjGetRot_2e7670(m, p1->b);
        EventObjGetScale_2e7690(m, p1->c);
        p1->d = VecDistSq_1cb3c0(p1, cv);
        n++;
    }
    pl = GetMonographyObj_1fdae0();
    if (n > 0 && pl != 0) {
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), *(s32 *)((u8 *)pl + 0x4DC), 1.0f);
        for (i = 0; i < n; i++) {
            p1 = &a1[i];
            ModelSetPos_151110(pl, p1->a);
            ModelSetRot_151080(pl, p1->b);
            ModelSetScale_150ff0(pl, p1->c);
            pl->f4(1.0f);
            pl->f7();
        }
    }
    k = 0;
    it2 = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(sc, 5));
    while (it2 != 0) {
        e2 = it2 + 0x10;
        it2 = DListGetNext_42eb30(it2);
        if (EvObjFlagBit30Clear_2f9cc0(e2) == 0) {
            continue;
        }
        p2 = &a2[k];
        pd = &p2->d;
        *pd = ObjTypeMonographGetTouchTimer_372a80(e2);
        if (*pd < 0.0f) {
            continue;
        }
        EventObjGetPos_2e7640(EvObjGetXform_2f9c90(e2), p2->p);
        k++;
    }
    if (k <= 0) {
        return;
    }
    mtx = *(M2CEEA0 *)D_00451890;
    MatIdentity_1cbe40((*(f32 (*)[12])(rgp_blk1 + 0x0)));
    mgr = GetDrawCtx_15de80();
    tl = GetDrawCtxNameTable_15de40();
    DrawListBeginPrim_141b00(mgr);
    tex = NameTableFindByName_159fb0(tl, D_00461550, 0x334);
    DrawListAddTexLoad_1418c0(mgr, 0x334, 1.0f);
    c = DrawListBeginPrim_141b00(mgr);
    GsPktSetAlphaBlend_13e500(c, 1);
    GsPktSetBlendMode_13e4f0(c, 2);
    GsPktEnableAlphaTest_13e4d0(c, 1);
    GsPktEnableZTest_13e460(c, 1);
    GsPktSetTextured_13e400(c, 1);
    GsPktSetOriginMode_13e2f0(c, 1);
    GsPktSetGouraud_13e3b0(c, 1);
    GsPktSetZWriteMask_13e430(c, 1);
    GsPktSetFrameMask_13e420(c, 1);
    GsPktSetUseUV_13e3e0(c, 0);
    GsPktOpenPrim_13f730(c, 0);
    GsPktSetRGBAQ_13ee40(c, 0, 0, 0, 0x80);
    GsPktSetXYZf_13f060(c, 0.0f, 0.0f, -1.0f);
    GsPktClose_13f5b0(c);
    for (i3 = 0; i3 < k; i3++) {
        p2 = &a2[i3];
        VecCopy_1cbe30((*(f32 (*)[4])(rgp_blk1 + 0x30)), p2);
        MatMul_1cb700(&mtx, (*(f32 (*)[12])(rgp_blk1 + 0x0)), &mtx);
        for (j = 0; j < 2; j++) {
            d = p2->d - (f32)(j * 5);
            if (d < 0.0f) {
                continue;
            }
            if (20.0f <= d) {
                continue;
            }
            t = 1.0f - d / 20.0f;
            one = 1.0f;
            q = 0.0f + one - t * t;
            r = 0.0f + one + one * q;
            nr = -r;
            MatMulPointXyz_1cb780(pos[0], &mtx, nr, 0.0f, nr);
            MatMulPointXyz_1cb780(pos[1], &mtx, nr, 0.0f, r);
            MatMulPointXyz_1cb780(pos[2], &mtx, r, 0.0f, nr);
            MatMulPointXyz_1cb780(pos[3], &mtx, r, 0.0f, r);
            if (CameraProjectToScreenStq_1c8f10(out[0], uv[0], pos[0], 0.0f, 0.0f) == 0) {
                continue;
            }
            if (CameraProjectToScreenStq_1c8f10(out[1], uv[1], pos[1], 0.0f, 1.0f) == 0) {
                continue;
            }
            if (CameraProjectToScreenStq_1c8f10(out[2], uv[2], pos[2], 1.0f, 0.0f) == 0) {
                continue;
            }
            if (CameraProjectToScreenStq_1c8f10(out[3], uv[3], pos[3], 1.0f, 1.0f) == 0) {
                continue;
            }
            GsPktOpenPrim_13f730(c, 4);
            GsPktSetTexture_13ec00(c, tex);
            GsPktSetSTVec_13ecc0(c, uv[0]);
            al = (s32)(128.0f * t);
            GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, al);
            GsPktSetXYZVecI_13eeb0(c, out[0]);
            GsPktSetSTVec_13ecc0(c, uv[1]);
            GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, al);
            GsPktSetXYZVecI_13eeb0(c, out[1]);
            GsPktSetSTVec_13ecc0(c, uv[2]);
            GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, al);
            GsPktSetXYZVecI_13eeb0(c, out[2]);
            GsPktSetSTVec_13ecc0(c, uv[3]);
            GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, al);
            GsPktSetXYZVecI_13eeb0(c, out[3]);
            GsPktClose_13f5b0(c);
        }
    }
    DrawListEndPrim_141a20(mgr);
}
