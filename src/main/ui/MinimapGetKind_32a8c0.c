#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 EntryListGetKind_323690(void *);

s32 MinimapGetKind_32a8c0(void *p4)
{
    return EntryListGetKind_323690((u8 *)p4 + 0x12C);
}
