#include "types.h"

extern s32 MapCfgIsCameraSkipped_18cb00(void);
extern s32 FixCameraRecGet_189710(s32, s32);
extern s32 VariantReadVec3_15f6c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481250;
extern s32 D_004812CC;

s32 MapCfgFixCameraPos_18b7c0(s32 p0)
{
    s32 r0;
    s32 rv4;
    s32 t0;
    s32 t1;
    s32 r1;
    s32 rv3;
    s32 r2;

    r0 = MapCfgIsCameraSkipped_18cb00();
    rv4 = rv3;
    if (r0 != 0) {
        rv4 = 1;
    } else {
        t0 = D_00481250;
        t1 = D_004812CC;
        r1 = FixCameraRecGet_189710(t0, t1);
        rv3 = 1;
        if (r1 == 0) {
            rv3 = 0;
        } else {
            r2 = VariantReadVec3_15f6c0((r1 + 0x10), p0);
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}
