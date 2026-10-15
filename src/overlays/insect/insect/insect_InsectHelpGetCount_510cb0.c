#include "types.h"
/* insect 0x00510CB0 -- 100 bytes.  Two independent queries against the handle
 * at +0x10; each `bnel` PAST the decrement, so the source predicate is
 * `== 0`.  The handle is RE-LOADED for the second query rather than CSE'd. */
typedef struct Ctx {
    u8    pad00[0x10];
    void *f10;                      /* +0x10 */
} Ctx;

extern Ctx *func_1FEDE0(s32 *p);
extern s32  func_3CCD70(void *h, s32 id);

s32 insect_InsectHelpGetCount_510cb0(s32 *p)
{
    Ctx *c;
    s32  n;

    n = *p;
    c = func_1FEDE0(p);
    if (func_3CCD70(c->f10, 0x186) == 0) {
        n--;
    }
    if (func_3CCD70(c->f10, 0x187) == 0) {
        n--;
    }
    return n;
}
