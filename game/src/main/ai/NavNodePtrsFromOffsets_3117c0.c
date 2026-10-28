/* rgp:protos */
#define RGP_SELF_NavNodePtrsFromOffsets_3117c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S003117C0 {
    u8 pad0[0x10];
    s32 f10;                  /* +0x10 */
    s32 f14;                  /* +0x14 */
} S003117C0;

void NavNodePtrsFromOffsets_3117c0(S003117C0 *p, s32 d)
{
    s32 v;

    v = p->f10;
    if (v != 0) {
        p->f10 = d + v;
    }
    v = p->f14;
    if (v != 0) {
        p->f14 = d + v;
    }
}
