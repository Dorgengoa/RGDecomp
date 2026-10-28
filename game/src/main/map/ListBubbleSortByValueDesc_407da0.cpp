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
    if (*(s16 *)(a+4) > *(s16 *)(b+4)) {
        r = true;
    }
    if (*(s16 *)(a+4)==*(s16 *)(b+4) && (((u64)(s64)a[3]<<59)>>63) && !(((u64)(s64)b[3]<<59)>>63)) r=true;
    return r;
}

extern "C" void ListBubbleSortByValueDesc_407da0(Obj00407A40 *arg0)
{
    u8 tmp[6];
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
        for (i = 1, next = p + 6; i < arg0->unk1; i++, next += 6) {
            if (less(p, next)) {
                memcpy(&tmp, p, 6);
                memcpy(p, next, 6);
                memcpy(next, &tmp, 6);
                swapped = true;
            }
            p = next;
        }
    } while (swapped);
}
