#include "types.h"

extern void ActTimeMoveAddOffset_227760(void *e, void *q, f32 x, f32 y);

void CharaTableDataAddTimeMove_226520(void *p, void *q, f32 x, f32 y)
{
    u8 *e;
    s32 i;

    e = *(u8 **)((u8 *)p + 0x14);
    if (e != 0) {
        for (i = 0; i < *(s16 *)((u8 *)p + 0x2C); i++, e += 0x14) {
            ActTimeMoveAddOffset_227760(e, q, x, y);
        }
    }
}
