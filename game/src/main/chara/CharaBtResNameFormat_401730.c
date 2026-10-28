/* rgp:protos */
#define RGP_SELF_CharaBtResNameFormat_401730 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
#pragma opt_propagation off

/*rgp*/
extern void *memset(void *, s32, s32);
extern u8 D_00483BB0[16] __attribute__((section(".sdata")));
#define DD D_00483BB0

void *CharaBtResNameFormat_401730(s16 *arg0)
{
    s64 c0;
    s32 id;
    s32 n;
    u8 *q;
    void *ret;
    s32 kind;

    memset(DD, 0, 0x10);
    id = *arg0;
    ret = NULL;
    kind = 2;
    if (id == 0x2AFC) {
        kind = 4;
    } else if (id == 0x2AFB) {
        kind = 1;
    } else if (id == 0x2B01) {
        kind = 1;
    }
    c0 = 0x63;
    n = MainCharaIdToNumber_4016b0(id);
    if (n < 0) {
        c0 = 0;
        n = -1;
    }
    if ((s8)c0 != 0 && id >= 0) {
        DD[0] = c0;
        q = DD;
        q[1] = ((n / 100) % 10) + 0x30;
        q[2] = ((n / 10) % 10) + 0x30;
        q[7] = kind + 0x30;
        q[8] = 0;
        q[4] = 0x5F;
        q[5] = 0x62;
        q[6] = 0x74;
        ret = DD;
        q[3] = (n % 10) + 0x30;
    }
    return ret;
}
