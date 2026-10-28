/* rgp:protos */
#line 1
#include "types.h"

typedef struct Arg { s32 a; s32 b; } Arg;

class VA {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * Find(s16 a0) { return VCM(u8 *, (void *, s16), 0x70, a0); }
};

class VB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Set(s8 * a0) { VCM(void, (void *, s8 *), 0x114, a0); }
};

struct R40 { u8 pad[8]; VA *m8; };
struct R8 { u8 pad[0x40]; R40 *m40; };
struct R94 { u8 pad[8]; R8 *m8; u8 padc[0xc]; s32 m18; };
struct G {
    u8 pad[0x94];
    R94 *m94;
    u8 pad98[2];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 5;
};

extern "C" s8 *SlotGetInt_15f720(Arg *);
extern "C" int VariantGetInt_15f780(Arg *);
extern "C" void InvAddItemAtSlot_3c64c0(s32, int, int, s32, s32);
extern "C" s32 InvGetCageItem_3c8040(s32, s32);
extern "C" VB *InsectItemCreateWithRandomName_3cff30(s32, s16);
extern "C" s32 atoi(const s8 *);
extern "C" G *D_004830F8;

extern "C" s32 WorldDataCmdAddItemMaybe_3b9d40(Arg *p)
{
    G *g;
    s64 a;
    s64 b;
    s8 *str;
    VB *vb;
    s32 i;
    s32 h;
    s32 cnt;
    u8 *r;

    g = D_004830F8;
    if (!g->b2) {
        return 1;
    }
    a = VariantGetInt_15f780(p++);
    b = VariantGetInt_15f780(p++);
    str = SlotGetInt_15f720(p);
    r = g->m94->m8->m40->m8->Find(b);
    r = (u8 *)(s32)r;
    if (r == 0) {
        return 1;
    }
    if (*(s8 *)(r + 2) == 0x14) {
        vb = 0;
        for (i = 0; i < 3; i++) {
            h = InvGetCageItem_3c8040(g->m94->m18, i);
            if (h == 0) continue;
            vb = InsectItemCreateWithRandomName_3cff30(h, *(s16 *)r);
            if (vb != 0) break;
        }
        if (vb != 0) {
            vb->Set(str);
        }
    } else {
        cnt = 1;
        if (str != 0 && *str == 0x2A) {
            cnt = atoi(str + 1);
        }
        InvAddItemAtSlot_3c64c0(g->m94->m18, (int)(b), (int)(a), cnt, 0);
    }
    return 1;
}
