/* rgp:protos */
#define RGP_SELF_Vec4ArraySet_1a8760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct S001A8760 {
    s32 f0;                   /* +0x0 */
    u128 *f4;                 /* +0x4 */
} S001A8760;

void Vec4ArraySet_1a8760(S001A8760 *p, s32 i, u128 *in)
{
    if (i < 0 || i >= p->f0) {
        return;
    }
    p->f4[i] = *in;
}
