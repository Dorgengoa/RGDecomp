#include "types.h"
#undef NULL
#define NULL 0

class VC_0 {
public:
    virtual void d0();
    virtual void f(s32 x0, s32 x1, s32 x2, s32 x3);
};
struct A { s32 x0; s32 x4; VC_0 *x8; VC_0 *xC; };

extern "C" {
extern VC_0 *ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e0b0(s32, s32);
extern s32 D_004657E8[0x100];
extern s32 D_004657F0[0x100];
extern void DataTableCtor_425d40();
extern void DataTableCtor_4263a0();

s32 WorldSubsysInit_425980(A *arg0, s32 arg1, s32 arg2)
{
    VC_0 *p;
    s32 i;
    s32 fl;
    s32 v;
    VC_0 *t;

    if (arg1 == 0) {
        return 0;
    }
    arg0->x0 = arg1;
    t = ConstructNewArray_100710(MemStackNew_14e0b0(0x140, arg1), (void *)DataTableCtor_4263a0, 0, 0x98, 2);
    arg0->x8 = t;
    if (t == NULL) {
        return 0;
    }
    t = ConstructNewArray_100710(MemStackNew_14e0b0(0x140, arg0->x0), (void *)DataTableCtor_425d40, 0, 0x98, 2);
    arg0->xC = t;
    if (t == NULL) {
        return 0;
    }
    p = arg0->x8;
    if (p != NULL) {
        i = 0;
        fl = *D_004657E8 != 0;
        do {
            v = arg1;
            if (arg2 != 0) {
                v = arg2 + i * 0x58;
            }
            p->f(v, 0, fl, 0);
            i += 1;
            p = (VC_0 *)((u8 *)p + 0x98);
        } while (i < 2);
    }
    p = arg0->xC;
    if (p != NULL) {
        i = 0;
        fl = *D_004657F0 != 0;
        do {
            v = arg1;
            if (arg2 != 0) {
                v = arg2 + i * 0x58;
            }
            p->f(v, 0, fl, 0);
            i += 1;
            p = (VC_0 *)((u8 *)p + 0x98);
        } while (i < 2);
    }

    return 1;
}
}
