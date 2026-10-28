/* rgp:protos */
#define RGP_SELF_factory_ModelAttachSlotCtor_504570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504570 -- set a two-word record to -1 and return it.
 *
 * ★ The HIGH word is stored first; 0x00504500 clears two of these pairs the
 * same way round.  Ascending order is 2 of 5 words wrong. */

typedef struct R2 {
    s32 f0;
    s32 f4;
} R2;

R2 *factory_ModelAttachSlotCtor_504570(R2 *o)
{
    o->f4 = -1;
    o->f0 = -1;
    return o;
}
