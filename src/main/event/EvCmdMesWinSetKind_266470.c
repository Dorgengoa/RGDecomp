#include "types.h"

/* Member of the 7-member clone group (100 B each).  Look the object up, hand it to
   a worker, report whether it was there.

   The cursor is a POST-INCREMENT on an 8-byte element type: retail spells the
   two arguments `daddu $17, $4, $0` + `addiu $17, $17, 0x8` and spends the
   advance in the first `jal`'s delay slot.  `(u8 *)a + 8` at the use site, a
   named local advanced by a separate statement, and `&a->m8` are all ONE
   `addiu $4, $17, 8` and one word short -- only `p++` with sizeof 8 reaches
   it ([[levers.d/main-clone-group-census]], the R8 rule). */

typedef struct R8 {
    u8 b[8];
} R8;

extern void *ScriptGetInt_26a2a0(void *p);
extern void *MesMgrGetSlotWin_266af0(void *p);
extern void  MesWinSetKind_276c80(void *dst, void *src);

s32 EvCmdMesWinSetKind_266470(R8 *p)
{
    void *o;

    o = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(p++));
    if (o == 0) {
        return 0;
    }
    MesWinSetKind_276c80(o, ScriptGetInt_26a2a0(p));
    return 1;
}
