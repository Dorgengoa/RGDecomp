#include "types.h"
/* normal 0x004F6ED0 -- one guarded three-store block.  `$3` carries the 2 into
 * both of its stores, which is mwcc sharing a constant it already
 * materialised, not two source constants.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
typedef struct Obj {
    u8  pad000[0x2B0];
    s16 f2B0;
    s16 f2B2;
    u8  pad2B4[0x378 - 0x2B4];
    s16 f378;
} Obj;

void normal_FieldHudPanelsFadeOut_4f6ed0(Obj *p)
{
    if (p->f378 != 0) {
        p->f2B0 = 2;
        p->f2B2 = 0;
        p->f378 = 2;
    }
}
