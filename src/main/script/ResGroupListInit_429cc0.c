#pragma opt_propagation off
#pragma opt_common_subs off
#include "types.h"

typedef struct T00429cc0 {
    s32 unk0;
    void *unk4;
    s16 unk8;
    u16 mode : 2;
    u16 count : 14;
} T00429cc0;

typedef struct P00429cc0 {
    u8 pad0[0x164];
    u16 flags;
    u8 pad166[2];
    u8 heap[4];
} P00429cc0;

extern void *ArenaNewChecked_42c9a0(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern void memset(void *arg0, s32 arg1, s32 arg2);

s32 ResGroupListInit_429cc0(T00429cc0 *o, P00429cc0 *p, s16 id, s32 n, T00429cc0 **out, s32 v)
{
    s32 m;
    s32 four;
    void *b;

    if (p != 0) {
        o->mode = p->flags;
    } else {
        o->mode = 3;
    }
    o->unk0 = v;
    o->unk8 = id;
    o->count = n;
    if (out != 0) {
        *out = o;
    }
    if (n <= 0) {
        o->unk4 = 0;
        return 0;
    }
    m = n + 1;
    four = 4;
    b = ArenaNewChecked_42c9a0(m << 6, p->heap, four, four);
    o->unk4 = b;
    if (b != 0) {
        memset(b, 0, m << 6);
        return 1;
    }
    o->count = 0;
    return 0;
}
