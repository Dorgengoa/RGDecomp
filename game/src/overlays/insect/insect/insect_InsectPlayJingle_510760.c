/* rgp:protos */
#define RGP_SELF_insect_InsectPlayJingle_510760 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510760 -- 20 bytes, 5 instructions.  A real mwcc TAIL CALL:
 * `j func_207340` with the second integer argument in the delay slot.
 *
 * $4 is never written, and the delay slot loads $5 -- so the callee's FIRST
 * integer argument is this function's own pass-through parameter and the zero
 * is the SECOND.  With no parameter the zero lands in $4 (1 bad word). */

/*rgp*/

void insect_InsectPlayJingle_510760(s32 h)
{
    StreamPlayMwv_207340(h, 0, 1.0f);
}
