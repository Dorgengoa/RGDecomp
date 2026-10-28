/* rgp:protos */
#define RGP_SELF_insect_InsectModelMemReleaseAll_512280 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512280 -- 232 bytes, 58 instructions.  Tear down every live slot
 * of the 0x1C-entry s16 id table at +0x400.  The table cell is read through
 * the scaled base (`lh 0x400($3)`) and written through the named pointer
 * (`addiu $16,$3,0x400`) -- the left-associative pointer sum of
 * insect-load-across-store's sibling lever. */

typedef struct Ent {
    u8  pad00[0x58];
    s32 f58;                        /* +0x58 */
} Ent;

typedef struct Buf {
    s32 f0;                         /* +0x000 */
    u8  pad04[0x400 - 0x4];
    s16 f400[0x1C];                 /* +0x400 */
} Buf;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectModelMemReleaseAll_512280(Buf *b)
{
    void *h;
    s32 i;
    s16 *p;
    Ent *e;

    h = GetDrawCtxNameTable_15de40();
    for (i = 0; i < 0x1C; i++) {
        p = &b->f400[i];
        if (*p != -1) {
            ObjRecReleaseResAndReset_1c4c70(b->f0, *p);
            NameTableFreeGroup_158ac0(h, i + 0x243);
            NameTableFreeGroup_158ac0(h, i + 0x263);
            e = ((Ent *)insect_InsectModelMemFindPiece_512370(b, *p));
            if (e != 0) {
                if (e->f58 != 0) {
                    ModelDetachRootFrames_151460(e->f58);
                    e->f58 = 0;
                    ObjRecReleaseResAndReset_1c4c70(b->f0, *p + 0x40);
                }
            }
            *p = -1;
        }
    }
    insect_InsectModelMemReleaseHeap_5129c0(b);
    return 1;
}
