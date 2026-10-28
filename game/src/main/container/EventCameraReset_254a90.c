/* rgp:protos */
#define RGP_SELF_EventCameraReset_254a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* A constructor-shaped zero-fill.  The store WIDTHS come off the listing, not
   off the draft: m2c prints `unk50 = 0` for a `sq` and for an `sw` alike, and
   four `sw zero`s never coalesce into a `sq` -- only `= 0` on a u128 does. */

/*rgp*/
/*rgp*/
extern void strcpy(void *, const char *);

extern char D_0045EDA0[];

void EventCameraReset_254a90(u8 *p)
{
    s32 i;

    *(s32 *)(p + 0x30) = 0;
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x38) = 0;
    *(s32 *)(p + 0x3C) = 0;
    *(s32 *)(p + 0x40) = 0;
    *(s32 *)(p + 0x44) = 0;
    *(s32 *)(p + 0x48) = 0;
    *(u128 *)(p + 0x50) = 0;
    *(u128 *)(p + 0x60) = 0;
    *(s32 *)(p + 0x78) = 0;
    *(s32 *)(p + 0x74) = 0;
    *(s32 *)(p + 0x70) = 0;
    *(s32 *)(p + 0x7C) = 0;
    *(s32 *)(p + 0x80) = -1;
    *(s32 *)(p + 0x84) = 0;
    *(u128 *)(p + 0x90) = 0;
    strcpy(p + 0xAC, D_0045EDA0);
    *(s32 *)(p + 0xA8) = 0;
    *(s32 *)(p + 0xA4) = 0;
    *(s32 *)(p + 0xA0) = 0;
    *(u128 *)(p + 0xD0) = 0;
    *(u128 *)(p + 0xE0) = 0;
    *(s32 *)(p + 0xFC) = 0;
    *(s32 *)(p + 0xF8) = 0;
    *(s32 *)(p + 0xF0) = 0;
    *(u128 *)(p + 0x100) = 0;
    *(u128 *)(p + 0x110) = 0;
    *(u128 *)(p + 0x120) = 0;
    *(u128 *)(p + 0x130) = 0;
    *(s32 *)(p + 0x140) = 0;
    *(u128 *)(p + 0x150) = 0;
    *(u128 *)(p + 0x160) = 0;
    *(u128 *)(p + 0x170) = 0;
    *(s32 *)(p + 0x180) = 0;
    SplinePathPairReset_257030(p + 0x1C0);
    *(u128 *)(p + 0x190) = 0;
    *(u128 *)(p + 0x1A0) = 0;
    *(u128 *)(p + 0x1B0) = 0;
    *(s32 *)(p + 0x08) = 0;
    *(s32 *)(p + 0x0C) = 0;
    *(s32 *)(p + 0x10) = 0;
    *(s32 *)(p + 0x14) = 0;
    *(s32 *)(p + 0x18) = 0;
    *(s32 *)(p + 0x1C) = 0;
    *(s32 *)(p + 0x20) = 0;
    *(s32 *)(p + 0x24) = 0;
    *(s32 *)(p + 0x28) = 0;
    *(s32 *)(p + 0x2C) = 0;
    if (*(s32 *)(p + 0x00) != 0 && *(s32 *)(p + 0x04) > 0) {
        for (i = 0; i < *(s32 *)(p + 0x04); i++) {
            EventCameraNodeReset_254c90(*(u8 **)(p + 0x00) + i * 0x60);
        }
    }
}
