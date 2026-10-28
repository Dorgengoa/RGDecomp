/* rgp:protos */
#define RGP_SELF_insect_InsectMsgClearBank_512b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512B90 -- a 2-instruction leaf that clears one word.  The stored
 * value is `$0`, so the body is no evidence for a second parameter; both call
 * sites (0x004F9648 and 0x0050E9F8) marshal $4 and nothing else, which is what
 * settles the arity at ONE. */
typedef struct Ent {
    s32 f00;
} Ent;

void insect_InsectMsgClearBank_512b90(Ent *p)
{
    p->f00 = 0;
}
