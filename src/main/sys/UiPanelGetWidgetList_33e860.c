#include "types.h"

/* Address of the sub-object at +0x1C. */

typedef struct Obj_FUN_0033e860 {
    u8 pad000[0x1C];
    u8 sub[1];         /* +0x1C */
} Obj_FUN_0033e860;

void *UiPanelGetWidgetList_33e860(Obj_FUN_0033e860 *o)
{
    return o->sub;
}
