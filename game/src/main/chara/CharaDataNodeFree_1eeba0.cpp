#include "types.h"

class Comp {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f54(s32 a0) { VCM(void, (void *, s32), 0x54, a0); }
    void f58() { VCM0(void, 0x58); }
    u8 pad1B4[0x790 - 0x1B4];
};

struct Obj {
    u8 pad0[8];
    s16 m8;
    s16 mA;
    s32 mC;
    u8 pad10[4];
    s16 m14[4];
    s16 m1C;
    u8 pad1E[2];
    Comp *m20;
    s32 m24;
    u8 pad28[2];
    s16 m2A;
    Comp *m2C;
};

extern "C" {
extern void NameTableFreeGroup_158ac0(s32, s32);
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void ModelObjExUnlinkAttachById_1afeb0(Comp *, Comp *);
extern void ModelObjExEffectsStopAll_1b0870(Comp *);
extern void SoundBankPartFree_1b9b00(Comp *);
extern void LoaderReleaseById_1cd340(s32, s32);
extern s32 IdSlotTableFind_1efa60(void *, s32);
extern u8 *IdSlotTableGet_1efaa0(void *, s32);
extern void IdSlotTableClear_1efad0(void *, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern u8 D_004B3910[];
}

extern "C" void CharaDataNodeFree_1eeba0(Obj *arg0) {
    s32 i;
    u8 *p;

    if (arg0->mC > -1) {
        s32 t = GetLoaderMgr_1f59d0();
        LoaderReleaseById_1cd340(t, arg0->mC);
    }
    switch (arg0->m8) {
    case 0:
        if (arg0->m20 == 0) {
            break;
        }
        IdSlotTableClear_1efad0(D_004B3910, IdSlotTableFind_1efa60(D_004B3910, arg0->mA));
        ModelObjExEffectsStopAll_1b0870(arg0->m20);
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), *(s32 *)((u8 *)arg0->m20 + 0x4DC));
        arg0->m20->f58();
        arg0->m20->f54((s32)arg0->m20);
        ModelObjExUnlinkAttachById_1afeb0(arg0->m20, arg0->m20);
        *(s32 *)((u8 *)arg0->m20 + 0x530) = 0;
        if (arg0->m2C != 0) {
            for (i = 0; i < arg0->m2A; i++) {
                arg0->m2C[i].f58();
            }
            arg0->m2C = 0;
        }
        arg0->m2A = 0;
        break;
    case 1:
        if (IdSlotTableGet_1efaa0(D_004B3910, IdSlotTableFind_1efa60(D_004B3910, arg0->m24)) == 0) {
            break;
        }
        for (i = 0; i < arg0->m1C; i++) {
            arg0->m20->f54(arg0->m14[i]);
        }
        DrawCtxVif1HandlerStop_15dc40();
        break;
    case 2:
        if (IdSlotTableGet_1efaa0(D_004B3910, IdSlotTableFind_1efa60(D_004B3910, arg0->m24)) == 0) {
            break;
        }
        for (i = 0; i < arg0->m1C; i++) {
            arg0->m20->f54(arg0->m14[i]);
        }
        break;
    case 5:
        SoundBankPartFree_1b9b00(arg0->m20);
        p = IdSlotTableGet_1efaa0(D_004B3910, IdSlotTableFind_1efa60(D_004B3910, arg0->m24));
        if (p == 0) {
            break;
        }
        *(s32 *)(p + 0x4FC) = -1;
        break;
    case 4:
        arg0->m20 = 0;
        break;
    }
}
