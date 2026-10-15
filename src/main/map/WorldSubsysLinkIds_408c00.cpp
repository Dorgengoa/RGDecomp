#include "types.h"
#pragma opt_common_subs off

class VC_408 {
public:
    virtual void d0();
    virtual void d1();
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
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual s32 f(s32 x0);
};

extern "C" s32 WorldSubsysLinkIds_408c00(void *arg0, void *arg1)
{
    void *top;
    s32 i;
    void *e21_2;
    void **p6;
    s32 v4;
    VC_408 *t4;
    void *e21;
    s32 j;
    s32 k;

    if (arg1 == NULL) {
        return 0;
    }
    top = *(void **)((u8 *)arg0 + 0x8C);
    if (top == NULL) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0x7C) <= 0) {
        return 0;
    }
    i = 0;
    while (i < *(s16 *)((u8 *)arg0 + 0x7C)) {
        e21 = *(void **)((u8 *)top + 0x8);
        j = 0;
        while (j < *(s16 *)((u8 *)top + 0x4)) {
            t4 = *(VC_408 **)((u8 *)*(void **)((u8 *)arg1 + 0x44) + 0x8);
            *(s32 *)((u8 *)e21 + 0x0) = t4->f(*(s16 *)((u8 *)e21 + 0x0));
            p6 = *(void ***)((u8 *)e21 + 0x8);
            k = 0;
            while (k < *(s16 *)((u8 *)e21 + 0x4)) {
                v4 = *(s16 *)p6;
                if (v4 >= 0 && v4 < *(s16 *)((u8 *)top + 0x4)) {
                    *p6 = (u8 *)*(void **)((u8 *)top + 0x8) + v4 * 0x1C;
                } else {
                    *p6 = 0;
                }
                k += 1;
                p6 += 1;
            }
            j += 1;
            e21 = (u8 *)e21 + 0x1C;
        }
        e21_2 = *(void **)((u8 *)top + 0x10);
        j = 0;
        while (j < *(s16 *)((u8 *)top + 0xC)) {
            t4 = *(VC_408 **)((u8 *)*(void **)((u8 *)arg1 + 0x40) + 0x8);
            *(s32 *)e21_2 = t4->f(*(s16 *)e21_2);
            j += 1;
            e21_2 = (u8 *)e21_2 + 4;
        }
        i += 1;
        top = (u8 *)top + 0x18;
    }
    return 1;
}
