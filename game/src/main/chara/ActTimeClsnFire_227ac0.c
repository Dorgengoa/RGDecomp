/* rgp:protos */
#define RGP_SELF_ActTimeClsnFire_227ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_00227ac0 {
    f32 m00;         /* +0x0 */
} Obj4_FUN_00227ac0;

/*rgp*/

s32 ActTimeClsnFire_227ac0(Obj4_FUN_00227ac0 *o, s32 a5, s32 a6, s32 a7)
{
    return CharaSpawnClsnJudge_227c70((u8 *)o + 4, a5, a6, a7, o->m00);
}
