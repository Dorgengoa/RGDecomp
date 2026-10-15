#include "types.h"
/* insect 0x00512B80 -- a 3-instruction leaf setter.  Both parameters are USED in
 * the body, so the arity needs no caller evidence: a store of $5 through $4
 * cannot be a pass-through. */
typedef struct Ent {
    s32 f00;
} Ent;

void insect_InsectMsgSetBank_512b80(Ent *p, s32 v)
{
    p->f00 = v;
}
