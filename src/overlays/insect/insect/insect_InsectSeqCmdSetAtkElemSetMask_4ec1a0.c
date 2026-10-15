#include "types.h"
/* insect 0x004EC1A0 -- a 3-instruction leaf setter.  Both parameters are USED in
 * the body, so the arity needs no caller evidence: a store of $5 through $4
 * cannot be a pass-through. */
typedef struct Ent {
    u8 pad00[0xC];
    s32 f0C;
} Ent;

void insect_InsectSeqCmdSetAtkElemSetMask_4ec1a0(Ent *p, s32 v)
{
    p->f0C = v;
}
