#include "types.h"
/* insect 0x00522C90 -- 11 instructions.  A one-call forwarder that returns its
 * own argument; `addiu $4,$16,0xC4` is a member address. */

typedef struct Obj {
    u8 pad000[0xC4];
    u8 mC4[4];                      /* +0x00C4 */
} Obj;

extern void insect_InsectAiActionListCtor_5233e0(u8 *p);

Obj *insect_InsectAiCtor_522c90(Obj *o)
{
    insect_InsectAiActionListCtor_5233e0(o->mC4);
    return o;
}
