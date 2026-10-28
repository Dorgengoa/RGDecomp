/* rgp:protos */
#define RGP_SELF_TrailRibbonSetEnabled_32c820 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct S0032c820 {
    u8  pad[0x18];
    u32 val;
} S0032c820;

void TrailRibbonSetEnabled_32c820(S0032c820 *s, s32 b)
{
    s->val = s->val & 0x7FFFFFFF;
    if (b == 0) {
        s->val = s->val | 0x80000000;
    }
}
