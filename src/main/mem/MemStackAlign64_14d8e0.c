#include "types.h"

/* Round the cursor at +0x2C up so that base + cursor*16 lands on a 0x40
   boundary, then clamp it to the limit at +0x34.

   The `bgez` / `addiu 0xF` / `sra 4` pair around the shift is the signed
   divide-by-16 idiom, not a shift: a plain `>> 4` emits one `sra`. And the
   limit is READ ONCE in the source -- retail's two `lw 0x34` are the likely
   branch duplicating the load into its own delay slot. */

typedef struct Obj0014d8e0 {
    u8 pad00[0x20];
    s32 unk20;
    u8 pad24[0x4];
    s32 base;          /* +0x28 */
    s32 cursor;        /* +0x2C */
    u8 pad30[0x4];
    s32 limit;         /* +0x34 */
} Obj0014d8e0;

void MemStackAlign64_14d8e0(Obj0014d8e0 *o)
{
    s32 over;

    if (o->unk20 != 0) {
        return;
    }
    over = (o->base + o->cursor * 16) & 0x3F;
    if (over != 0) {
        o->cursor = o->cursor + (0x40 - over) / 16;
    }
    if (o->cursor >= o->limit) {
        o->cursor = o->limit;
    }
}
