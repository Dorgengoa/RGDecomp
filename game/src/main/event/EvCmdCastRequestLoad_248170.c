/* rgp:protos */
#define RGP_SELF_EvCmdCastRequestLoad_248170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* lane N4 family: EvCmdCastRequestLoad_248170 / 00248200 / 00248240 / 002482d0 /
   00248310 / 00248350 - six byte-identical 56 B thunks, one source text. */

struct Obj0 { u8 pad00[4]; u8 *m04; };

extern struct Obj0 *gEventContext;

/*rgp*/
/*rgp*/

void EvCmdCastRequestLoad_248170(void *rgp_a0)
{
    u8 *q;

    q = gEventContext->m04 + 0x60;
    EventCastRequestLoad_24bc30(q, ScriptGetCodeAddr_249050((void *)rgp_a0));
}
