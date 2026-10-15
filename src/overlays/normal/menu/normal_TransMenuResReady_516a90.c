#include "types.h"
/* normal 0x00516A90 -- `j normal_TransMenuResPoll_5181d0 / nop`, a bare tail call with an
 * EMPTY delay slot, so the callee takes no argument this function sets.
 * mwcc -O4 emits the tail call from plain source.  One of the 55 unnamed
 * functions; see scripts/n_unnamed.py. */
extern void normal_TransMenuResPoll_5181d0(void);

void normal_TransMenuResReady_516a90(void)
{
    normal_TransMenuResPoll_5181d0();
}
