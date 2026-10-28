#include "types.h"

struct GObj {
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v15(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
    
    
    
    
    
    void v21() { VCM0(void, 0x5C); }
};

struct MObj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v15() { VCM0(void, 0x44); }
    
    
    
    
    
    void v21() { VCM0(void, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 w72() { return VCM0(s32, 0x128); }
};

extern "C" GObj *D_004832F8;
extern "C" s32 D_004832FC;
extern "C" f32 D_004832F0;
extern "C" f32 D_004832F4;
extern "C" f32 D_0047FBC0, D_0047FBC4, D_0047FBC8, D_0047FBCC;
extern "C" f32 D_0047D410, D_0047D414, D_0047D3B4, D_0047D288;
extern "C" u8 D_00463EC0[];

extern "C" {
void GetDrawCtxNameTable_15de40(void);
void MemStackReset_14d830(s32);
void ModelObjExCopy_1aff40(void *, void *, s32);
void ModelSetPos_151110(void *, f32 *);
void ModelSetRot_151080(void *, f32 *);
void ModelSetScale_150ff0(void *, f32 *);
void ModelObjPlayMotionByName_1867a0(void *, void *, s32);
s32 MenuObjInsectGetDefId_386d70(void *);
void *InsectCageAdjFindById_3916e0(s32);
void InsectModelApplyColorRec_3913f0(void *, s32, s32);
void InsectCagePreviewModelSetup_389370(void *ent, s32 mode);
}

void InsectCagePreviewModelSetup_389370(void *ent, s32 mode)
{
    volatile f32 va[4] __attribute__((aligned(16)));
    f32 vb[4] __attribute__((aligned(16)));
    f32 vc[4] __attribute__((aligned(16)));
    f32 vd[4] __attribute__((aligned(16)));
    f32 ve[4] __attribute__((aligned(16)));
    GObj *o1;
    u8 *q;
    u32 n;
    s32 id;
    void *o;
    f32 t;

    GetDrawCtxNameTable_15de40();
    MemStackReset_14d830(D_004832FC);
    D_004832F8->v21();
    if (ent != 0) {
        ModelObjExCopy_1aff40(ent, D_004832F8, D_004832FC);
        va[0] = D_0047FBC0;
        va[1] = D_0047FBC4;
        va[2] = D_0047FBC8;
        va[3] = D_0047FBCC;
        va[2] = 70.0f;
        va[0] = 0.0f;
        va[1] = 0.0f;
        ModelSetPos_151110(D_004832F8, (f32 *)va);
        o1 = D_004832F8;
        q = (u8 *)vb;
        n = 0x10;
        if (q != 0) { do { *q = 0; n--; q++; } while (n != 0); }
        vb[0] = D_0047D410;
        vb[1] = D_0047D414;
        vb[2] = 0.0f;
        ModelSetRot_151080(o1, vb);
        *(s32 *)((u8 *)D_004832F8 + 0x450) = 0;
        ModelObjPlayMotionByName_1867a0(D_004832F8, (u8 *)ent + 0x974, 0);
        D_004832F8->v15(1.0f);
        o = InsectCageAdjFindById_3916e0(MenuObjInsectGetDefId_386d70(ent));
        id = *(s32 *)((u8 *)ent + 0x970);
        switch (mode) {
        case 0:
            D_004832F0 = 1940;
            D_004832F4 = 1998;
            if (o != 0) {
                D_004832F0 = *(f32 *)((u8 *)o + 0x8);
                D_004832F4 = *(f32 *)((u8 *)o + 0xC);
                t = *(f32 *)((u8 *)o + 0x4);
                o1 = D_004832F8;
                q = (u8 *)vc;
                n = 0x10;
                if (q != 0) { do { *q = 0; n--; q++; } while (n != 0); }
                vc[0] = t;
                vc[1] = t;
                vc[2] = t;
                ModelSetScale_150ff0(o1, vc);
            } else {
                D_004832F0 = 1940;
                D_004832F4 = 1988;
                o1 = D_004832F8;
                q = (u8 *)vd;
                n = 0x10;
                if (q != 0) { do { *q = 0; n--; q++; } while (n != 0); }
                vd[0] = D_0047D3B4;
                vd[1] = D_0047D3B4;
                vd[2] = D_0047D3B4;
                ModelSetScale_150ff0(o1, vd);
                if (*(s8 *)((u8 *)ent + 0x984) != 0) {
                    D_004832F4 = D_004832F4 + 30.0f;
                }
            }
            break;
        case 1:
            D_004832F0 = 1855;
            D_004832F4 = 1888.0f;
            if (*(s8 *)((u8 *)ent + 0x984) != 0) {
                D_004832F4 = D_004832F4 + 9.5f;
            }
            o1 = D_004832F8;
            q = (u8 *)ve;
            n = 0x10;
            if (q != 0) { do { *q = 0; n--; q++; } while (n != 0); }
            ve[0] = D_0047D288;
            ve[1] = D_0047D288;
            ve[2] = D_0047D288;
            ModelSetScale_150ff0(o1, ve);
            break;
        }
        ModelObjPlayMotionByName_1867a0(D_004832F8, D_00463EC0, 4);
        D_004832F8->v15(1.0f);
        InsectModelApplyColorRec_3913f0(D_004832F8, id, ((MObj *)*(void **)((u8 *)ent + 0x96C))->w72());
    }
}
