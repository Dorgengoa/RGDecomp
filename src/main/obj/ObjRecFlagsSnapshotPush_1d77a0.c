#include "types.h"

s32 ObjRecHasFlags6_1c3eb0(s32, s32, s32);

typedef struct { u8 n; u8 bits[7][0x1C]; } T1d77a0;

void ObjRecFlagsSnapshotPush_1d77a0(T1d77a0 *arg0, s32 arg1) {
    s32 i;
    u8 n;

    n = arg0->n;
    if (n < 7) {
        for (i = 0; i < 0x1C; i++) {
            arg0->bits[n][i] = 0;
        }
        for (i = 0; i < 0xE0; i++) {
            if (ObjRecHasFlags6_1c3eb0(arg1, 1, i) != 0) {
                arg0->bits[arg0->n][i / 8] |= 1 << (i % 8);
            }
        }
        arg0->n++;
    }
}
