/* rgp:protos */
#define RGP_SELF_SoundSetPan_1b8590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct P {
    u8  pad000[0x4];
    s16 f4;
    s8  f6;
    u8  pad007[0x3];
    s8  fA;
    u8  pad00B[0x5];
};

struct Buf {
    u8 pad000[0x8];
    struct P *f8;
    u8 pad00C[0x4];
};

struct T3 { u8 pad000[0x6]; s8 f6; s8 f7; u8 pad008[0x4]; };
struct T2 { u8 pad000[0x18]; s32 f18; struct T3 *f1C; u8 pad020[0x18]; };
struct T1 { u8 pad000[0x4]; s32 f4; u8 pad008[0x10]; struct T2 e[5]; u8 pad130[0xB0]; };

extern struct T1 D_0049EB10[];
/*rgp*/
/*rgp*/

void SoundSetPan_1b8590(s32 a, s32 b, s32 c, void *d)
{
    struct Buf buf __attribute__((aligned(16)));
    struct P *p;
    struct T1 *t1;
    struct T2 *t2;
    struct T3 *t3;
    struct T1 *u1;
    struct T2 *u2;
    s32 m;
    s32 dd;
    s32 ok;
    s32 r;
    s32 f7v;

    if (a != -1) {
        SoundResolveKey_1b9970(&buf, a, b);
        p = buf.f8;
        if (p != 0) {
            if (p->f6 == 4) {
                if (p->fA >= 0) {
                    b = p->f4;
                    a = (p->fA & 0xFF) << 24;
                }
            }
        }
    }
    if (a == -1) {
        return;
    }
    m = (s32)(((u32)a >> 24) & 0xFF);
    dd = (s32)(((u32)a >> 16) & 0xFF);
    if (m < 0 || m > 0x10) {
        t1 = 0;
    } else {
        t1 = &D_0049EB10[m];
    }
    if (t1 == 0) {
        return;
    }
    if (dd < 0 || dd >= 5) {
        t2 = 0;
    } else {
        t2 = &t1->e[dd];
    }
    if (t2 == 0) {
        return;
    }
    if (b < 0 || b >= t2->f18) {
        t3 = 0;
    } else {
        t3 = &t2->f1C[b];
    }
    if (t3 == 0) {
        return;
    }
    if (t3->f6 == 0) {
        return;
    }
    if (t3->f6 != 1) {
        return;
    }
    f7v = t3->f7;
    if (a == -1) {
        return;
    }
    if (m < 0 || m > 0x10) {
        u1 = 0;
    } else {
        u1 = &D_0049EB10[m];
    }
    if (u1 == 0) {
        ok = 0;
    } else {
        if (dd < 0 || dd >= 5) {
            u2 = 0;
        } else {
            u2 = &u1->e[dd];
        }
        if (u2 == 0) {
            ok = 0;
        } else {
            r = u1->f4;
            ok = 1;
        }
    }
    if (ok == 0) {
        return;
    }
    SoundSendCmd_1b6cc0(0x1E, 5, r, d, 0, f7v, c);
}
