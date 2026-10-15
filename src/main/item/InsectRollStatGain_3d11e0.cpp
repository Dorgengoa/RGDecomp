/* PARKED s17b: not attempted. Random-draw/shuffle helper with an M2C_BREAK
   (mod-by-a-computed-divisor that m2c couldn't prove nonzero) and a `sp`-only
   (no visible base) array of 5 records -- the stack frame layout needs a
   manual read of asm/matchings/main/InsectRollStatGain_3d11e0.s before a draft is worth
   writing. Not attempted this lane. */
/* s49m: MATCH */
#include "types.h"
#undef NULL
#define NULL 0
#pragma optimization_level 3
#pragma divbyzerocheck on

class Obj {
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
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void f1BC(s32, s32, s32);
};

extern "C" s8 D_004664C8[];
extern "C" s8 D_004664C9[];
extern "C" s8 D_004664CA[];
extern "C" void InsectGetStats_3d1470(Obj *, s32 *);
extern "C" s32 Rand_133710(void);
extern "C" void InsectSetStats_3d13d0(Obj *, s32 *);

extern "C" void InsectRollStatGain_3d11e0(Obj *o, s32 arg1, s32 level)
{
    s32 stats[12];
    s32 picked[5];
    s32 cand[9];
    s32 base;
    s32 i;
    s32 s;
    s32 range;
    s32 n;
    s32 ok;
    s32 count;
    s32 j;
    s32 m;

    o->f1BC(arg1, 0, 0);
    if (level < 0) {
        level = 0;
    }
    if (level > 2) {
        level = 2;
    }
    base = D_004664C8[level * 3];
    range = D_004664C9[level * 3];
    count = D_004664CA[level * 3];
    InsectGetStats_3d1470(o, stats);
    n = 0;
    for (i = 0; i < 5; i++) {
        picked[i] = -1;
    }
    for (; n < count; n++) {
        m = 0;
        for (s = 0; s < 9; s++) {
            ok = 1;
            for (j = 0; j < n; j++) {
                if (s == picked[j]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                cand[m++] = s;
            }
        }
        picked[n] = cand[Rand_133710() % m];
    }
    for (i = 0; i < count; i++) {
        stats[picked[i]] += base + Rand_133710() % range;
    }
    InsectSetStats_3d13d0(o, stats);
}
