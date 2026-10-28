/* rgp:protos */
#define RGP_SELF_ProgressGetByCode_3cd260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct B3CD260 { u8 pad000[0x8]; s16 f08; };
struct A3CD260 { u8 pad000[0x8]; void *f08; };
struct T3CD260 { u8 pad000[0x4]; struct A3CD260 *f04; };

/*rgp*/

s32 ProgressGetByCode_3cd260(struct T3CD260 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    struct A3CD260 *a;
    struct B3CD260 *r;
    s32 off;

    a = p->f04;
    if (a == 0) return -1;
    r = ((struct B3CD260 *)GroupTableFindEntryByCode_422910(a->f08, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3));
    if (r != 0) {
        off = r->f08 * 2;
        return *(s16 *)(off + (s32)p + 0xA);
    }
    return -1;
}
