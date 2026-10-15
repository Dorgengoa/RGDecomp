#include "types.h"

/* the `beql` skipping the second call duplicates `i++` into its delay slot;
   that is the loop increment, not a second statement. */

extern s32 ActTimeAttrIsActive_2284d0(void *e, f32 x);
extern s32 ActTimeAttrGetFlags_227740(void *e);

s32 CharaTableDataCollectAttrFlags_226490(void *p, f32 x)
{
    s32 r;
    u8 *e;
    s32 i;

    r = 0;
    e = *(u8 **)((u8 *)p + 0x18);
    if (e != 0) {
        for (i = 0; i < *(s16 *)((u8 *)p + 0x2E); i++, e += 0x10) {
            if (ActTimeAttrIsActive_2284d0(e, x) != 0) {
                r |= ActTimeAttrGetFlags_227740(e + 8);
            }
        }
    }
    return r;
}
