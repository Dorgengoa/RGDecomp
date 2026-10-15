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

extern void *func_15DE40(void);
extern void  func_1C4C70(s32 h, s32 k);
extern void  func_158AC0(void *h, s32 k);
extern void  func_151460(s32 h);
extern Ent  *insect_InsectModelMemFindPiece_512370(Buf *b, s32 id);
extern void  insect_InsectModelMemReleaseHeap_5129c0(Buf *b);

s32 insect_InsectModelMemReleaseAll_512280(Buf *b)
{
    void *h;
    s32 i;
    s16 *p;
    Ent *e;

    h = func_15DE40();
    for (i = 0; i < 0x1C; i++) {
        p = &b->f400[i];
        if (*p != -1) {
            func_1C4C70(b->f0, *p);
            func_158AC0(h, i + 0x243);
            func_158AC0(h, i + 0x263);
            e = insect_InsectModelMemFindPiece_512370(b, *p);
            if (e != 0) {
                if (e->f58 != 0) {
                    func_151460(e->f58);
                    e->f58 = 0;
                    func_1C4C70(b->f0, *p + 0x40);
                }
            }
            *p = -1;
        }
    }
    insect_InsectModelMemReleaseHeap_5129c0(b);
    return 1;
}
