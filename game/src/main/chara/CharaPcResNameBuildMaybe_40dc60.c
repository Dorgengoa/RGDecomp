/* rgp:protos */
#define RGP_SELF_CharaPcResNameBuildMaybe_40dc60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
#pragma opt_propagation off

typedef struct {
    s16 m0;
    s8 m2;
    s8 m3;
    s16 m4;
    s16 m6;
    s16 m8;
} P;

/*rgp*/
extern void *memset(void *, s32, s32);
extern u8 D_00483D30[16] __attribute__((section(".sdata")));
#define DD D_00483D30

#define W2(a, b) c1 = a; c2 = b; break;

void *CharaPcResNameBuildMaybe_40dc60(P *p)
{
    s64 c0;
    s64 c1;
    s64 c2;
    s32 n;
    s32 k;
    s32 m;
    s32 t;
    s32 x;
    u8 *q;
    u8 *q2;
    void *ret;

    memset(DD, 0, 0x10);
    c1 = 0;
    c2 = 0;
    c0 = 0x63;
    n = MainCharaIdToNumber_4016b0(p->m8);
    if (n < 0) {
        c0 = 0;
        n = -1;
    }
    k = p->m8;
    if (k == 0x2B01) {
        if (p->m0 == 0x407F) {
            n = 1;
        }
    }
    if (k == 0x2B02) {
        n = 0x2B00;
    }
    t = p->m2;
    switch (t) {
    case 0:
        switch (p->m4) {
        case 100: W2(0x77, 0x73)
        case 107: W2(0x61, 0x78)
        case 103: W2(0x77, 0x67)
        case 101: W2(0x77, 0x73)
        case 102: W2(0x77, 0x68)
        case 105: W2(0x77, 0x62)
        case 106: W2(0x77, 0x73)
        case 104: W2(0x77, 0x73)
        default: W2(0, 0)
        }
        break;
    case 1:
        switch (p->m4) {
        case 200: W2(0x77, 0x67)
        case 207: W2(0x68, 0x62)
        case 203: W2(0x77, 0x63)
        case 201: W2(0x77, 0x6B)
        case 202: W2(0x77, 0x73)
        case 205: W2(0x77, 0x73)
        case 206: W2(0x77, 0x70)
        case 204: W2(0x77, 0x74)
        default: W2(0, 0)
        }
        break;
    }
    m = p->m3;
    x = p->m6;
    ret = 0;
    switch (t) {
    case 0:
    case 1:
        if ((s8)c0 != 0 && n >= 0 && (s8)c1 != 0 && (s8)c2 != 0 && m >= 0) {
            DD[0] = c0;
            q = DD;
            q[1] = ((n / 100) % 10) + 0x30;
            q[2] = ((n / 10) % 10) + 0x30;
            q[3] = (n % 10) + 0x30;
            q[4] = 0x5F;
            q[5] = c1;
            q[6] = c2;
            q[7] = ((m / 10) % 10) + 0x30;
            q[8] = (m % 10) + 0x30;
            q2 = q + 9;
            if (x >= 2 && x < 5) {
                *q2 = x + 0x5F;
                q2++;
            }
            *q2 = 0;
            ret = DD;
        }
        break;
    case 2:
        if ((s8)c0 != 0 && n >= 0 && m >= 0) {
            DD[0] = c0;
            q = DD;
            q[1] = ((n / 100) % 10) + 0x30;
            q[2] = ((n / 10) % 10) + 0x30;
            q[3] = (n % 10) + 0x30;
            q[4] = 0x5F;
            q[5] = 0x73;
            q[6] = 0x6B;
            q[7] = 0x69;
            q[8] = 0x6E;
            q[9] = ((m + 1) % 10) + 0x30;
            ret = DD;
            q[10] = 0;
        }
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}
