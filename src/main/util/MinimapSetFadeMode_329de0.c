#include "types.h"

extern void MinimapSetFadeAlpha_32a1d0(void *, f32);

void MinimapSetFadeMode_329de0(void *arg0, s32 arg1, f32 fparg0) {
    f32 var_f0;
    f32 var_f1;
    s8 v;

    if ((arg1 >= 3) || (arg1 < 0)) {
        arg1 = 0;
    }
    *(s8 *)((u8 *)arg0 + 0x11B) = arg1;
    v = arg1;
    var_f1 = 0.0f;
    switch (v) {
        case 0:
            return;
        case 1:
            if (!(fparg0 < 0.0f) && (fparg0 <= 1.0f)) {
                var_f1 = fparg0;
            }
            MinimapSetFadeAlpha_32a1d0(arg0, var_f1);
            return;
        case 2:
            var_f0 = 1.0f;
            if (!(fparg0 < 0.0f) && (fparg0 <= 1.0f)) {
                var_f0 = fparg0;
            }
            MinimapSetFadeAlpha_32a1d0(arg0, var_f0);
            return;
    }
}
