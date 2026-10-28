/* rgp:protos */
#define RGP_SELF_TextReaderParseAll_15f3f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Drains TextReaderParseStatement_15f430 until it reports failure. The object is held in $16
   because the callee takes it in $4 and a second argument goes in $5, so the
   argument register cannot carry it across the loop. */

/*rgp*/

int TextReaderParseAll_15f3f0(void *self)
{ int rgp_v0 = 0;
    while ((rgp_v0 = TextReaderParseStatement_15f430(self, 1)) >= 0) {
        ;
    }
return rgp_v0; }
