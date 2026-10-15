#include "types.h"
/* insect 0x00522E20 -- a 3-instruction leaf setter.  Both parameters are USED in
 * the body, so the arity needs no caller evidence: a store of $5 through $4
 * cannot be a pass-through. */
typedef struct Ent {
    u8 pad00[0x8];
    s32 f08;
} Ent;

void insect_InsectAiCfgSetHeap_522e20(Ent *p, s32 v)
{
    p->f08 = v;
}
