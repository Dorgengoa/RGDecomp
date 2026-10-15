#include "types.h"
/* normal 0x005245A0 -- `j normal_InsectEntryMenuResPoll_524680 / nop`, a bare tail call with an
 * EMPTY delay slot, so the callee takes no argument this function sets.
 * mwcc -O4 emits the tail call from plain source.  One of the 55 unnamed
 * functions; see scripts/n_unnamed.py. */
extern void normal_InsectEntryMenuResPoll_524680(void);

void normal_InsectEntryMenuResReady_5245a0(void)
{
    normal_InsectEntryMenuResPoll_524680();
}
