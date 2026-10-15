#include "types.h"

/* Hand every id in the array EventCastListAllocIds_24bae0 built to EventCastLoadPoll_24c230. The base
   pointer is reloaded in the loop back-edge's delay slot on every pass and
   the count is re-read at the top, which is what an ordinary indexed loop
   over two fields of the receiver compiles to. */

typedef struct Obj0024d2a0 {
    u8 pad000[0x320];
    s32 *list;             /* +0x320 */
    s32 count;             /* +0x324 */
} Obj0024d2a0;

extern void EventCastLoadPoll_24c230(Obj0024d2a0 *self, void *arg, s32 id);

void EventCastLoadPollAll_24d2a0(Obj0024d2a0 *self, void *arg)
{
    s32 i;

    for (i = 0; i < self->count; i++) {
        EventCastLoadPoll_24c230(self, arg, self->list[i]);
    }
}
