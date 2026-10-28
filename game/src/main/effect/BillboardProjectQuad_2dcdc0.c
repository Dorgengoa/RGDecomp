/* rgp:protos */
#define RGP_SELF_BillboardProjectQuad_2dcdc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} IVec;

typedef struct {
    u8 pad0[0x1C0];
    u8 x1C0[0x40];
    f32 x200;
    u8 pad204[0x10];
    f32 x214;
} Cam;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 BillboardProjectQuad_2dcdc0(IVec *out, s32 arg1, f32 a, f32 b, f32 ang) {
    Vec v[4] __attribute__((aligned(16)));
    Vec p __attribute__((aligned(16)));
    Cam *cam;
    f32 h;
    f32 w;
    f32 inv;
    f32 c;
    f32 s;

    cam = ((Cam *)GetDrawCtxCamera_15de60());
    w = a * cam->x200;
    h = -b * cam->x214;
    MtxMulPoint_13c890(&p, cam->x1C0, arg1);
    if (p.w < 1.0f) {
        return 0;
    }
    inv = 1.0f / p.w;
    p.x *= inv;
    p.y *= inv;
    p.z *= inv;
    w *= inv;
    h *= inv;
    ang = -WrapAngle_13c050(ang);
    c = 0.5f * Cosf_128d30(ang);
    s = 0.5f * Sinf_128fd0(ang);
    v[0].x = p.x - c * w + s * h;
    v[0].y = p.y - s * w - c * h;
    v[0].z = p.z;
    v[0].w = p.w;
    v[1].x = p.x - c * w - s * h;
    v[1].y = p.y - s * w + c * h;
    v[1].z = p.z;
    v[1].w = p.w;
    v[2].x = p.x + c * w + s * h;
    v[2].y = p.y + s * w - c * h;
    v[2].z = p.z;
    v[2].w = p.w;
    v[3].x = p.x + c * w - s * h;
    v[3].y = p.y + s * w + c * h;
    v[3].z = p.z;
    v[3].w = p.w;
    out[0].x = 16.0f * v[0].x;
    out[0].y = 16.0f * v[0].y;
    out[0].z = v[0].z;
    out[0].w = 0;
    out[1].x = 16.0f * v[1].x;
    out[1].y = 16.0f * v[1].y;
    out[1].z = v[1].z;
    out[1].w = 0;
    out[2].x = 16.0f * v[2].x;
    out[2].y = 16.0f * v[2].y;
    out[2].z = v[2].z;
    out[2].w = 0;
    out[3].x = 16.0f * v[3].x;
    out[3].y = 16.0f * v[3].y;
    out[3].z = v[3].z;
    out[3].w = 0;
    return ScreenPosIsVisible_2dd0b0(&v[0]) & ScreenPosIsVisible_2dd0b0(&v[1]) & ScreenPosIsVisible_2dd0b0(&v[2]) & ScreenPosIsVisible_2dd0b0(&v[3]);
}
