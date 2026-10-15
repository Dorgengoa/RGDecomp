#include "types.h"

typedef struct S00209D90 {
    u8 pad0[0x18];
    s32 *f18;                 /* +0x18 */
    s16 count;                /* +0x1C */
} S00209D90;

s32 DebugMenuWidgetGetChild_209d90(S00209D90 *o, s32 i)
{
    if (i < 0 || o->count <= i) {
        return 0;
    }
    return o->f18[i];
}
