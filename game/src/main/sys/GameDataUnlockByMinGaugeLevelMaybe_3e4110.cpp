/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x17];
    u8 lo7 : 7;
    u8 hi : 1;
    u8 pad18[0x1F - 0x18];
    s8 lo : 1;
    s8 hi7 : 7;
} Elem003E4110;

class Item003E4110 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v364() { return VCM0(s32, 0x364); }
    
    s32 v36C() { return VCM0(s32, 0x36C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v4BC() { return VCM0(s32, 0x4BC); }
};

class VObj003E4110 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Elem003E4110 * slot70(s16 a0) { return VCM(Elem003E4110 *, (void *, s16), 0x70, a0); }
};

typedef struct {
    u8 pad0[0x8];
    VObj003E4110 *unk8;
} Hold003E4110;

typedef struct {
    u8 pad0[0x40];
    Hold003E4110 *unk40;
} Mgr003E4110;

typedef struct {
    u8 pad0[0x8];
    Mgr003E4110 *unk8;
    u8 padC[0x14 - 0xC];
    s32 unk14;
} Obj003E4110;

typedef struct {
    s32 a;
    s32 b;
} Iter003E4110;

extern "C" {
Item003E4110 *IterNext_370040(Iter003E4110 *);
void IterInit_370170(Iter003E4110 *, s32, int, int);
extern s16 D_00466B68[];
}

extern "C" s32 GameDataUnlockByMinGaugeLevelMaybe_3e4110(Obj003E4110 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    Iter003E4110 it __attribute__((aligned(16)));
    s32 b;
    s32 min;
    Item003E4110 *p;
    s32 v;
    s32 i;
    Elem003E4110 *e;

    b = arg0->unk14;
    min = -1;
    if (b != 0) {
        b += 4;
    }
    IterInit_370170(&it, b, (int)rgp_a2, (int)rgp_a3);
    goto nxt;
top:
    if (p->v364() != 0 && p->v36C() == 0) {
        v = p->v4BC();
        if (min < 0 || v < min) {
            min = v;
        }
    }
nxt:
    p = IterNext_370040(&it);
    if (p != NULL) {
        goto top;
    }
    for (i = 1; i <= 3; i++) {
        if (min >= i) {
            e = arg0->unk8->unk40->unk8->slot70(D_00466B68[i - 1]);
            e->hi = 1;
            e->lo = 1;
        }
    }
    return 1;
}
