#include "types.h"

class VObj003FA780 {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
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
    virtual s32 slot70(s16);
};

typedef struct {
    u8 pad0[0x8];
    VObj003FA780 *unk8;
    u8 padC[4];
    VObj003FA780 *unk10;
} Hold003FA780;

typedef struct {
    u8 pad0[0x48];
    Hold003FA780 *unk48;
    Hold003FA780 *unk4C;
    Hold003FA780 *unk50;
    u8 pad54[8];
    Hold003FA780 *unk5C;
} Tbl003FA780;

typedef struct {
    u8 pad0[0x8];
    s32 unk8;
    s32 unkC;
    s32 unk10[3];
    u8 pad1C[4];
    s32 unk20;
    s16 unk24;
    u8 pad26[2];
    s32 *unk28;
} Item003FA780;

typedef struct {
    s32 a;
    s32 b;
} Iter003FA780;

extern "C" {
Item003FA780 *IterNext_370040(Iter003FA780 *);
void IterInit_370170(Iter003FA780 *, s32);
}

static inline Item003FA780 *NextIt(Iter003FA780 *p) { return IterNext_370040(p); }
extern "C" s32 WorldSubsysLinkIds_3fa780(s32 arg0, Tbl003FA780 *arg1)
{
    Iter003FA780 it;
    s32 b;
    Item003FA780 *p;
    s32 i;
    s32 *q;
    s32 i2;

    if (arg1 == NULL) {
        return 0;
    }
    b = arg0;
    if (arg0 != 0) {
        b += 0x88;
    }
    IterInit_370170(&it, b);
    while ((p = NextIt(&it)) != NULL) {
        p->unk8 = arg1->unk4C->unk8->slot70(p->unk8);
        p->unkC = arg1->unk50->unk8->slot70(p->unkC);
        for (i = 0; i < 3; i++) {
            q = &p->unk10[i];
            *q = arg1->unk5C->unk8->slot70(*q);
        }
        p->unk20 = arg1->unk5C->unk8->slot70(p->unk20);
        for (i2 = 0; i2 < p->unk24; i2++) {
            q = &p->unk28[i2];
            *q = arg1->unk48->unk10->slot70(*q);
        }
    }
    return 1;
}
