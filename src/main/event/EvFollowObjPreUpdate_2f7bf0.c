#include "types.h"

/* MAIN EvFollowObjPreUpdate_2f7bf0 -- EvTargetPointObjPreUpdate_2f9280's body plus the 0xD0 flag poke. */

typedef struct V3 { f32 x, y, z; } V3;
typedef struct B36 { u32 w[9]; } B36;

extern void EvObjPreUpdateBase_2f9930(u8 *);

void EvFollowObjPreUpdate_2f7bf0(u8 *p)
{
    s32 f;
    s32 a;

    EvObjPreUpdateBase_2f9930(p);
    *(V3 *)(p + 0x58) = *(V3 *)(p + 0x10);
    *(V3 *)(p + 0x64) = *(V3 *)(p + 0x1C);
    *(V3 *)(p + 0x70) = *(V3 *)(p + 0x28);
    *(B36 *)(p + 0x7C) = *(B36 *)(p + 0x34);
    f = *(s32 *)(p + 0xD0);
    a = !((f & 0x80000000) != 0);
    if (a != 0) {
        if ((f & 0x2000000) != 0) {
            *(s32 *)(p + 0xD0) = f | 0x8000;
        }
    }
}
