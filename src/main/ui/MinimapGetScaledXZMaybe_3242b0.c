#include "types.h"

typedef struct ObjFUN_003242b0 {
    u8 pad0[0x40];
    f32 unk40;
    u8 pad44[0x48 - 0x44];
    f32 unk48;
} ObjFUN_003242b0;

extern f32 EntryGetScale_323b30(s32 arg0);
extern s32 MinimapGetPendingOrCurEntry_32a8f0(void);
extern s32 MinimapGetCurOrPendingEntry_32a920(void);

s32 MinimapGetScaledXZMaybe_3242b0(ObjFUN_003242b0 *arg0, f32 *arg1, f32 *arg2, s32 arg3)
{
    f32 div;
    s32 v;

    *arg2 = 0.0f;
    *arg1 = 0.0f;
    if (arg3 != 0) {
        v = MinimapGetCurOrPendingEntry_32a920();
    } else {
        v = MinimapGetPendingOrCurEntry_32a8f0();
    }
    if (v == 0) {
        return 0;
    }
    div = EntryGetScale_323b30(v);
    *arg1 = arg0->unk40 / div;
    *arg2 = arg0->unk48 / div;
    return 1;
}
