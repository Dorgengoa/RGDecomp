#include "types.h"

class VBase {
public:
    virtual void *slot00();
    virtual void *slot01();
    virtual void *slot02();
    virtual void *slot03();
    virtual void *slot04();
    virtual void *slot05();
    virtual void *slot06();
    virtual void *slot07();
    virtual void *slot08();
    virtual void *slot09();
    virtual void *slot0A();
    virtual void *slot0B();
    virtual void *slot0C();
    virtual void *slot0D();
    virtual void *slot0E();
    virtual void *slot0F();
    virtual void *slot10();
    virtual void *slot11();
    virtual void *slot12();
    virtual void *slot13();
    virtual void *slot14();
    virtual void *slot15();
    virtual void *slot16();
    virtual void *slot17();
    virtual void *slot18();
    virtual void *slot19();
    virtual s32 slot1A(s16 val);
};

struct C2 {
    u8 pad0[8];
    VBase *unk8;
};

struct Arg1 {
    u8 pad0[0x48];
    C2 *unk48;
};

struct Node {
    u8 pad0[0x10];
    union {
        s16 s;
        s32 w;
    } f10;
    union {
        s16 s;
        s32 w;
    } f14;
};

extern "C" s32 IterNext_370040(void *);
extern "C" void IterInit_370170(void *, s32);
extern "C" void *AbilityDataGetKind0Rec_3f5db0(s32);

extern "C" s32 WorldSubsysLinkIds_3f49c0(s32 arg0, Arg1 *arg1)
{
    u8 sp38[8];
    s32 temp_2;
    s32 var_5;
    Node *temp_2_2;

    if (arg1 == 0) {
        return 0;
    }
    var_5 = arg0;
    if (arg0 != 0) {
        var_5 += 0x88;
    }
    IterInit_370170(sp38, var_5);
    goto test;
body:
    temp_2_2 = (Node *) AbilityDataGetKind0Rec_3f5db0(temp_2);
    if (temp_2_2 != 0) {
        temp_2_2->f10.w = arg1->unk48->unk8->slot1A(temp_2_2->f10.s);
        temp_2_2->f14.w = arg1->unk48->unk8->slot1A(temp_2_2->f14.s);
    }
test:
    temp_2 = IterNext_370040(sp38);
    if (temp_2 != 0) {
        goto body;
    }
    return 1;
}
