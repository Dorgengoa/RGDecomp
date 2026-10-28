/* rgp:protos */
#define RGP_SELF_TimeOfDaySunDir_18d2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

struct Obj0;
struct Obj0 {
    u8 pad000[0x1F0];
    s32 m1F0;
    u8 pad1F4[0x1448];
    f32 m163C;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_0047E080;
extern f32 D_0047E084;
extern f32 D_0047E088;
extern f32 D_0047E08C;
extern f32 D_0047D804;

typedef struct {
    u8 pad000[0x208];
    f32 f208;
} T_0018d2d0;

void TimeOfDaySunDir_18d2d0(T_0018d2d0 *arg0, void *arg1)
{
    Vec4 v __attribute__((aligned(16)));
    Mtx4 mtx __attribute__((aligned(16)));
    f32 t;
    f32 angle1;

    v.x = D_0047E080;
    v.y = D_0047E084;
    v.z = D_0047E088;
    v.w = D_0047E08C;

    MtxIdentity_13d2e0(&mtx);
    t = TimeOfDayGetHour_18d920((struct Obj0 *)arg0);
    angle1 = WrapAngle_13c050(D_0047D804 * t / 24.0f);
    sceVu0RotMatrixZ(&mtx, &mtx, angle1);
    sceVu0RotMatrixY(&mtx, &mtx, arg0->f208);
    MtxMulVec4_13c900(arg1, &mtx, &v);
}
