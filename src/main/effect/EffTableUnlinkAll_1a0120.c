#include "types.h"

/* Intrusive-list walk.  RbTreeIncrement_1a2210 takes the ADDRESS of the cursor, which
   makes the whole enclosing aggregate memory-resident: that is why the end
   marker is re-loaded at every loop test and why the node id gets a dead home
   store at sp+0x24.  The aggregate is 16 bytes and sits at the TOP of the
   local area (sp+0x20..0x2F), so it carries a leading word before `v`.
   The head is read into a temporary FIRST (retail's `lw $4,0xE0($4)` precedes
   the `addiu $3,$16,0xD8`) but the end marker is STORED first. */

extern void EffDefUnlinkByHandle_1a0040(void *, s32);
extern void RbTreeIncrement_1a2210(void *);

struct W {
    s32 pad;
    s32 v;
    u8 *end;
    u8 *it;
};

void EffTableUnlinkAll_1a0120(u8 *o)
{
    struct W w;
    u8 *head;

    head = *(u8 **)(o + 0xE0);
    w.end = o + 0xD8;
    w.it = head;
    while (w.it != w.end) {
        w.v = *(s32 *)(w.it + 0x18);
        EffDefUnlinkByHandle_1a0040(o, w.v);
        RbTreeIncrement_1a2210(&w.it);
    }
}
