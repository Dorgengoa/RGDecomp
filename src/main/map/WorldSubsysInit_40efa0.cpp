#include "types.h"
extern "C" {
extern void *MemStackNew_14e130(u32, s32);
extern void *MemStackNew_14e0b0(u32, s32);
extern void *ConstructNewArray_100710(void *, void *, void *, u32, u32);
extern void *DataTableCtor_410430(void *);
extern void *DataTableCtor_40f7b0(void *);
extern s32 D_00465818[4];
extern s32 D_00465820[4];
extern s32 D_00465828[4];
extern s32 D_00465830[4];
}

class VO {
public:
    virtual void d0();
    virtual void f(s32 a, s32 b, bool c, s32 d);
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void g();
};

struct T {
    s32 x0;
    s32 x4;
    VO *x8;
    u8 *xC;
    VO *x10;
    u8 *x14;
};

extern "C" s32 WorldSubsysInit_40efa0(T *t, s32 a1, u8 *a2) {
    void *p;
    u8 *q;
    s32 i;
    s32 arg;
    bool flag;

    if (a1 == 0) {
        return 0;
    }
    t->x0 = a1;
    p = MemStackNew_14e130(0x3E0, a1);
    if (p != NULL) {
        p = DataTableCtor_410430(p);
    }
    t->x8 = (VO *)p;
    if (p == NULL) {
        return 0;
    }
    p = MemStackNew_14e130(0x98, t->x0);
    if (p != NULL) {
        p = DataTableCtor_40f7b0(p);
    }
    t->x10 = (VO *)p;
    if (p == NULL) {
        return 0;
    }
    t->xC = (u8 *)ConstructNewArray_100710(MemStackNew_14e0b0(0x7D0, t->x0), (void *)DataTableCtor_410430, NULL, 0x3E0, 2);
    if (t->xC == NULL) {
        return 0;
    }
    t->x14 = (u8 *)ConstructNewArray_100710(MemStackNew_14e0b0(0x140, t->x0), (void *)DataTableCtor_40f7b0, NULL, 0x98, 2);
    if (t->x14 == NULL) {
        return 0;
    }
    if (t->x8 != NULL) {
        t->x8->g();
        t->x8->f(a1, 0, D_00465818[0] != 0, 0);
    }
    if (t->x10 != NULL) {
        t->x10->g();
        t->x10->f(a1, 0, D_00465820[0] != 0, 0);
    }
    q = t->xC;
    if (q != NULL) {
        i = 0;
        flag = D_00465828[0] != 0;
        for (; i < 2; i++) {
            arg = a1;
            if (a2 != NULL) {
                arg = (s32)(a2 + i * 0x58);
            }
            ((VO *)q)->g();
            ((VO *)q)->f(arg, 0, flag, 0);
            q += 0x3E0;
        }
    }
    q = t->x14;
    if (q != NULL) {
        i = 0;
        flag = D_00465830[0] != 0;
        for (; i < 2; i++) {
            arg = a1;
            if (a2 != NULL) {
                arg = (s32)(a2 + i * 0x58);
            }
            ((VO *)q)->g();
            ((VO *)q)->f(arg, 0, flag, 0);
            q += 0x98;
        }
    }
    return 1;
}
