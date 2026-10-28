/* rgp:protos */
#line 1
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f1BC(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1BC, a0, a1, a2); }
};

extern "C" s8 D_004664C8[];
extern "C" s8 D_004664C9[];
extern "C" s8 D_004664CA[];
extern "C" void InsectGetStats_3d1470(Obj *, s32 *, int, int);
extern "C" s32 Rand_133710(void);
extern "C" void InsectSetStats_3d13d0(Obj *, s32 *, int, int);

extern "C" void InsectRollStatGain_3d11e0(Obj *o, s32 arg1, s32 level)
{
    s32 stats[12] __attribute__((aligned(16)));
    s32 picked[5] __attribute__((aligned(16)));
    s32 cand[9] __attribute__((aligned(16)));
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
    InsectGetStats_3d1470(o, stats, 0, 0);
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
    InsectSetStats_3d13d0(o, stats, 0, 0);
}
