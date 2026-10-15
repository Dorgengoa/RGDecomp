#pragma optimization_level 3

#include "types.h"

/* factory.bin overlay, 0x005005D0 -- 96 bytes / 24 words, 2 branches, 1 call.
 *
 * ** TWIN of `factory_FactoryBeltCommitPreview_500400` (72 B): the same guard, the same walk and
 *    the same pragma -- read that file's note for the measurement.  The only
 *    difference is the tail: this one `return 1;`s after
 *    `factory_FactoryBeltRebuildTiles_500b00(o)`, which blocks the tail jump and forces the 0x10
 *    frame plus the `sd $31`; 00500400 has no frame at all.  Confirming the
 *    twin cost nothing: the same pragma took both from 5 bad words to zero.
 *
 * ** `#pragma optimization_level 3`: at -O4 the loop body is a pure $2/$3
 *    rename (base in $2 / 12*i product in $3, retail the other way round) and
 *    eleven of fourteen source spellings gave the byte-identical wrong object.
 *
 * * `jal factory_FactoryBeltRebuildTiles_500b00` carries a bare `nop` in its delay slot because
 *   `$4` still holds the parameter -- the argument needs no move.
 * * Part list at `0x2AC` / count `0x2B0` / 0xC stride, the fy04 family shape.
 */

typedef struct Part {
    u8  pad00[0x6];
    s16 f06;
    s16 f08;
    u8  pad0A[0x2];
} Part;                                         /* 0xC */

typedef struct Obj {
    u8    pad000[0x2AC];
    Part *parts;
    s16   nparts;
} Obj;

extern void factory_FactoryBeltRebuildTiles_500b00(Obj *o);

s32 factory_FactoryBeltCommitPreview_5005d0(Obj *o)
{
    s32 i;

    if (o->parts != 0) {
        for (i = 0; i < o->nparts; i++) {
            o->parts[i].f06 = o->parts[i].f08;
        }
    }
    factory_FactoryBeltRebuildTiles_500b00(o);
    return 1;
}
