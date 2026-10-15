#include "types.h"

typedef struct Obj {
    u8 pad0[0x168];
    u8 sub[0x17A - 0x168];
    u16 cnt;
    u8 pad2[0x198 - (0x17A + 2)];
    s32 head;
    s32 tail;
} Obj;

extern s32 ArenaNewChecked_42c9e0(s32, s32, s32, s32);
extern s32 ResGroupListInitDefault_429f60(s32);
extern s32 ResGroupListInit_429e30(s32, s32, s32, s32, s32, s32);

s32 ResGroupListAppendNew_42c1a0(Obj *self, s32 a1, s32 a2)
{
    s32 n;
    s32 p8;
    s32 p9;
    s32 t;

    n = ArenaNewChecked_42c9e0(0xC, (s32)&self->sub, 0x4, 0x4);
    if (n != 0) {
        ResGroupListInitDefault_429f60(n);
    }
    if (n == 0) {
        return 0;
    }
    p9 = p8 = 0;
    if (self->head == 0 || (t = self->tail) == 0) {
        self->head = n;
        self->tail = n;
        self->cnt = 1;
    } else {
        p8 = t;
        self->tail = n;
        self->cnt = self->cnt + 1;
    }
    ResGroupListInit_429e30(n, (s32)self, a1, a2, p8, p9);
    return n;
}
