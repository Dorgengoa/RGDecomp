#include "types.h"

/* Known-positive sibling shape of ObjRecGetLiveObject_1c3bc0 (byte-identical, in cunits):
   look the slot up, reject a null slot and a dead slot, return the object. */

typedef struct Slot {
    s32 live;      /* +0x00 */
    u8 pad04[0x20];
    void *object;  /* +0x24 */
} Slot;

extern Slot *ObjRecTableGet_1c3b80(void *table, s32 id);

void *ObjRecGetLiveObject_1c3a00(void *table, s32 id)
{
    Slot *slot = ObjRecTableGet_1c3b80(table, id);
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
