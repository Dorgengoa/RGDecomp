/* rgp:protos */
#define RGP_SELF_MesWinPushNumVar0_275dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_00275dd0 {
    u8 pad000[0x1C18];
    s32 m1C18;         /* +0x1C18 */
} Obj4_FUN_00275dd0;

/*rgp*/

s32 MesWinPushNumVar0_275dd0(Obj4_FUN_00275dd0 *o, s32 a5, s32 a6, s32 a7, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    return (MesWinPushNumber_275de0(o, o->m1C18, 0), (s32)0);
}
