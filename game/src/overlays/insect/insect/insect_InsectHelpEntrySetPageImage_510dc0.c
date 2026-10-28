/* rgp:protos */
#define RGP_SELF_insect_InsectHelpEntrySetPageImage_510dc0 1
#include "port/game_protos.h"
#line 1
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

extern s32 strlen(void *c);
/*rgp*/
extern void strcpy(s32 t, void *c);

void insect_InsectHelpEntrySetPageImage_510dc0(WObj *a, void *b, void *c)
{
    s32 t;

    strlen(c);
    t = MemStackAllocQw_14d950(b, 1);
    a->f0C = t;
    strcpy(t, c);
}
