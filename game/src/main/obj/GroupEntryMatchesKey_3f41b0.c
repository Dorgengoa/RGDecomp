/* rgp:protos */
#define RGP_SELF_GroupEntryMatchesKey_3f41b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct H { s16 f00; };
struct S { struct H *f00; s16 ft; u8 pad006[0x12]; u8 fb; };
s32 GroupEntryMatchesKey_3f41b0(struct S *p, s32 k)
{
    s16 v;
    u8 ok;

    if (p->f00 == 0) goto fail;
    v = p->f00->f00;
    if (v < 0) goto fail;
    ok = 0;
    if ((p->fb & 1) != 0) {
        ok = 1;
    } else if (p->ft == 3) {
        goto have;
    } else if (p->ft == 4) {
have:
        ok = 1;
    }
    if (!ok) goto fail;
    if (k < 0) goto ok1;
    if (k != v) goto fail;
ok1:
    return 1;
fail:
    return 0;
}
