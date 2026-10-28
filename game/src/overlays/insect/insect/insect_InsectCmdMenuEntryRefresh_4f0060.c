/* rgp:protos */
#define RGP_SELF_insect_InsectCmdMenuEntryRefresh_4f0060 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F0060 -- 196 bytes, 49 instructions, 5 calls.  A widget refresh
 * on the 0x502C list head: publish the list's leading value, then colour the
 * n-th entry.  The colour is built with `ori / dsll 16 / ori`, a 64-bit
 * materialisation, so the local is 64-bit and every use is
 * `dsll32 0 / dsra32 0` = the (s32) narrowing at the call
 * ([[insect_FUN_004FAF00]]'s colour local, same shape).
 */

typedef struct Node {
    u8           pad00[4];
    struct Node *f4;                /* +0x04 */
    s8           f8;                /* +0x08 */
} Node;

typedef struct Ins {
    u8 pad000[0x878];
    void *f878;                     /* +0x0878 */
    u8 pad87C[0x502C - 0x87C];
    u8 f502C[4];                    /* +0x502C */
} Ins;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectCmdMenuEntryRefresh_4f0060(Ins *o, s32 n, void *m)
{
    Node *e;
    u64 col;

    UiSetTextString_28f510(o->f878, 0x7561, insect_InsectCmdMenuGetLabel_4efbe0((Node *)o->f502C, n), n);
    e = ((Node *)insect_InsectCmdMenuGetEntry_4efc50((Node *)o->f502C, n));
    if (e != 0) {
        col = 0xFF7F7F7F;
        if (e->f8 == 2) {
            if (m != 0) {
                if (insect_InsectPieceSpecialUsable_514860(m) == 0) {
                    col = 0xFF202020;
                }
            }
        }
        UiSetTextColor_290a40(o->f878, 0x7561, col, n);
    }
}
