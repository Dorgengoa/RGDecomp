/* rgp:protos */
#define RGP_SELF_insect_InsectAiActionListReset_523290 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00523290 -- 40 bytes.  A 0x200-entry clear of the array at +4,
 * a clear of the word at +0x804 and an external TAIL CALL (`j func_14D830`
 * with `lw $4, 0($4)` in the delay slot), so the argument is the FIRST member.
 * The +0x804 store sits in the loop-back branch's delay slot; it is the
 * post-loop statement the scheduler moved there. */
typedef struct S {
    void *f0;                       /* +0x000 */
    s32   list[0x200];              /* +0x004 .. +0x800 */
    s32   f804;                     /* +0x804 */
} S;

/*rgp*/

void insect_InsectAiActionListReset_523290(S *s)
{
    s32 i;

    for (i = 0; i < 0x200; i++) {
        s->list[i] = 0;
        s->f804 = 0;
    }
    MemStackReset_14d830(s->f0);
}
