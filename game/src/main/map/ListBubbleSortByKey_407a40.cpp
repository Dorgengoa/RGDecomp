#include "types.h"

typedef struct {
    u8 pad0[0x1];
    u8 unk1;
    u8 pad2[0x2];
    u8 *unk4;
} Obj00407A40;

extern "C" void memcpy(void *, void *, s32);

static inline bool less(u8 *a, u8 *b)
{
    bool r = false;
    if (*a > *b) {
        r = true;
    }
    return r;
}

extern "C" void ListBubbleSortByKey_407a40(Obj00407A40 *arg0)
{
    s32 tmp;
    u8 *p;
    u8 *next;
    s32 i;
    bool swapped;

    if (!((s32)arg0->unk1 > 1) || arg0->unk4 == NULL) {
        return;
    }
    do {
        p = arg0->unk4;
        swapped = false;
        for (i = 1, next = p + 2; i < arg0->unk1; i++, next += 2) {
            if (less(p, next)) {
                memcpy(&tmp, p, 2);
                memcpy(p, next, 2);
                memcpy(next, &tmp, 2);
                swapped = true;
            }
            p = next;
        }
    } while (swapped);
}
