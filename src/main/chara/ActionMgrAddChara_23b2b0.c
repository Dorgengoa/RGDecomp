#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern void CharaCtor_215390(void *, s32, s32);
extern s32 ActionMgrFindOrAddChara_2341b0(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 ActionMgrAddChara_23b2b0(s32 p0, s32 p1)
{
    u128 v40[183];
    s32 r0;
    s32 r2;

    r0 = GetActionMgr_1fdb50();
    CharaCtor_215390(v40, p0, p1);
    r2 = ActionMgrFindOrAddChara_2341b0(r0, v40);
    return (r2 != 0);
}
