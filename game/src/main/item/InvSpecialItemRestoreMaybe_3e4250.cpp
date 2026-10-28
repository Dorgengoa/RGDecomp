#include "types.h"
#pragma opt_common_subs off
extern "C" {

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))

class VV {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f68(u8 x) { VCM(void, (void *, u8), 0x68, x); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fA0(s32 i, u8 x) { VCM(void, (void *, s32, u8), 0xA0, i, x); }
    
    
    
    void fB0(u8 x) { VCM(void, (void *, u8), 0xB0, x); }
};

class VC_3 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(VV *x0) { VCM(void, (void *, VV *), 0x398, x0); }
};

extern VC_3 *CharaMgrPoolFindById_3a8c60(s32, s32);
extern void InvDiscardItem_3c5010(s32, void *, s32);
extern VV *InvAddItemAtSlot_3c64c0(s32, s16, s16, s32, s32);
extern VV *InvAddItemCoreMaybe_3c6540(s32, s16, s32, s32, s32, s32, s32);
extern void *InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern void InvPurgeRemoved_3c8cc0(s32);
extern volatile s16 D_004801F8;
extern u8 D_004839D8;
extern u8 D_004839DC;
extern u8 D_004839E0[5];

s32 InvSpecialItemRestoreMaybe_3e4250(void *arg0)
{
    VV *o;
    s32 i;
    s16 k;
    void *t;

    t = InvFindInCategoryRange_3c8370(S32(arg0, 0x18), 0x4110, 0, -1, 0, 0);
    k = -1;
    if (t != NULL) {
        k = S16(t, 6);
        InvDiscardItem_3c5010(S32(arg0, 0x18), t, 1);
    }
    InvPurgeRemoved_3c8cc0(S32(arg0, 0x18));
    if (t != NULL) {
        o = InvAddItemAtSlot_3c64c0(S32(arg0, 0x18), D_004801F8, k, 1, 0);
    } else {
        o = InvAddItemCoreMaybe_3c6540(S32(arg0, 0x18), D_004801F8, 0xA, 1, -1, 0, 0);
    }
    if (o == NULL) {
        return 0;
    }
    o->fB0(D_004839D8);
    o->f68(D_004839DC);
    i = 0;
    do {
        o->fA0(i, D_004839E0[i]);
        i++;
    } while (i < 5);
    CharaMgrPoolFindById_3a8c60(S32(arg0, 0x14), 0)->f(o);
    return 1;
}

}
