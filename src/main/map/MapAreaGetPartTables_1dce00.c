#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableGetPartTables_1dd580(void *);

s32 MapAreaGetPartTables_1dce00(void *p4)
{
    return MapRecTableGetPartTables_1dd580((u8 *)p4 + 0x54);
}
