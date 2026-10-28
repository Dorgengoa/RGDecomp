/* rgp:protos */
#define RGP_SELF_ObjRecGetLiveObject_1c5250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of ObjRecGetLiveObject_1c3bc0 (byte-identical, in cunits):
   look the slot up, reject a null slot and a dead slot, return the object. */

typedef struct Slot {
    s32 live;      /* +0x00 */
    u8 pad04[0x20];
    void *object;  /* +0x24 */
} Slot;

/*rgp*/

void *ObjRecGetLiveObject_1c5250(void *table, s32 id)
{
    Slot *slot = ((Slot *)ObjRecTableGet_1c3fa0(table, id));
    u8 empty;

    if (slot == NULL) {
        return NULL;
    }
    empty = slot->live == 0;
    if (empty) {
        return NULL;
    }
    return slot->object;
}
