#include "types.h"
/* normal 0x004F4DC0 -- clear the three fixed rows' flags, then flag the
 * selected row of the live list.  Ids walk 10, 17, 24, ... (u16, so the
 * `+7` is followed by an `andi 0xFFFF`). */

typedef struct Ent { u8 pad00[0x2]; s16 f02; } Ent;

typedef struct Obj { u8 pad000[0x378]; s16 f378; } Obj;

extern void  func_1FEDE0(void);
extern Ent  *func_28FE10(Obj *a, u16 id, s32 k);
extern s32   normal_FieldHudPartyRowCount_4f9c50(Obj *a);

void normal_FieldHudPanelSelectRaise_4f4dc0(Obj *p, s32 sel)
{
    s32  j;
    u16  id;
    s32  i;
    s32  n;
    Ent *e;

    if (p->f378 == 0) {
        return;
    }
    id = 10;
    for (i = 0; i < 3; i++) {
        e = func_28FE10(p, id, 0);
        if (e == NULL) {
            return;
        }
        e->f02 = 0;
        id += 7;
    }
    func_1FEDE0();
    n = normal_FieldHudPartyRowCount_4f9c50(p);
    id = 10;
    for (j = 0; j < n; j++) {
        if (j == sel) {
            e = func_28FE10(p, id, 0);
            if (e == NULL) {
                return;
            }
            e->f02 = -10;
        }
        id += 7;
    }
}
