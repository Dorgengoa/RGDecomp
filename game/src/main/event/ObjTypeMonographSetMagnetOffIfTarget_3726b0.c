/* rgp:protos */
#define RGP_SELF_ObjTypeMonographSetMagnetOffIfTarget_3726b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void ObjTypeMonographSetMagnetOffIfTarget_3726b0(u8 *p, s32 p1, f32 t)
{
    s32 r;
    s32 s;

    r = ((short)TargetRefGetKind_2e7130(p + 0xA0));
    switch (r) {
    case 4:
    case 5:
        break;
    default:
        return;
    }
    s = ((short)TargetRefGetId_2e7120(p + 0xA0));
    if (p1 == s) {
        ObjTypeMonographSetMagnetOffTime_372730(p, t);
    }
}
