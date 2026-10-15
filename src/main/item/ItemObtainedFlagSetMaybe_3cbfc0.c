#include "types.h"

extern void Abort_12de80(void);
extern void Fprintf_12f9a0(s32 arg0, void *arg1);
extern void BitsetAssignBit_3cde00(s32 arg0, u32 arg1, s32 arg2);
extern void *D_00449858[];
extern u8 D_004663E0[];

typedef struct { s32 p; u32 i; } P;

s32 ItemObtainedFlagSetMaybe_3cbfc0(s32 arg0, s32 arg1, s32 arg2) {
    volatile P s;
    u32 temp_17;

    if (arg1 >= 0x3E80 && arg1 < 0x432F) goto body;
    return 0;
body:
    s.p = arg0 + 0x360;
    temp_17 = arg1 - 0x3E80;
    s.i = temp_17;
    if (temp_17 >= 0x500U) {
        Fprintf_12f9a0(*(s32 *)((u8 *)D_00449858[0] + 0xC), D_004663E0);
        Abort_12de80();
    }
    BitsetAssignBit_3cde00(s.p, temp_17, arg2);
    return 1;
}
