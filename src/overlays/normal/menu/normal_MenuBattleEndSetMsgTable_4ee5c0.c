#include "types.h"
/* normal 0x004EE5C0 -- stores its second argument into the object, then calls
 * normal_MenuBattleEndGetMsg_4ee5b0 twice and publishes each result to a gp global.  It is the
 * CALLER that proves normal_MenuBattleEndGetMsg_4ee5b0's arity: `$5` is marshalled with a real
 * instruction at both sites and `$2` is stored afterwards.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
typedef struct Obj {
    u8   pad000[0x118];
    void *f118;
} Obj;

extern void *normal_MenuBattleEndGetMsg_4ee5b0(Obj *p, s32 k);
extern void *D_004843E8;
extern void *D_004843EC;

void normal_MenuBattleEndSetMsgTable_4ee5c0(Obj *p, void *q)
{
    p->f118 = q;
    D_004843E8 = normal_MenuBattleEndGetMsg_4ee5b0(p, 0);
    D_004843EC = normal_MenuBattleEndGetMsg_4ee5b0(p, 1);
}
