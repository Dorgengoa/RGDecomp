#include "types.h"

typedef struct { u8 b0:1; u8 b1:1; u8 b2:1; u8 b3:1; u8 b4:1; u8 b5:1; u8 b6:1; u8 b7:1; } Bits;
typedef struct { s16 a; s16 b; } Ent;
typedef struct {
    s16 count;
    Ent ent[16];
    u8 pad42[2];
    Bits f44;
} Obj;

extern void *D_004837BC;

s32 CharaEventLogKeysClear_3a66e0(Obj *arg0) {
    Ent *p;
    s32 i;

    if (*(s16 *)((u8 *)(*(void **)((u8 *)D_004837BC + 0xC)) + 0x2C) == 1) goto L1;
    return 0;
L1:
    if (arg0->count > 0) goto L2;
    return 0;
L2:
    p = arg0->ent;
    i = 0;
    while (i < arg0->count) {
        p->a = -1;
        i++;
        p++;
    }
    arg0->count = 0;
    arg0->f44.b0 = 1;
    return 1;
}
