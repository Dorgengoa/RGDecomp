#include "types.h"
#include "vec.h"

struct Obj0;
struct Obj0 {
    u8 pad000[0x1F0];
    s32 m1F0;
    u8 pad1F4[0x1448];
    f32 m163C;
};

extern void MtxIdentity_13d2e0(void *p);
extern f32 TimeOfDayGetHour_18d920(struct Obj0 *p0);
extern f32 WrapAngle_13c050(f32 x);
extern void sceVu0RotMatrixZ(Mtx4 *out, Mtx4 *m, f32 a);
extern void sceVu0RotMatrixY(Mtx4 *out, Mtx4 *m, f32 a);
extern void MtxMulVec4_13c900(void *, void *, void *);

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
    Vec4 v;
    Mtx4 mtx;
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
