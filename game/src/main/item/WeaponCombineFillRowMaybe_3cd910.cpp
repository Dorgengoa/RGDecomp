/* rgp:protos */
#line 1
#include "types.h"


struct Src {
    s16 h0;
    __extension__ unsigned short a : 1;
    unsigned short b : 1;
    unsigned short c : 10;
} __attribute__((aligned(2)));
struct Item {
    s16 h0;
    u8 b2;
    u8 x0 : 1;
    u8 x1 : 1;
    u8 x2 : 1;
    u8 x3 : 1;
    u8 f4 : 1;
    s16 h4;
};
struct Ent {
    s32 h;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
};
struct Dst {
    __extension__ unsigned short v : 10;
    unsigned short f10 : 1;
    unsigned short f11 : 1;
    u8 pad2[2];
    Ent e[3];
} __attribute__((aligned(2)));
class VObj {
public:
    VC_VPTR_MEMBER;    
        
        
        
        
    
    s32 Get(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};
struct G1 { u8 pad[0x18]; s32 f18; };
struct G2b { u8 pad[8]; VObj *f8; };
struct G2 { u8 pad[0x40]; G2b *f40; };

extern "C" {
Item *RecTableBinSearch_407bb0(s32, s16, s32);
Item *RecTableFindByByteId_407c70(s32, u8);
void WeaponCombineLookupByIds_3c45c0(s32, long long, bool, long long, bool, s32 *, u8 *, u8 *, s32 *, s32, s32, Item **);
s32 InvHasWeaponWithSuffixFlagMaybe_3c7e00(s32, s32, bool, s32, s32);
s32 InvHasFullyGrownWeaponMaybe_3c7cb0(s32, s32, bool, s32);
}
extern "C" G1 *D_004838B8;
extern "C" G2 *D_004838BC;

extern "C" s32 WeaponCombineFillRowMaybe_3cd910(Src *src, Dst *dst, s32 arg2) {
    u8 c7F;
    u8 c7E;
    s32 c78;
    s32 c74;
    Item *p70;
    Item *x;
    Item *y;
    Ent *e;

    if (dst == 0 || arg2 == 0) return 0;
    x = RecTableBinSearch_407bb0(arg2, src->h0, src->a);
    if (x == 0) return 0;
    y = RecTableFindByByteId_407c70(arg2, x->b2);
    if (y == 0) return 0;
    c78 = 0;
    c7F = 0;
    c7E = 0;
    c74 = 0;
    p70 = 0;
    WeaponCombineLookupByIds_3c45c0(D_004838B8->f18, (long long)(x->h4), x->f4, (long long)(y->h4), y->f4, &c78, &c7F, &c7E, &c74, 0, 0, &p70);
    dst->v = src->c;
    dst->f10 = 1;
    dst->f11 = 1;

    e = &dst->e[0];
    e->h = D_004838BC->f40->f8->Get(x->h4);
    e->b0 = x->f4 != 0;
    e->b1 = 1;
    e->b2 = InvHasWeaponWithSuffixFlagMaybe_3c7e00(D_004838B8->f18, x->h4, x->f4, 0, 0);
    e->b3 = InvHasFullyGrownWeaponMaybe_3c7cb0(D_004838B8->f18, x->h4, x->f4, 0);
    if (!e->b2) dst->f10 = false;
    if (!e->b3) dst->f11 = false;

    e = &dst->e[1];
    e->h = D_004838BC->f40->f8->Get(y->h4);
    e->b0 = y->f4 != 0;
    e->b1 = 1;
    e->b2 = InvHasWeaponWithSuffixFlagMaybe_3c7e00(D_004838B8->f18, y->h4, y->f4, 0, 0);
    e->b3 = InvHasFullyGrownWeaponMaybe_3c7cb0(D_004838B8->f18, y->h4, y->f4, 0);
    if (!e->b2) dst->f10 = false;
    if (!e->b3) dst->f11 = false;

    e = &dst->e[2];
    e->h = D_004838BC->f40->f8->Get(p70->h4);
    e->b0 = p70->f4 != 0;
    e->b1 = dst->v > 0;
    e->b2 = InvHasWeaponWithSuffixFlagMaybe_3c7e00(D_004838B8->f18, p70->h4, p70->f4, 0, 0);
    e->b3 = false;
    return 1;
}
