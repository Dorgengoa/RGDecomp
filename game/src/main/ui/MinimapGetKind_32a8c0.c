/* rgp:protos */
#define RGP_SELF_MinimapGetKind_32a8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MinimapGetKind_32a8c0(void *p4)
{
    return ((short)EntryListGetKind_323690((u8 *)p4 + 0x12C));
}
