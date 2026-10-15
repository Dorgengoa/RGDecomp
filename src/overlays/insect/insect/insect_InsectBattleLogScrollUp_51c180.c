#include "types.h"
/* insect 0x0051C180 -- 34 instructions.  A 0x4F-entry walk over 0x5A-byte
 * records, stopped early by a zero at +0x54.  0x4F * 0x5A == 0x1BC6, so the
 * `addiu $4,$2,0x1BC6` after the loop is `&base[0x4F]` off a RE-LOADED base --
 * the loop's own cursor is dead there. */

typedef struct Elem {
    u8 pad00[0x54];
    s8 m54;                         /* +0x54 */
    u8 pad55[0x5A - 0x55];
} Elem;                             /* 0x5A */

typedef struct Obj {
    u8    pad00[0x4];
    Elem *m04;                      /* +0x04 */
} Obj;

extern void insect_InsectBattleLogLineCopy_51c670(Elem *p, Elem *q);
extern void insect_InsectBattleLogLineClear_51c810(Elem *p);

void insect_InsectBattleLogScrollUp_51c180(Obj *o)
{
    Elem *p;
    Elem *q;
    s32   i;

    p = o->m04;
    i = 0;
    while (i < 0x4F) {
        if (p->m54 == 0) {
            break;
        }
        q = p + 1;
        if (((s8 *)p)[0xAE] != 0) {
            insect_InsectBattleLogLineCopy_51c670(p, q);
        } else {
            insect_InsectBattleLogLineClear_51c810(p);
        }
        i++;
        p++;
    }
    insect_InsectBattleLogLineClear_51c810(&o->m04[0x4F]);
}
