/* rgp:protos */
#define RGP_SELF_SysModeIsInsMenu_1c3550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004A3EF0[];

/*rgp*/

s32 SysModeIsInsMenu_1c3550(void)
{
    return ((unsigned char)SysModeMsgIsInsMenu_1c6970(D_004A3EF0));
}
