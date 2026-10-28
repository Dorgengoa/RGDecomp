/* rgp:protos */
#define RGP_SELF_EvFollowObjInit_2f7f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_002f7f90 {
    u8 pad0[0x110];
    s32 f110;
    s32 f114;
    s32 f118;
    u8 pad11C[0x138 - 0x11C];
    f32 f138;
} S_002f7f90;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvFollowObjInit_2f7f90(S_002f7f90 *self, s32 p1, S_002f7f90 *src, s32 p3, s32 p4, s32 p5)
{
    EvFollowObjReset_2f8170(self);
    if (src == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    if (EvObjInit_2f9cf0(self, p1, src, p3, p4, p5) == 0) return 0;
    TargetRefCopy_2e7140((u8 *)self + 0xE0, (u8 *)src + 0xE0, p3);
    self->f110 = EvFollowObjGetPathRec_2f80c0(src);
    self->f114 = EvFollowObjGetVolumeRec_2f80b0(src);
    self->f118 = EvFollowObjGetParamRec_2f80a0(src);
    self->f138 = src->f138;
    return 1;
}
