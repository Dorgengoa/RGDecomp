#include "types.h"
/* insect 0x004F45B0 -- 14 instructions.  Two nested guards; the 1.0f arrives as
 * `lui 0x3F80` + `mtc1`, i.e. an immediate float constant and not a pool load. */

typedef struct Obj {
    u8    pad000[0x870];
    void *m870;                     /* +0x0870 */
} Obj;

extern void func_1D05F0(void *h, f32 v);

void insect_InsectBattlePlaySe_4f45b0(Obj *o, s32 id)
{
    void *h;

    if (id != -1) {
        h = o->m870;
        if (h != 0) {
            func_1D05F0(h, 1.0f);
        }
    }
}
