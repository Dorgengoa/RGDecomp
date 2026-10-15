#include "types.h"

typedef struct E0049B100 {
    u8 unk0;
    u8 unk1;
    u8 pad2[0x7A];
} E0049B100;

extern s32 FileSlotRead_180aa0(s32, s32, s32);
extern E0049B100 D_0049B100[12];
extern E0049B100 D_0049B178[12];

static inline E0049B100 *get(s32 i)
{
    E0049B100 *e;

    if (i < 0 || i >= 12) {
        return NULL;
    }
    e = &D_0049B100[i];
    if (e->unk0 == 0) {
        return NULL;
    }
    if (D_0049B178[i].unk0 != 0) {
        return NULL;
    }
    return e;
}

s32 FileReadChunked_180400(s32 arg0, s32 arg1, s32 arg2)
{
    E0049B100 *e;
    s32 p;
    s32 rem;
    s32 total;
    s32 n;
    s32 r;

    e = get(arg0);
    if (e == NULL) {
        return -1;
    }
    if (e->unk1 == 2) {
        return FileSlotRead_180aa0(arg0, arg1, arg2);
    }
    p = arg1;
    rem = arg2;
    total = 0;
    while (rem > 0) {
        n = rem;
        if (n > 0x100000) {
            n = 0x100000;
        }
        r = FileSlotRead_180aa0(arg0, p, n);
        if (r < 0) {
            total = r;
            break;
        }
        rem -= r;
        p += r;
        total += r;
        if (rem <= 0) {
            break;
        }
        if (r == 0) {
            break;
        }
    }
    return total;
}
