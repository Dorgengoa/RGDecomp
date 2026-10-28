/* rgp:protos */
#define RGP_SELF_ObjRecGetLiveObject_1c4a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Look a camera path/track record up by index -- the same slot protocol
   as ObjRecGetLiveObject_1c3bc0, against a different table.

   DRAFT -- capped locally by two likely branches. Structure is confirmed
   against the diff; the one unexplained detail is that retail materialises
   `!slot->live` into a register (`xor v1,v1,zero; sltiu v1,v1,1`) before
   branching on it, which a plain `if (!slot->live)` does not reproduce.
   Writing it as an explicit bool made the score worse, so it is left alone
   until b210 can adjudicate. */

typedef struct Slot {
    s32 live;      /* +0x00 */
    u8 pad04[0x20];
    void *object;  /* +0x24 */
} Slot;

/*rgp*/

void *ObjRecGetLiveObject_1c4a90(void *table, s32 id)
{
    Slot *slot = ((Slot *)ObjRecTableGet_1c3fe0(table, id));
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
