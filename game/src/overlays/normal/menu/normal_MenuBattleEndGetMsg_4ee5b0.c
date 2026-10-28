/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndGetMsg_4ee5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EE5B0 -- `j func_28AA30 / lw $4, 0x118($4)`.  A tail call whose
 * single argument is a member of its own parameter, loaded in the delay slot.
 * mwcc -O4 emits `j` for this from plain source.  One of the 55 unnamed
 * functions; see scripts/n_unnamed.py.
 *
 * ⚠ `$5` and the return value are PASS-THROUGHS and leave no trace here -- the
 * arity was read off the CALLER, normal_MenuBattleEndSetMsgTable_4ee5c0, which marshals `$5` with a
 * real instruction at both of its call sites and stores `$2` afterwards.
 * Seventh instance of the pass-through-argument trap. */
typedef struct Obj {
    u8   pad000[0x118];
    void *f118;
} Obj;

/*rgp*/

void *normal_MenuBattleEndGetMsg_4ee5b0(Obj *p, s32 k)
{
    return MsgTableLookup_28aa30(p->f118, k);
}
