/* rgp:protos */
#define RGP_SELF_DataTableRowViewGetAt_404910 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct Obj0 { u8 pad000[0x7C]; s8 m7C : 5; s8 m7Cb : 3; u8 pad07D[0x3]; s32 m80; };
s32 DataTableRowViewGetAt_404910(struct Obj0 *p0, s32 p1)
{
    if (p1 >= 0) {
        if (p1 < p0->m7C) {
            return (p0->m80 + (((p1 << 3) - p1) << 2));
        }
    }
    return 0;
}
