#include "types.h"
/* insect 0x00510710 -- 68 bytes.  Two queries against the same handle; the
 * `slt $2,$2,$16` has the SECOND result in rs, so the comparison is
 * `b < a` with the first result named. */

typedef struct Ctx {
    u8  pad00[0x10];
    s32 m10;                        /* +0x10 */
} Ctx;

extern Ctx *func_1FEDE0(void);
extern s32  func_3CCAC0(s32 h, s32 k);

s32 insect_InsectStoryIsRankCleared_510710(void)
{
    Ctx *g;
    s32  a;
    s32  b;

    g = func_1FEDE0();
    a = func_3CCAC0(g->m10, 5);
    b = func_3CCAC0(g->m10, 6);
    return b < a;
}
