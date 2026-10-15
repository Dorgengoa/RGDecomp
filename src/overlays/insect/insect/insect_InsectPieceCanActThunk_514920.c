#include "types.h"
/* insect 0x00514900 -- 8 bytes, 2 instructions.  A pure tail jump to
 * insect_InsectPieceCanAct_514920 with the argument registers untouched, so the C is a
 * void->void forwarding call and mwcc turns it into `j`. */

extern void insect_InsectPieceCanAct_514920(void);

void insect_InsectPieceCanActThunk_514920(void)
{
    insect_InsectPieceCanAct_514920();
}
