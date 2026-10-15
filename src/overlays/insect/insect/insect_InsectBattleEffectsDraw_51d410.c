#include "types.h"
/* insect 0x0051D410 -- 148 bytes, 37 instructions.  Same slot table as
 * insect_FUN_0051DBE0: the entries live at `a[i + 2]`.  The slot ADDRESS is
 * kept in a callee-saved register and the entry re-loaded after func_1418C0,
 * which is what writing `a[i + 2]` a second time gives.  1.0f is a `lui`
 * literal, not a pool load. */

typedef struct Res {
    u8  pad000[0x4DC];
    s32 f4DC;                       /* +0x4DC */
} Res;

typedef struct Ent {
    Res *f00;                       /* +0x00 */
} Ent;

extern void *func_15DE80(void);
extern void func_1418C0(void *h, s32 id, f32 v);
extern void insect_InsectBattleEffectNodeDraw_51e080(Ent *e);

void insect_InsectBattleEffectsDraw_51d410(Ent **a)
{
    void *h;
    Ent *e;
    s32 i;

    h = func_15DE80();
    for (i = 0; i < 15; i++) {
        e = a[i + 2];
        if (e != 0) {
            if (e->f00 != 0) {
                func_1418C0(h, e->f00->f4DC, 1.0f);
                insect_InsectBattleEffectNodeDraw_51e080(a[i + 2]);
            }
        }
    }
}
