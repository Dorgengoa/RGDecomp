/* rgp:protos */
#define RGP_SELF_TextStyleClearClipRect_26f600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0026f600 {
    u8 pad000[0x20];
    s16 m20;         /* +0x20 */
    u8 pad022[0x2];
    s32 m24;         /* +0x24 */
    s32 m28;         /* +0x28 */
    s32 m2C;         /* +0x2C */
    s32 m30;         /* +0x30 */
} Obj_FUN_0026f600;

void TextStyleClearClipRect_26f600(Obj_FUN_0026f600 *o)
{
    o->m20 = 0;
    o->m24 = 0;
    o->m28 = 0;
    o->m2C = 0;
    o->m30 = 0;
}
