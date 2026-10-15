#include "types.h"
/* insect 0x00512EC0 -- 32 bytes, 8 instructions, 1 conditional branch.
 *
 * Retail reads 0x1E back ONCE into $3 and stores it twice, so the reload is a
 * NAMED LOCAL in the source ([[insect-load-across-store]]); written as two
 * `o->f1C = o->f1E;` statements mwcc would have to re-load across the store.
 */

typedef struct Obj {
    u8  pad00[0x1A];
    s16 f1A;                        /* +0x1A */
    s16 f1C;                        /* +0x1C */
    s16 f1E;                        /* +0x1E */
    s16 f20;                        /* +0x20 */
} Obj;

void insect_InsectPieceSetMaxHp_512ec0(Obj *o, s16 v, s32 f)
{
    s16 t;

    o->f20 = v;
    o->f1E = v;
    if (f != 0) {
        t = o->f1E;
        o->f1C = t;
        o->f1A = t;
    }
}
