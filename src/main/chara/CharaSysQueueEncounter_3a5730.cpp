#include "types.h"

class O3a5730 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual s32 f70(s16);
};
typedef struct A3a5730 {
    u8 pad0[4];
    u8 b0 : 2;
    u8 b2 : 1;
    u8 b3 : 5;
    u8 pad5[7];
    s16 xC;
    s16 xE;
    s16 x10;
    u8 pad12[2];
    s32 x14;
    s32 x18;
} A3a5730;

extern "C" void GameReqQueuePushBack_1f5b50(s32 arg0, s32 arg1);
extern "C" void CharaSysEncounterDistRoll_3a59d0(A3a5730 *arg0, s32 arg1);
extern "C" s16 *PartyGetEncounterRec_3cb040(void *arg0);
extern "C" u8 *D_004837C0;
extern "C" u8 *D_004837C4;

extern "C" s32 CharaSysQueueEncounter_3a5730(A3a5730 *arg0, s32 arg1)
{
    s16 a;
    s16 b;
    s16 c;
    s32 n;
    s16 *p;
    u8 *q;
    O3a5730 *o;
    s32 r;

    if ((D_004837C0 == 0) || (D_004837C4 == 0)) {
        return 0;
    }
    if (*(u8 *)(*(u8 **)(D_004837C0 + 0x20) + 0x24C) & 1) {
        return 0;
    }
    if (!arg0->b2) {
        return 0;
    }
    if (arg0->x10 >= 0 || arg0->x14 != 0 || arg0->x18 != 0) {
        return 0;
    }
    a = -1;
    n = 0;
    b = a;
    c = a;
    if (arg1 < 0) {
        p = PartyGetEncounterRec_3cb040(*(void **)(D_004837C0 + 0x18));
        if (p == 0) {
            CharaSysEncounterDistRoll_3a59d0(arg0, 1);
            return 0;
        }
        c = *p;
        q = *(u8 **)(D_004837C0 + 0x18);
        a = *(s16 *)(q + 0x7E);
        b = *(s16 *)(q + 0x82);
    } else {
        o = *(O3a5730 **)(*(u8 **)(D_004837C4 + 0x70) + 8);
        r = o->f70(arg1);
        n = r;
        if (r == 0) {
            return 0;
        }
    }
    arg0->xC = a;
    arg0->xE = b;
    arg0->x10 = c;
    arg0->x14 = n;
    GameReqQueuePushBack_1f5b50(7, 0);
    return 1;
}
