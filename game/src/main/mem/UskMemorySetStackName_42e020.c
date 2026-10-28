/* rgp:protos */
#define RGP_SELF_UskMemorySetStackName_42e020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 UskMemorySetStackName_42e020(void *p4, int rgp_a1)
{
    return UskStackSetName_42e3b0((u8 *)p4 + 0x14, (int)rgp_a1);
}
