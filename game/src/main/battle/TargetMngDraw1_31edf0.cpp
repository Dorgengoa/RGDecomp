/* rgp:protos */
#line 1
#include "types.h"


typedef rg_u128 u128;

struct V4 {
    f32 x, y, z, w;
};

struct ChrBase {
    u8 pad0[0x190];
    u128 q190;
    u8 pad1A0[0x10];
};

class Chr : public ChrBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    void v4(f32 a0) { VCM(void, (void *, f32), 0x18, a0); }
    
    
    void v7() { VCM0(void, 0x24); }
    u8 pad1B4[0x4DC - 0x1B4];
    s32 f4DC;
};

struct Tgt {
    u8 pad0[0x180];
    u128 pos;
    u8 pad190[0x4CC - 0x190];
    f32 f4CC;
};

struct Ent {
    u8 pad0[8];
    s16 flags;
};

struct Obj {
    s32 f0;
    f32 f4;
    s32 f8;
    u8 padC[0x10 - 0xC];
    u8 s10[0xC0 - 0x10];
    u8 sC0[0xF4 - 0xC0];
    f32 fF4;
    f32 fF8;
};

struct Pt {
    s32 x, y;
} __attribute__((aligned(16)));

extern "C" {
s32 GetDrawCtx_15de80(void);
void *GetStaticScene_1c6c70(void);
Chr *GetCursorObj_1fdb20(void);
s32 TargetRefResolve_2e5ed0(void *, s32);
void TargetMngClearAimMode_31ed40(Obj *);
s32 TargetSlotGetState_320a30(void *);
s32 TargetRefGetId_2e7120(void *);
s32 TargetRefGetKind_2e7130(void *);
void TargetRefCtor_2e71f0(void *);
void TargetRefSetAttachPoint_2e65f0(void *, s32, s32, s32);
s32 TargetRefGetPos_2e6a60(void *, V4 *);
f32 TargetRefGetRadius_2e7100(void *);
s32 TargetRefGetObj_2e7110(void *);
void *TargetRefGetTreasureBox_2e7010(void *);
void *TargetRefGetInsectCageSlot_2e6fd0(void *);
void TreasureBoxGetPos_33ae30(void *, V4 *);
void InsectCageSlotGetPos_39b340(void *, V4 *);
Tgt *ObjRecGetLiveObject_1c4a90(void *, s32);
void *GetNpcObjTable_312860();
Ent *NpcObjFindDefById_2fb490(void *, s32);
s32 ProjectToScreenOffset_15d160(Pt *, V4 *);
void TargetMngSetAimOffscreen_31ed50(Obj *);
void ModelSetPos_151110(Chr *, V4 *);
void ModelSetRot_151080(Chr *, V4 *);
f32 Sinf_128fd0(f32);
f64 dpmul(f64, f64);
void ModelSetScale_150ff0(Chr *, V4 *);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void TargetMngDrawAimArrow_31eae0(Obj *);
}
extern "C" f32 D_0047D5D0;
extern "C" f32 D_0045B080[];
extern "C" volatile f64 D_0047D198;
extern "C" volatile f64 D_0047D1A0;

extern "C" void TargetMngDraw1_31edf0(Obj *a) {
    s32 gfx;
    void *tbl;
    Chr *chr;
    bool flag;
    V4 pos __attribute__((aligned(16)));
    V4 rot __attribute__((aligned(16)));
    u8 obj[0x30] __attribute__((aligned(16)));
    Pt pt __attribute__((aligned(16)));
    V4 sc __attribute__((aligned(16)));
    f32 k;
    f64 inv;
    f64 one = 1.0;

    if (a->f8 == 0) {
        return;
    }
    gfx = GetDrawCtx_15de80();
    tbl = GetStaticScene_1c6c70();
    chr = GetCursorObj_1fdb20();
    TargetRefResolve_2e5ed0(a->sC0, 0);
    TargetMngClearAimMode_31ed40(a);
    if (chr != 0) {
        flag = 0;
        if (TargetSlotGetState_320a30(a->s10) == 0) {
            if (a->f0 == 1 && ((short)TargetRefGetId_2e7120(a->sC0)) >= 0) {
                switch (((short)TargetRefGetKind_2e7130(a->sC0))) {
                case 4:
                    TargetRefCtor_2e71f0(obj);
                    TargetRefSetAttachPoint_2e65f0(obj, ((short)TargetRefGetId_2e7120(a->sC0)), 0x96, 0);
                    if (TargetRefResolve_2e5ed0(obj, 0) != 0) {
                        if (TargetRefGetPos_2e6a60(obj, &pos) == 0) {
                            break;
                        }
                        pos.y += 5.0f + TargetRefGetRadius_2e7100(obj);
                    } else {
                        if (TargetRefGetPos_2e6a60(a->sC0, &pos) == 0) {
                            break;
                        }
                        pos.y += 10.0f + TargetRefGetRadius_2e7100(a->sC0);
                    }
                    flag = 1;
                    break;
                case 3: {
                    Tgt *t = ObjRecGetLiveObject_1c4a90(tbl, ((short)TargetRefGetId_2e7120(a->sC0)));
                    if (t != 0) {
                        Ent *e;
                        *(u128 *)&pos = t->pos;
                        pos.y += 11.0f + D_0047D5D0 * t->f4CC;
                        e = NpcObjFindDefById_2fb490(GetNpcObjTable_312860(), ((short)TargetRefGetId_2e7120(a->sC0)));
                        if (e != 0) {
                            if (e->flags & 6) {
                                pos.y += 10.0f;
                            }
                        }
                        flag = 1;
                    }
                    break;
                }
                case 13:
                    TargetRefGetPos_2e6a60(a->sC0, &pos);
                    pos.y += 0.5f * D_0045B080[0];
                    flag = 1;
                    break;
                case 7:
                case 9:
                    if (TargetRefGetObj_2e7110(a->sC0) != 0) {
                        TargetRefGetPos_2e6a60(a->sC0, &pos);
                        pos.y += TargetRefGetRadius_2e7100(a->sC0) + 0.5f * D_0045B080[0];
                        flag = 1;
                    }
                    break;
                case 11:
                    if (TargetRefGetObj_2e7110(a->sC0) != 0) {
                        TreasureBoxGetPos_33ae30(TargetRefGetTreasureBox_2e7010(a->sC0), &pos);
                        pos.y += 30.0f;
                        flag = 1;
                    }
                    break;
                case 12:
                    if (TargetRefGetObj_2e7110(a->sC0) != 0) {
                        InsectCageSlotGetPos_39b340(TargetRefGetInsectCageSlot_2e6fd0(a->sC0), &pos);
                        pos.y += 20.0f;
                        flag = 1;
                    }
                    break;
                }
            }
        } else {
            if (((short)TargetRefGetKind_2e7130(a->sC0)) == 4 && TargetRefGetPos_2e6a60(a->sC0, &pos) != 0) {
                if (ProjectToScreenOffset_15d160(&pt, &pos) == 0 || pt.x < 0 || pt.x >= 0x2000 || pt.y < 0 || pt.y >= 0x1C00) {
                    TargetMngSetAimOffscreen_31ed50(a);
                }
            }
        }
        if (flag) {
            ModelSetPos_151110(chr, &pos);
            *(u128 *)&rot = chr->q190;
            rot.y = a->f4;
            ModelSetRot_151080(chr, &rot);
            k = a->fF8 * Sinf_128fd0(a->fF4);
            { u8 *p_ = (u8 *)&sc; u32 n_ = 0x10; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }
            inv = one - dpmul(D_0047D198, k);
            sc.x = inv;
            sc.y = one + dpmul(D_0047D1A0, k);
            sc.z = inv;
            ModelSetScale_150ff0(chr, &sc);
            DrawListAddTexLoad_1418c0(gfx, chr->f4DC, 1.0f);
            chr->v4(1.0f);
            chr->v7();
        }
    }
    TargetMngDrawAimArrow_31eae0(a);
}
