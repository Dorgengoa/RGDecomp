/* rgp:protos */
#define RGP_SELF_DebugItemListDtor_29ace0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN DebugItemListDtor_29ace0 -- guarded forwarder.  `dsll32/dsra32 ..,16` off the
   PARAMETER is the s16 cast on an s32 argument (the normal-overlay reading);
   the raw $5 is what reaches OperatorDelete_100840, so the cast is only in the test. */

/*rgp*/

void *DebugItemListDtor_29ace0(void *p, s32 n)
{
    if (p != 0) {
        if ((s16)n > 0) {
            OperatorDelete_100840(p);
        }
    }
    return p;
}
