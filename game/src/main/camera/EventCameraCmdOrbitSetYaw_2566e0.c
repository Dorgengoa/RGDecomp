/* rgp:protos */
#define RGP_SELF_EventCameraCmdOrbitSetYaw_2566e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/   /* sin */
/*rgp*/   /* cos */

struct Obj0 {
    u8 pad000[0x30];
    f32 m30;
};

struct Obj1 {
    u8 pad000[0x50];
    f32 m50;
    u8 pad054[0x4];
    f32 m58;
    u8 pad05C[0x4];
    f32 m60;
    u8 pad064[0x4];
    f32 m68;
    u8 pad06C[0x4];
    f32 m70;
    u8 pad074[0x4];
    f32 m78;
};

s32 EventCameraCmdOrbitSetYaw_2566e0(struct Obj0 *p0, struct Obj1 *p1)
{
    p1->m50 = p1->m60 + p1->m78 * Sinf_128fd0(p0->m30);
    p1->m58 = p1->m68 + p1->m78 * Cosf_128d30(p0->m30);
    p1->m70 = p0->m30;
    return 0;
}
