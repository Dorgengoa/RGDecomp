#include "types.h"
#pragma opt_repositioncode on
#pragma opt_repositioncode off

/* m2c could not decompile this one directly ("jr instruction ... jump table
   not provided") -- jtbl_00466300 targets have no labels at all in the
   retail listing (nothing else branches to them), so a synthetic .rodata
   block AND inserted .L<addr>: case labels were both required before m2c
   would produce a draft. See build/s17/reports/e.md for the lever. */

extern void *PoolGetUsedElem_36acb0(s32, s32);

extern u8 D_00465A08[0x400];
extern u8 D_00465A10[0x400];
extern u8 D_00465A38[0x400];
extern u8 D_00465A40[0x400];
extern u8 D_00465A60[0x400];
extern u8 D_00465A68[0x400];
extern u8 D_00465A78[0x400];
extern u8 D_00465A80[0x400];
extern u8 D_00465A90[0x400];
extern u8 D_00465A98[0x400];
extern u8 D_00465AA8[0x400];
extern u8 D_00465AB0[0x400];
extern u8 D_00465AD0[0x400];
extern u8 D_00465AD8[0x400];
extern u8 D_00465AE8[0x400];
extern u8 D_00465AF0[0x400];
extern u8 D_00465B00[0x400];
extern u8 D_00465B08[0x400];
extern u8 D_00465B30[0x400];
extern u8 D_00465B38[0x400];
extern u8 D_00465B40[0x400];
extern u8 D_00465B48[0x400];
extern u8 D_00465B50[0x400];

typedef struct {
    u8 b0:1;
    u8 bit:1;
    u8 pad:6;
} Flags;

typedef struct { u8 pad[0x168]; s32 h168; } Obj8370;

void *InvFindInCategoryRange_3c8370(Obj8370 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 lo;
    s32 hi;
    s32 lo0;
    s32 hi0;
    u8 *res;
    s32 i;
    s32 count;
    u8 *p;

    if (arg1 < 0) {
        return NULL;
    }
    if (arg0->h168 == 0) {
        return NULL;
    }
    switch (arg2) {
    case 0:
        lo = *(s32 *)D_00465A08;
        hi = *(s32 *)D_00465A10;
        break;
    case 1:
        lo = *(s32 *)D_00465A38;
        hi = *(s32 *)D_00465A40;
        break;
    case 10:
        lo = *(s32 *)D_00465B40;
        hi = *(s32 *)D_00465B48;
        break;
    case 2:
        lo = *(s32 *)D_00465A60;
        hi = *(s32 *)D_00465A68;
        break;
    case 3:
        lo = *(s32 *)D_00465A78;
        hi = *(s32 *)D_00465A80;
        break;
    case 4:
        lo = *(s32 *)D_00465A90;
        hi = *(s32 *)D_00465A98;
        break;
    case 5:
        lo = *(s32 *)D_00465AA8;
        hi = *(s32 *)D_00465AB0;
        break;
    case 6:
        lo = *(s32 *)D_00465AD0;
        hi = *(s32 *)D_00465AD8;
        break;
    case 7:
        lo = *(s32 *)D_00465AE8;
        hi = *(s32 *)D_00465AF0;
        break;
    case 8:
        lo = *(s32 *)D_00465B00;
        hi = *(s32 *)D_00465B08;
        break;
    case 9:
        lo = *(s32 *)D_00465B30;
        hi = *(s32 *)D_00465B38;
        break;
    case -1:
    default:
        lo = 0;
        hi = *(s32 *)D_00465AD8;
        break;
    }
    if (lo < 0 || hi < 0) {
        return NULL;
    }
    if (arg4 == 0) {
        if (arg3 < 0) {
            lo0 = lo;
        } else {
            lo0 = arg3;
        }
        hi0 = hi;
    } else {
        if (arg3 < 0) {
            lo0 = hi;
        } else {
            lo0 = arg3;
        }
        hi0 = lo;
    }
    res = NULL;
    count = *(s32 *)D_00465B50;
    for (i = 0; i < count; i++) {
        p = PoolGetUsedElem_36acb0(arg0->h168, i);
        if (p == NULL) {
            continue;
        }
        if (*(s16 *)(p + 6) < lo0) {
            continue;
        }
        if (*(s16 *)(p + 6) > hi0) {
            continue;
        }
        if (arg5 == 0 && ((Flags *)(p + 0xA))->bit) {
            continue;
        }
        if (**(s16 **)(p + 0x10) != arg1) {
            continue;
        }
        res = p;
        break;
    }
    return res;
}
