/* rgp:protos */
#define RGP_SELF_MenuPartyCmdRowIsDimmed_29c2f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern f32 D_0047D288;
extern u16 D_0047EC00;
extern u16 D_0047EC10;

typedef struct Obj0029c2f0 {
    u8 pad00[0x4C4];
    s32 unk4C4;
} Obj0029c2f0;

s32 MenuPartyCmdRowIsDimmed_29c2f0(Obj0029c2f0 *arg0, s64 arg1_unused, s64 arg2) {
    f32 *var_2;

    if (*(s8 *)((u8 *)MenuGetCursorPos_29fae0((void *)arg0) + 1) == 0) {
        var_2 = ((f32 *)UiGetWidgetColor_2904b0(arg0->unk4C4, *(&D_0047EC00 + (s16)arg2)));
    } else {
        var_2 = ((f32 *)UiGetWidgetColor_2904b0(arg0->unk4C4, *(&D_0047EC10 + (s16)arg2)));
    }
    if (D_0047D288 == *var_2) {
        return 1;
    }
    return 0;
}
