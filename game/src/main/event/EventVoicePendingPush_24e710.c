/* rgp:protos */
#define RGP_SELF_EventVoicePendingPush_24e710 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct S0024e710 {
    u8 pad00[0x24];
    void *arr[8];             /* +0x24 */
    s32 count;                /* +0x44 */
} S0024e710;

void EventVoicePendingPush_24e710(S0024e710 *s, void *v)
{
    s32 n;

    n = s->count;
    if (n < 8) {
        s->arr[n] = v;
        s->count = s->count + 1;
    }
}
