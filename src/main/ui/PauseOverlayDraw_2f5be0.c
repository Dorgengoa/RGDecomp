#include "types.h"

extern void DiscStatusMessageDraw_39ecf0(s32);
extern void PauseReasonDrawMaybe_2f5c40(s32);
extern void GoTitleMenuDrawThunk_39bf40(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048276C;
extern s32 D_00482770;

void PauseOverlayDraw_2f5be0(void)
{
    s32 t0;
    s32 t1;
    s32 t2;

    t0 = D_0048276C;
    if (t0 != 0) {
        t1 = D_00482770;
        if (t1 == 6) {
            DiscStatusMessageDraw_39ecf0(0);
        } else {
            PauseReasonDrawMaybe_2f5c40(t1);
            t2 = D_0048276C;
            if (t2 == 3) {
                GoTitleMenuDrawThunk_39bf40(t2);
            }
        }
    }
}
