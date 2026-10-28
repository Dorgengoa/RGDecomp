/* rgp:protos */
#define RGP_SELF_ModelTagMeshesUnderFrame_1516d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_001516d0 {
    u8 pad000[0x104];
    s32 m104;         /* +0x104 */
} Obj4_FUN_001516d0;

/*rgp*/

s32 ModelTagMeshesUnderFrame_1516d0(Obj4_FUN_001516d0 *o, s32 a5, s32 a6, s32 a7)
{
    return ModelMeshTagUnderFrame_152700(a5, o->m104, a6, a7);
}
