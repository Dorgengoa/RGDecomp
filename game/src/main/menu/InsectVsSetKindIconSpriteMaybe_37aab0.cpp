#include "types.h"
#pragma opt_propagation off

typedef struct { s16 key; s16 a; s16 b; } Rec37A;
extern "C" s16 D_00453FB0[];

extern "C" void InsectVsSetKindIconSpriteMaybe_37aab0(void *arg0, s32 arg1) {
    Rec37A tbl[20] __attribute__((aligned(16)));
    s32 kv;
    s32 i;
    s32 key;
    s16 *s;
    s16 *d;
    s32 n;

    if (arg0 == NULL) {
        return;
    }
    s = (s16 *)D_00453FB0;
    d = (s16 *)tbl;
    n = 0x1E;
    do {
        d[0] = s[0];
        d[1] = s[1];
        s += 2;
        d += 2;
    } while (--n > 0);
    key = (s16)arg1 + 0x7D0;
    for (i = 0; tbl[i].key != -1; i++) {
        if (key == tbl[i].key) {
            kv = i;
            *(s16 *)((u8 *)arg0 + 8) = tbl[kv].a;
            *(s16 *)((u8 *)arg0 + 0xA) = tbl[kv].b;
            break;
        }
    }
    *(s16 *)((u8 *)arg0 + 0xE) = 0x32;
    *(s16 *)((u8 *)arg0 + 6) = 0x32;
    *(s16 *)((u8 *)arg0 + 0xC) = 0x32;
    *(s16 *)((u8 *)arg0 + 4) = 0x32;
}
