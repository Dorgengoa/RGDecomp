#include "types.h"

/* factory.bin overlay, 0x004FF9F0 -- copy the four-float table at 0x00480840
 * to the stack and return element `i & 3` of it as a raw word.
 * 60 bytes / 15 words.  TWIN of factory_FUN_004FF9B0 (table at 0x00480850);
 * the only difference is the table address and the signedness of the read,
 * which is INERT here -- `((u32 *)t)[j]` and `*(s32 *)&t[j]` are one object.
 *
 * ** THE CONSTRUCT IS A STRUCT COPY THROUGH A CAST; see the twin's note for
 * the 42 measured cells that do not reach it.
 */

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

extern f32 D_00480840;

s32 factory_FactoryGridDirDx_4ff9f0(s32 i)
{
    V4 t;

    t = *(V4 *)&D_00480840;
    return ((s32 *)&t)[i & 3];
}
