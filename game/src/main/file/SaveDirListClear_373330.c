/* rgp:protos */
#define RGP_SELF_SaveDirListClear_373330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj4_FUN_00373330 {
    u8 pad000[0x500];
    s32 m500;         /* +0x500 */
} Obj4_FUN_00373330;

/*rgp*/

s32 SaveDirListClear_373330(Obj4_FUN_00373330 *o)
{
    return (SaveDirEntriesClear_376020(o->m500, 0x32), (s32)0);
}
