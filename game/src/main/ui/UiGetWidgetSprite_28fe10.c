/* rgp:protos */
#define RGP_SELF_UiGetWidgetSprite_28fe10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem {
    u8 pad[0x20];
} Elem;

typedef struct Holder {
    u8   pad00[0x20];
    Elem *arr;
} Holder;

/*rgp*/

Elem *UiGetWidgetSprite_28fe10(void *a, s32 b, s32 idx)
{
    Holder *h;
    Elem *arr;

    h = ((Holder *)UiFindWidget_290460(a, b));
    if (h == NULL) {
        return NULL;
    }
    arr = h->arr;
    if (arr != NULL) {
        return &arr[idx];
    }
    return NULL;
}
