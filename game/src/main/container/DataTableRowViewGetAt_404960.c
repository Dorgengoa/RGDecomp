/* rgp:protos */
#define RGP_SELF_DataTableRowViewGetAt_404960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x2C];
    s8 m2C;
    u8 pad02D[0x3];
    s32 m30;
};

s32 DataTableRowViewGetAt_404960(struct Obj0 *p0, s32 p1)
{
    s8 t0;
    s32 t1;

    if (p1 < 0) {
        goto fail;
    }
    t0 = p0->m2C;
    if (p1 < t0) {
        t1 = p0->m30;
        return (t1 + p1 * 12);
    }
fail:
    return 0;
}
