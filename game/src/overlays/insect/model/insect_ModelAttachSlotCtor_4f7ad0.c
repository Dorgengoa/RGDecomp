/* rgp:protos */
#define RGP_SELF_insect_ModelAttachSlotCtor_4f7ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F7AD0 -- 5-instruction leaf returning its own argument.  The
 * store to +0x00 sits in the `jr $31` delay slot. */
typedef struct PRec { s32 f00; s32 f04; } PRec;

PRec *insect_ModelAttachSlotCtor_4f7ad0(PRec *p)
{
    p->f04 = -1;
    p->f00 = -1;
    return p;
}
