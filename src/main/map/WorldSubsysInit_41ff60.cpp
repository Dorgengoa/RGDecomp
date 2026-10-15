#include "types.h"
#undef NULL
#define NULL 0

class A {
public:
    virtual void v08();
    virtual void vC(s32, s32, s32, s32);
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    u8 pad[0xBC];
};

class B {
public:
    virtual void v08();
    virtual void vC(s32, s32, s32, s32);
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    u8 pad[0x94];
};

struct Self {
    s32 heap;
    s32 x4;
    A *a;
    B *b;
};

extern "C" {
void *ConstructNewArray_100710(s32, void *, s32, s32, s32);
s32 MemStackNew_14e0b0(s32, s32);
void DataTableCtor_420350(void);
void DataTableCtor_4209b0(void);
}
extern s32 D_00465808[];
extern s32 D_00465810[];

extern "C" s32 WorldSubsysInit_41ff60(Self *self, s32 arg1, s32 arg2)
{
    A *a;
    B *b;
    s32 i;
    s32 x;
    s32 f;
    s32 j;
    s32 g;

    if (arg1 == 0) {
        return 0;
    }
    self->heap = arg1;
    self->a = (A *)ConstructNewArray_100710(MemStackNew_14e0b0(0x190, arg1), (void *)DataTableCtor_4209b0, 0, 0xC0, 2);
    if (self->a == NULL) {
        return 0;
    }
    self->b = (B *)ConstructNewArray_100710(MemStackNew_14e0b0(0x140, self->heap), (void *)DataTableCtor_420350, 0, 0x98, 2);
    if (self->b == NULL) {
        return 0;
    }
    a = self->a;
    if (a != NULL) {
        f = D_00465808[0] != 0;
        for (i = 0; i < 2; i++) {
            x = arg1;
            if (arg2 != 0) {
                x = arg2 + i * 0x58;
            }
            a->v4C();
            a->vC(x, 0, f, 0);
            a++;
        }
    }
    b = self->b;
    if (b != NULL) {
        g = D_00465810[0] != 0;
        for (j = 0; j < 2; j++) {
            x = arg1;
            if (arg2 != 0) {
                x = arg2 + j * 0x58;
            }
            b->v4C();
            b->vC(x, 0, g, 0);
            b++;
        }
    }
    return 1;
}
