#include "types.h"

typedef struct Elem {
    s16 x0;
    s16 x2;
    u8 pad4[0x350 - 0x4];
} Elem;

typedef struct Hdr {
    s16 x0;
    s16 pad2;
    Elem *x4;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 padE;
    s16 x10;
    s16 x12;
} Hdr;

typedef struct Obj {
    u8 pad0[0x68];
    Hdr *x68;
} Obj;

Elem *SlotRecordFindById_3e4e80(Obj *arg0, s32 arg1)
{
    s32 i;
    Elem *arr;
    s32 end;
    Elem *p;
    Hdr *h;

    h = arg0->x68;
    if (h == 0) {
        return 0;
    }
    arr = h->x4;
    if (arr == 0) {
        return 0;
    }
    if (h->x8 <= 0) {
        return 0;
    }
    if (arg1 < h->x10) {
        return 0;
    }
    if (h->x12 < arg1) {
        return 0;
    }
    end = h->xC;
    i = h->xA;
    if (i <= end) {
        for (p = &arr[i]; i <= end; i++, p++) {
            if (p->x2 == arg1) {
                return p;
            }
        }
    } else {
        for (p = &arr[i]; i < h->x0; i++, p++) {
            if (p->x2 == arg1) {
                return p;
            }
        }
        for (i = 0; i <= end; i++, arr++) {
            if (arr->x2 == arg1) {
                return arr;
            }
        }
    }
    return 0;
}
