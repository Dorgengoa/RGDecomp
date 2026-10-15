#include "types.h"
/* insect 0x00510DC0 -- three-call forwarder.
 * ARITY: every argument of all three calls is MARSHALLED with a real
 * instruction here, so by the no-dead-argument-setup rule at -O4 each one is
 * read by its callee -- nothing is inferred from a pass-through.
 * func_134BB0's result is dead: $2 is overwritten by the next call.
 * The result of func_14D950 is held in a LOCAL, not re-read from +0x0C:
 * retail's third call takes `daddu $4, $2, $0` straight off the return
 * register rather than reloading. */
typedef struct WObj { u8 pad00[0xC]; s32 f0C; } WObj;

extern s32 func_134BB0(void *c);
extern s32 func_14D950(void *b, s32 k);
extern void func_134A98(s32 t, void *c);

void insect_InsectHelpEntrySetPageImage_510dc0(WObj *a, void *b, void *c)
{
    s32 t;

    func_134BB0(c);
    t = func_14D950(b, 1);
    a->f0C = t;
    func_134A98(t, c);
}
