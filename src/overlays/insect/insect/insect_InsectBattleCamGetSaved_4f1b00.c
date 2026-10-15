#include "types.h"
/* insect 0x004F1B00 -- 72 bytes, 18 instructions.  Copy two optional
 * 3-vectors out of the object. */

typedef struct Vec { f32 x, y, z; } Vec;

typedef struct Obj {
    u8  pad00[0x60];
    f32 f60, f64, f68;              /* +0x60 */
    u8  pad6C[0x70 - 0x6C];
    f32 f70, f74, f78;              /* +0x70 */
} Obj;

void insect_InsectBattleCamGetSaved_4f1b00(Obj *o, Vec *a, Vec *b)
{
    if (a != 0) {
        a->x = o->f60;
        a->y = o->f64;
        a->z = o->f68;
    }
    if (b != 0) {
        b->x = o->f70;
        b->y = o->f74;
        b->z = o->f78;
    }
}
