#include "types.h"

typedef struct { s16 id; s16 val; } E3c3280;
extern E3c3280 *BestiaryCountBumpMaybe_3c3300(void *, s32);
extern s32 D_00465B70[4];

static inline E3c3280 *find(void *arg0, s32 arg1) {
    E3c3280 *p = *(E3c3280 **)((u8 *)arg0 + 0x17C);
    s32 n;
    s32 i;
    if (p == 0) return 0;
    n = D_00465B70[0];
    for (i = 0; i < n; i++, p++) {
        if (p->id == arg1) return p;
    }
    return 0;
}

E3c3280 *BestiaryCountSetMaybe_3c3280(void *arg0, s32 arg1, s32 arg2) {
    E3c3280 *e = find(arg0, arg1);
    if (e == 0) e = BestiaryCountBumpMaybe_3c3300(arg0, arg1);
    if (e != 0) e->val = arg2;
    return e;
}
