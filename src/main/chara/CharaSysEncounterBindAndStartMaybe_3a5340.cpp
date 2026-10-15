#include "types.h"

class VA {
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
    virtual u8 *Get(s16);
};

struct Unit {
    u8 pad0[0x7e];
    s8 f0 : 1;
    s8 f1 : 1;
    s8 f2 : 1;
    s8 f3 : 5;
};

struct Sub {
    u8 pad0[0x18];
    Unit *m18;
    u8 pad1c[8];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 6;
    u8 pad25[3];
    s32 m28;
    u8 pad2c[0x14];
    s32 m40;
    u8 pad44[0x168 - 0x44];
    u8 m168[4];
};

struct Actor {
    u8 pad0[4];
    u8 a0 : 1;
    u8 a1 : 1;
    u8 a2 : 1;
    u8 a3 : 5;
    u8 pad5[0x13];
    Unit *m18;
    s32 m1C;
    u8 pad20[0x238 - 0x20];
    Sub *m238;
};

struct G20 { u8 pad[0x24c]; u8 m24C; };
struct G0 { u8 pad[0x20]; G20 *m20; };
struct H70 { u8 pad[0x10]; VA *m10; };
struct H0 { u8 pad[0x70]; H70 *m70; };

extern "C" s32 BattleEncounterStart_3a41f0(Actor *, Unit *, s32);
extern "C" void CharaSysEncounterDistRoll_3a59d0(Actor *, s32);
extern "C" void BattleRecordReset_3a7fd0(u8 *);
extern G0 *D_004837C0;
extern H0 *D_004837C4;

extern "C" s32 CharaSysEncounterBindAndStartMaybe_3a5340(Actor *a, s32 arg1, s32 arg2)
{
    Unit *u;
    Sub *s;
    s32 r;

    if (D_004837C0 == 0) {
        return 0;
    }
    if (D_004837C0->m20->m24C & 1) {
        return 0;
    }
    if (!a->a2) {
        return 0;
    }
    if (arg1 < 0) {
        s = a->m238;
        u = a->m18;
        if (s != 0) {
            s->m18 = u;
            a->m238->m28 = a->m1C;
        }
        a->m18 = 0;
        a->m1C = -1;
    } else {
        u = (Unit *)D_004837C4->m70->m10->Get((s16)arg1);
    }
    if (u == 0) {
        CharaSysEncounterDistRoll_3a59d0(a, 1);
        return 0;
    }
    s = a->m238;
    if (s != 0) {
        s->m18 = u;
        if (u != 0) {
            a->m238->b0 = u->f1 != 0;
            a->m238->b1 = !u->f2;
        }
        a->m238->m40 = 0;
    }
    r = BattleEncounterStart_3a41f0(a, u, 0);
    s = a->m238;
    if (s != 0) {
        BattleRecordReset_3a7fd0(s->m168);
    }
    if (r <= 0) {
        CharaSysEncounterDistRoll_3a59d0(a, 1);
    } else {
        s = a->m238;
        if (s != 0) {
            s->m28 = arg2;
        }
    }
    return r;
}
