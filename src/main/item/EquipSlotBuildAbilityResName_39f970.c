#include "types.h"

typedef struct { u8 pad[4]; u8 *p; } A0;
extern s32 EquipSlotGetCharaId_3a06f0(void *);
extern s32 MainCharaIdToNumber_4016b0(s32);
extern void *memset(void *, s32, s32);
extern u8 D_00483760[16] __attribute__((section(".sdata")));
#define DD D_00483760
#pragma divbyzerocheck on
#pragma opt_propagation off

void *EquipSlotBuildAbilityResName_39f970(A0 *arg0) {
    s64 c0;
    s64 c1;
    s64 c2;
    s64 c3;
    s32 n;
    u8 *p;
    u8 *q;
    s32 k;
    void *ret;

    if (arg0->p == NULL) {
        return NULL;
    }
    memset(DD, 0, 0x10);
    c1 = 0;
    c2 = 0;
    c3 = 0;
    n = EquipSlotGetCharaId_3a06f0(arg0);
    c0 = 0x63;
    n = MainCharaIdToNumber_4016b0(n);
    if (n < 0) {
        c0 = 0;
        n = -1;
    }
    p = arg0->p;
    switch (p[2]) {
    case 0:
        switch (p[3]) {
        case 1: case 2: case 3: case 4: case 5:
            c1 = 0x61; c2 = 0x62; c3 = 0x69;
            break;
        default:
            c1 = 0; c2 = 0; c3 = 0;
            break;
        }
        break;
    }
    k = p[4];
    ret = NULL;
    if ((s8)c0 != 0 && n >= 0 && (s8)c1 != 0 && (s8)c2 != 0 && (s8)c3 != 0 && k >= 0) {
        DD[0] = c0;
        q = DD;
        q[1] = ((n / 100) % 10) + 0x30;
        q[2] = ((n / 10) % 10) + 0x30;
        q[3] = (n % 10) + 0x30;
        q[5] = c1;
        q[6] = c2;
        q[7] = c3;
        q[4] = 0x5F;
        q[8] = ((k / 10) % 10) + 0x30;
        ret = DD;
        q[0xA] = 0;
        q[9] = (k % 10) + 0x30;
    }
    return ret;
}
