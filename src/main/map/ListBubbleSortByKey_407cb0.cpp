#include "types.h"

extern "C" {
void DataTableRowReset_407b30(u8 *);
void *memcpy(void *, const void *, u32);
}

struct T407cb0 {
    u8 pad0[2];
    u8 n;
    u8 pad3[5];
    u8 *list;
};

extern "C" void ListBubbleSortByKey_407cb0(T407cb0 *arg0)
{
    u8 tmp[8];
    u8 *a;
    u8 *b;
    s32 i;
    bool swapped;
    bool gt;

if (arg0->n <= 1 || arg0->list == NULL) {
return;
}
do {
        a = arg0->list;
        swapped = false;
        for (i = 1, b = a + 8; i < arg0->n; i++, b += 8) {
            gt = false;
            if (*a > *b) {
                gt = true;
            }
            if (gt) {
                DataTableRowReset_407b30(tmp);
                memcpy(tmp, a, 8);
                memcpy(a, b, 8);
                memcpy(b, tmp, 8);
                swapped = true;
            }
            a = b;
        }
} while (swapped);
}
