#include "types.h"
extern void *ActCfgTableFindLocusByName_2226d0(void *a, s32 c);
extern u8 CharaTrailSetup_22f380(void *r, s32 b, s32 d, f32 x, s32 e, f32 y,
                       s32 f, f32 z, f32 w);
s32 CharaTrailSetupByName_21f6c0(void *a, s32 b, s32 c, s32 d, s32 e, s32 f,
                 f32 x, f32 y, f32 z, f32 w)
{
    void *r;
    r = ActCfgTableFindLocusByName_2226d0(a, c);
    if (r != 0) {
        return CharaTrailSetup_22f380(r, b, d, x, e, y, f, z, w);
    }
    return -1;
}
/* MEASURED - this OVERTURNS the brief's "prototype / argument POSITION cannot
   reach argument SETUP order" null.  Retail interleaves the GPR and FPR
   argument moves; that interleave is reached by interleaving the CALLEE's
   prototype (s32,s32,f32,s32,f32,s32,f32,f32).  Under the PS2 EABI the
   independent pools put the args in the same registers either way, so this
   is purely a schedule lever.  OUR OWN parameter order is INERT (moving our
   four f32 params to the front gave object 01bce7b3, identical to the
   grouped-prototype arm). */
