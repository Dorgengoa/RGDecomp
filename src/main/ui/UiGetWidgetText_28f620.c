#include "types.h"

typedef struct Elem {
    u8 pad[0x10];
} Elem;

typedef struct Holder {
    u8   pad00[0x28];
    Elem *arr;
} Holder;

extern Holder *UiFindWidget_290460(void *a, s32 b);

Elem *UiGetWidgetText_28f620(void *a, s32 b, s32 idx)
{
    Holder *h;
    Elem *arr;

    h = UiFindWidget_290460(a, b);
    if (h == NULL) {
        return NULL;
    }
    arr = h->arr;
    if (arr != NULL) {
        return &arr[idx];
    }
    return NULL;
}
