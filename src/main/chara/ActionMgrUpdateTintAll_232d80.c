#include "types.h"

/* A list walk: the `b` into the test with the head in its delay slot is the
   standard while-loop rotation. */

extern s32 DListGetHead_42ea60(void *);
extern void CharaUpdateTint_213fc0(s32, f32);
extern s32 DListGetNext_42eb30(s32);

void ActionMgrUpdateTintAll_232d80(s32 p0, f32 f)
{
    s32 it;

    it = DListGetHead_42ea60((u8 *)p0 + 0x20);
    while (it != 0) {
        CharaUpdateTint_213fc0(it + 0x10, f);
        it = DListGetNext_42eb30(it);
    }
}
