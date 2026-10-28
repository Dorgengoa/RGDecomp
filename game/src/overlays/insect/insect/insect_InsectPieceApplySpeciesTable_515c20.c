/* rgp:protos */
#define RGP_SELF_insect_InsectPieceApplySpeciesTable_515c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00515C20 -- 42 instructions.  The 95-byte prologue loop is an
 * explicit byte copy of the 19x5 table at insect_D_00524190 into a frame buffer at
 * 0x10; spelling it as a local aggregate INITIALISER would put the image in
 * this unit's .rodata instead of referencing retail's, so the copy is
 * written out.  The key byte at +0x38 is re-loaded every iteration, so the
 * compare reads the member and not a hoisted local. */

typedef struct Obj {
    u8 pad00[0x38];
    s8 m38;                         /* +0x38 */
    u8 pad39[0x6E - 0x39];
    s8 m6E;                         /* +0x6E */
    s8 m6F;                         /* +0x6F */
    u8 pad70[0xDC - 0x70];
    s16 mDC;                        /* +0xDC */
} Obj;

extern s8 insect_D_00524190[19][5];

/*rgp*/

void insect_InsectPieceApplySpeciesTable_515c20(Obj *o)
{
    s8 tbl[19][5] __attribute__((aligned(16)));
    s8 *src;
    s8 *dst;
    s32 n;
    s32 i;

    src = &insect_D_00524190[0][0];
    dst = &tbl[0][0];
    n = 0x5F;
    do {
        n--;
        *dst = *src;
        src++;
        dst++;
    } while (n > 0);

    for (i = 0; i < 19; i++) {
        if (o->m38 == tbl[i][0]) {
            o->m6E = tbl[i][1];
            o->m6F = tbl[i][2];
            o->mDC = tbl[i][3] + 0x12C;
            if (tbl[i][4] != 0) {
                insect_InsectPieceSetStatus_5132d0(o, 0x22);
                return;
            }
            return;
        }
    }
}
