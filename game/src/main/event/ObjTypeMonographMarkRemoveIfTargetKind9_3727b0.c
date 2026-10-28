/* rgp:protos */
#define RGP_SELF_ObjTypeMonographMarkRemoveIfTargetKind9_3727b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub3727 {
    u8 pad000[0x4];
} Sub3727;

typedef struct S3727 {
    u8       pad000[0xA0];
    Sub3727  mA0;
    u8       pad0A4[0xD0 - 0xA4];
    s32      mD0;
} S3727;

/*rgp*/
/*rgp*/

short ObjTypeMonographMarkRemoveIfTargetKind9_3727b0(S3727 *p, s32 q)
{ short rgp_v0 = 0;
    if ((rgp_v0 = ((short)TargetRefGetKind_2e7130(&p->mA0))) == 0x9) {
        if (q == (rgp_v0 = ((short)TargetRefGetId_2e7120(&p->mA0)))) {
            p->mD0 |= 0x1000000;
        }
    }
return rgp_v0; }
