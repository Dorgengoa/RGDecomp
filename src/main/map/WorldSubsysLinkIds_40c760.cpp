#include "types.h"

class V {
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
    virtual s32 f70(s16);
};

typedef struct {
    u8 pad0[8];
    V *unk8;
    V *unkC;
} Holder;

typedef struct {
    u8 pad0[0x48];
    Holder *unk48;
    u8 pad4C[0x1C];
    Holder *unk68;
} Obj;

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x24 - 8];
    s32 unk24;
    s32 unk28;
} E;

typedef struct {
    s32 a;
    s32 b;
} Iter;

extern "C" {
E *IterNext_370040(Iter *);
void IterInit_370170(Iter *, u8 *);
E *ItemDefGetInsectData_40e0b0(E *);
E *ItemDefGetWeaponData_40e110(E *);
}

extern "C" s32 WorldSubsysLinkIds_40c760(u8 *arg0, Obj *arg1)
{
    Iter it;
    E *e;
    E *s;
    u8 *t;

    if (arg1 == NULL) {
        return 0;
    }
    t = arg0;
    if (t != NULL) {
        t += 0x88;
    }
    IterInit_370170(&it, t);
    while (e = IterNext_370040(&it), e != NULL) {
        e->unk24 = arg1->unk48->unk8->f70(e->unk24);
        e->unk28 = arg1->unk48->unk8->f70(e->unk28);
        s = ItemDefGetWeaponData_40e110(e);
        if (s != NULL) {
            s->unk28 = arg1->unk48->unk8->f70(s->unk28);
        }
        s = ItemDefGetInsectData_40e0b0(e);
        if (s != NULL) {
            s->unk4 = arg1->unk68->unkC->f70(s->unk4);
        }
    }
    return 1;
}
