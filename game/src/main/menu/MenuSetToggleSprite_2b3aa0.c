/* rgp:protos */
#define RGP_SELF_MenuSetToggleSprite_2b3aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_002b3aa0 {
    u8 pad000[0x10];
    s8 m10;         /* +0x10 */
} Obj4_FUN_002b3aa0;

/*rgp*/

s32 MenuSetToggleSprite_2b3aa0(Obj4_FUN_002b3aa0 *o, s32 a5, s32 a6)
{
    return ((s32)MenuToggleSpriteApply_2b3ab0((long long)(o->m10), a5, a6));
}
