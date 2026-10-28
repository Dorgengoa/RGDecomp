/* rgp:protos */
#define RGP_SELF_ScriptListRun_22f110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MEASURED, 8-arm sweep: the callee-saved pair is fixed by DECLARATION ORDER
   (`u8 *q;` before `s32 i;` gives i=$17, q=$18; the reverse costs 6 words) and
   the two increments must both sit in the FOR-INCREMENT, `i++` first --
   putting `q += 0xC` in the body costs 2 words and is inert across for/while. */

/*rgp*/

typedef struct {
    u8 pad00[4];
    u8 *m04;
    s16 m08;
    u16 m0A;
} Ctl;

void ScriptListRun_22f110(Ctl *p, s32 arg)
{
    s32 buf[9] __attribute__((aligned(16)));
    u8 *q;
    s32 i;

    if (p->m0A == 0) {
        p->m0A = 1;
        buf[0] = arg;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;
        buf[4] = 0;
        buf[5] = 0;
        buf[6] = 0;
        buf[7] = 0;
        buf[8] = 0;
        q = p->m04;
        for (i = 0; i < p->m08; i++, q += 0xC) {
            ScriptCallWithArgs_302770(q, buf, 0);
        }
        p->m0A = 0;
    }
}
