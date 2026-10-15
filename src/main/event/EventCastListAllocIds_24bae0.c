#include "types.h"

/* Count the list at +0x0, record the length at +0x328, and allocate a
   four-byte slot per entry at +0x320 with the cursor at +0x324 reset.
   EventCastIdListContains_24c1f0 is the reader of that array and EventCastLoadPollAll_24d2a0 walks it.

   The allocation result is stored AFTER the count, and the shift that scales
   it sits in the call's delay slot -- so "count * 4" is the argument
   expression, not a local computed earlier.

   THE HEAP ARGUMENT IS A PASS-THROUGH and was invisible until MemStackNew_14e1b0
   was written: nothing here touches $5, so an earlier version of this file
   declared one parameter and matched byte-for-byte. MemStackNew_14e1b0 reads $5 as
   its heap, so this function must be taking one and forwarding it. Second
   instance of the same trap in one session -- see ParamTableSetAlpha_1cfb10. */

typedef struct Node0024bae0 {
    struct Node0024bae0 *next;
} Node0024bae0;

typedef struct Obj0024bae0 {
    Node0024bae0 *head;    /* +0x000 */
    u8 pad004[0x320 - 0x4];
    s32 *list;             /* +0x320 */
    s32 cursor;            /* +0x324 */
    s32 count;             /* +0x328 */
} Obj0024bae0;

extern s32 *MemStackNew_14e1b0(s32 bytes, void *heap);

void EventCastListAllocIds_24bae0(Obj0024bae0 *self, void *heap)
{
    Node0024bae0 *n;
    s32 count;

    n = self->head;
    if (n == 0) {
        count = 0;
    } else {
        n = n->next;
        count = 1;
        while (n != 0) {
            n = n->next;
            count++;
        }
    }
    self->count = count;
    self->list = MemStackNew_14e1b0(count * 4, heap);
    self->cursor = 0;
}
