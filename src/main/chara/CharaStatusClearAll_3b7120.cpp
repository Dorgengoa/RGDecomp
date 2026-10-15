#include "types.h"

struct V3b7120 {
    virtual void _v8();
    virtual void _vc();
    virtual void _v10();
    virtual void _v14();
    virtual void _v18();
    virtual void _v1c();
    virtual void _v20();
    virtual void _v24();
    virtual void _v28();
    virtual void _v2c();
    virtual void _v30();
    virtual void _v34();
    virtual void _v38();
    virtual void _v3c();
    virtual void _v40();
    virtual void _v44();
    virtual void _v48();
    virtual void _v4c();
    virtual void _v50();
    virtual void _v54();
    virtual void _v58();
    virtual void _v5c();
    virtual void _v60();
    virtual void _v64();
    virtual void _v68();
    virtual void _v6c();
    virtual void _v70();
    virtual void _v74();
    virtual void _v78();
    virtual void _v7c();
    virtual void _v80();
    virtual void _v84();
    virtual void _v88();
    virtual void _v8c();
    virtual void _v90();
    virtual void _v94();
    virtual void _v98();
    virtual void _v9c();
    virtual void _va0();
    virtual void _va4();
    virtual void _va8();
    virtual void _vac();
    virtual void _vb0();
    virtual void _vb4();
    virtual void _vb8();
    virtual void _vbc();
    virtual void _vc0();
    virtual void _vc4();
    virtual void _vc8();
    virtual void _vcc();
    virtual void _vd0();
    virtual void _vd4();
    virtual void _vd8();
    virtual void _vdc();
    virtual void _ve0();
    virtual void _ve4();
    virtual void _ve8();
    virtual void _vec();
    virtual void _vf0();
    virtual void _vf4();
    virtual void _vf8();
    virtual void _vfc();
    virtual void _v100();
    virtual void _v104();
    virtual void _v108();
    virtual void _v10c();
    virtual void _v110();
    virtual void _v114();
    virtual void _v118();
    virtual void _v11c();
    virtual void _v120();
    virtual void _v124();
    virtual void _v128();
    virtual void _v12c();
    virtual void _v130();
    virtual void _v134();
    virtual void _v138();
    virtual void _v13c();
    virtual void _v140();
    virtual void _v144();
    virtual void _v148();
    virtual void _v14c();
    virtual void _v150();
    virtual void _v154();
    virtual void _v158();
    virtual void _v15c();
    virtual void _v160();
    virtual void _v164();
    virtual void _v168();
    virtual void _v16c();
    virtual void _v170();
    virtual void _v174();
    virtual void _v178();
    virtual void _v17c();
    virtual void _v180();
    virtual void _v184();
    virtual void _v188();
    virtual void _v18c();
    virtual void _v190();
    virtual void _v194();
    virtual void _v198();
    virtual void _v19c();
    virtual void _v1a0();
    virtual void f1a4(u32);
    virtual void _v1a8();
    virtual void _v1ac();
    virtual void _v1b0();
    virtual void _v1b4();
    virtual void _v1b8();
    virtual void _v1bc();
    virtual void _v1c0();
    virtual void _v1c4();
    virtual void _v1c8();
    virtual void _v1cc();
    virtual void _v1d0();
    virtual void _v1d4();
    virtual void _v1d8();
    virtual void _v1dc();
    virtual void _v1e0();
    virtual void _v1e4();
    virtual void _v1e8();
    virtual void _v1ec();
    virtual void _v1f0();
    virtual void _v1f4();
    virtual void _v1f8();
    virtual void _v1fc();
    virtual void _v200();
    virtual void _v204();
    virtual void _v208();
    virtual void _v20c();
    virtual void _v210();
    virtual void _v214();
    virtual void _v218();
    virtual void _v21c();
    virtual void _v220();
    virtual void _v224();
    virtual void _v228();
    virtual void _v22c();
    virtual void _v230();
    virtual void _v234();
    virtual void _v238();
    virtual void _v23c();
    virtual void _v240();
    virtual void _v244();
    virtual void _v248();
    virtual void _v24c();
    virtual void f250(s32, s32);
    virtual void _v254();
    virtual void f258(s32, s32);
};

struct S3b7120 : V3b7120 {
    u8 pad4[8];
    s32 mC;
    u8 pad10[0xC8 - 0x10];
    u64 mC8;
};

struct B3b7120 {
    u64 *volatile bits;
    volatile u32 idx;
};

extern "C" {
void Abort_12de80(void);
void Fprintf_12f9a0(s32, void *);
s32 GetStatusEffect_2d9010(void);
void StatusEffectStopMatching_33c1c0(s32, s32, s32);
extern u8 *D_00449858[4];
extern u8 D_0045CB40[];
}

static inline s32 test3b7120(B3b7120 *r, u32 i)
{
    u64 *b;
    if (i >= 48) {
        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_0045CB40);
        Abort_12de80();
    }
    b = r->bits;
    return (*b & ((u64)1 << i)) != 0;
}

extern "C" s32 CharaStatusClearAll_3b7120(S3b7120 *self, s32 arg1, s32 arg2, s32 arg3)
{
    s32 h;
    u32 i;
    s32 j;
    B3b7120 r;

    h = GetStatusEffect_2d9010();
    i = 2;
    do {
        r.bits = &self->mC8;
        r.idx = i;
        if (test3b7120(&r, i)) {
            if (i != 31 || arg1 != 0) {
                self->f1a4(i);
            }
        }
        i++;
    } while ((s32)i < 48);
    if (arg2 != 0) {
        self->f250(0, 0);
    }
    if (arg3 != 0) {
        self->f258(0, 0);
    }
    for (j = 0; j <= 11; j++) {
        StatusEffectStopMatching_33c1c0(h, j, self->mC);
    }
    return 1;
}
