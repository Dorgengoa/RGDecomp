#include "types.h"

extern void Abort_12de80(void);
extern void Fprintf_12f9a0(s32, void *);
extern void InvAddItemCoreMaybe_3c6540(s32, s32, s32, s32, s32, s32, s32);
extern void *D_00449858 __attribute__((section(".data")));
extern s16 D_00454760[0x80];
extern u8 D_00465ED0[];
extern s16 D_00480200[] __attribute__((section(".sdata")));

typedef struct {
    u64 *volatile p;
    volatile u32 n;
} BitRef;

void UnlockMaskGrantItems_3e3ef0(u8 *arg0, u64 mask)
{
    u32 bit;
    s16 *p;
    s32 id;
    s32 found;
    s32 k;
    s32 id2;
    BitRef r;

    if (arg0 == NULL) {
        return;
    }
    bit = 0;
    for (p = D_00480200; (id = p[0]) >= 0; p += 2) {
        for (id2 = id; id2 <= p[1]; id2++) {
            found = 0;
            for (k = 0; D_00454760[k] >= 0; k++) {
                if (id2 == D_00454760[k]) {
                    found = 1;
                    break;
                }
            }
            r.p = &mask;
            r.n = bit;
            if (bit >= 0x40) {
                Fprintf_12f9a0(*(s32 *)((u8 *)D_00449858 + 0xC), D_00465ED0);
                Abort_12de80();
            }
            if (*r.p & ((u64)1 << bit)) {
                if (!found) {
                    InvAddItemCoreMaybe_3c6540(*(s32 *)(arg0 + 0x18), id2, 10, 1, -1, 0, 0);
                }
            }
            bit++;
        }
    }
}
