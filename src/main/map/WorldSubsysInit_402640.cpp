#include "types.h"

class VObj {
public:
    virtual void d8();
    virtual void vC(s32, s32, s32, s32);
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1C();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2C();
    virtual void d30();
    virtual void d34();
    virtual void d38();
    virtual void d3C();
    virtual void d40();
    virtual void d44();
    virtual void d48();
    virtual void v4C();
};

struct Cur {
    VObj o;
    u8 pad[0xA4];
};

typedef struct {
    s32 unk0;
    u8 pad4[4];
    VObj *unk8;
    Cur *unkC;
    VObj *unk10;
} S1;

extern "C" {
extern void *MemStackNew_14e130(s32, s32);
extern s32 MemStackNew_14e0b0(s32, s32);
extern Cur *ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern VObj *DataTableCtor_4033b0(void *);
extern VObj *DataTableCtor_404840(void *);
extern s32 D_004657D0[4];
extern s32 D_004657D8[4];
extern s32 D_004657E0[4];
extern void DataTableCtor_404190(void);
}

extern "C" s32 WorldSubsysInit_402640(S1 *arg0, s32 arg1, s32 arg2)
{
    VObj *p;
    Cur *c;
    s32 i;
    s32 flag;
    s32 param;

    if (arg1 == 0) {
        return 0;
    }
    arg0->unk0 = arg1;
    p = (VObj *)MemStackNew_14e130(0x98, arg1);
    if (p != 0) {
        p = DataTableCtor_404840(p);
    }
    arg0->unk8 = p;
    if (p == 0) {
        return 0;
    }
    arg0->unkC = ConstructNewArray_100710(MemStackNew_14e0b0(0x160, arg0->unk0), (void *)DataTableCtor_404190, 0, 0xA8, 2);
    if (arg0->unkC == 0) {
        return 0;
    }
    p = (VObj *)MemStackNew_14e130(0xA0, arg0->unk0);
    if (p != 0) {
        p = DataTableCtor_4033b0(p);
    }
    arg0->unk10 = p;
    if (arg0->unkC == 0) {
        return 0;
    }
    if (arg0->unk8 != 0) {
        arg0->unk8->vC(arg0->unk0, 0, D_004657D0[0] != 0, 0);
    }
    c = arg0->unkC;
    if (c != 0) {
        flag = D_004657D8[0] != 0;
        for (i = 0; i < 2; i++) {
            param = arg1;
            if (arg2 != 0) {
                param = arg2 + i * 0x58;
            }
            c->o.v4C();
            c->o.vC(param, 0, flag, 0);
            c++;
        }
    }
    if (arg0->unk10 != 0) {
        arg0->unk10->vC(arg0->unk0, 0, D_004657E0[0] != 0, 0);
    }
    return 1;
}
