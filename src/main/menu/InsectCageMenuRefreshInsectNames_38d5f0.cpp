#include "types.h"
#pragma opt_loop_invariants off
class VC_38d {
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
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual s32 f(s32 x);
};

extern "C" {
s32 UiSetTextString_28f510(s32, s32, s32, s32);
s32 InsectCageMenuSlotTextSetStateMaybe_38d550(s32, s32);
VC_38d *InsectCageMenuGetCageInsect_390f00(s32, s32);
s32 InsectCageMenuHasCage_391080(s32);
extern s32 D_00483308;

void InsectCageMenuRefreshInsectNames_38d5f0(void) {
    s32 i;
    s32 j;
    s32 r;
    VC_38d *o;

    i = 0;
    do {
        j = 0;
        do {
            r = 0;
            if (InsectCageMenuHasCage_391080(i) != 0) {
                o = InsectCageMenuGetCageInsect_390f00(i, j);
                if (o != NULL) {
                    r = o->f(0);
                }
            }
            UiSetTextString_28f510(D_00483308, (i + 0x7580) & 0xFFFF, r, j);
            j += 1;
        } while (j < 5);
        InsectCageMenuSlotTextSetStateMaybe_38d550(i, 1);
        i += 1;
    } while (i < 3);
}
}
