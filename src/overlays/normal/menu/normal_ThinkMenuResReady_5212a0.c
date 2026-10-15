#include "types.h"
/* normal 0x005212A0 -- `j normal_ThinkMenuResPoll_5217e0 / nop`, a bare tail call with an
 * EMPTY delay slot, so the callee takes no argument this function sets.
 * mwcc -O4 emits the tail call from plain source.  One of the 55 unnamed
 * functions; see scripts/n_unnamed.py. */
extern void normal_ThinkMenuResPoll_5217e0(void);

void normal_ThinkMenuResReady_5212a0(void)
{
    normal_ThinkMenuResPoll_5217e0();
}
