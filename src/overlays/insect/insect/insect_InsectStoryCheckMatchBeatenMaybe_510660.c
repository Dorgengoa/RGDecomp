#include "types.h"
/* insect 0x00510660 -- 172 bytes, 43 instructions, 6 calls.
 *
 * `slt $1,$16,$2` lands in $at, so the branch-taken condition is NOT a bare
 * `<` with the tested value on the left: the guard is spelled `d > n`
 * (at-compare-class).  Both early `return K` blocks reach the SHARED epilogue
 * through a branch-likely with the constant in the delay slot.
 */

typedef struct H {
    u8  pad00[0x10];
    s32 m10;                        /* +0x10 */
} H;

extern H   *func_1FEDE0(void);
extern s32  func_3CCAC0(s32 h, s32 id);
extern void func_3CC9C0(s32 h, s32 id, s16 v, s32 w);

s32 insect_InsectStoryCheckMatchBeatenMaybe_510660(s32 f)
{
    H  *h;
    s32 b;
    s32 n;

    h = func_1FEDE0();
    b = func_3CCAC0(h->m10, 6) + 0x13;
    n = func_3CCAC0(h->m10, 7);
    if (func_3CCAC0(h->m10, b) <= n) {
        if (f != 0) {
            func_3CC9C0(h->m10, b, func_3CCAC0(h->m10, 7) + 1, 0);
        }
        return 0;
    }
    return 2;
}
