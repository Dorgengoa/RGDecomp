#include "types.h"

typedef struct RangeEntry {
    s16 start;
    s16 end;
} RangeEntry;

extern void Abort_12de80(void);
extern void Fprintf_12f9a0(s32 arg0, void *arg1);
extern s32 InvHasItemInCategory_3c7f40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_00449858[0x400];
extern u8 D_00465EA0[0x400];
extern RangeEntry D_00480200[] __attribute__((section(".sdata")));

void UnlockMaskBuildFromInv_3e4020(void *arg0, s64 *arg1)
{
    s32 bit;
    RangeEntry *e;
    s32 id;
    s32 k;
    volatile s32 sp6C;
    s64 *volatile sp68;

    bit = 0;
    *arg1 = 0;
    if (arg0 != NULL) {
        for (e = D_00480200; (k = e->start) >= 0; e++) {
            for (id = k; id <= e->end; id++) {
                if (InvHasItemInCategory_3c7f40(*(s32 *)((u8 *)arg0 + 0x18), id, 10, 0) != 0) {
                    sp68 = arg1;
                    sp6C = bit;
                    if ((u32)bit >= 64) {
                        Fprintf_12f9a0(*(s32 *)(*(u8 **)D_00449858 + 0xC), D_00465EA0);
                        Abort_12de80();
                    }
                    *sp68 |= (s64)1 << bit;
                }
                bit++;
            }
        }
    }
}
