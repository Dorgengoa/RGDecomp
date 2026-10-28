/* rgp:protos */
#define RGP_SELF_EventCameraCmdOrbitCastSet_255630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern char *strcpy(char *, const char *);
/*rgp*/   /* sin */
/*rgp*/   /* cos */

struct Obj0 {
    u8 pad000[0x10];
    f32 m10;
    f32 m14;
    f32 m18;
    u8 pad01C[0x4];
    u8 m20[0x10];
    s32 m30;
    s32 m34;
    u8 pad038[0x4];
    char m3C[0x20];
};

struct Obj1 {
    u8 pad000[0x50];
    f32 m50;
    f32 m54;
    f32 m58;
    u8 pad05C[0x4];
    f32 m60;
    f32 m64;
    f32 m68;
    u8 pad06C[0x4];
    f32 m70;
    f32 m74;
    f32 m78;
    s32 m7C;
    s32 m80;
    s32 m84;
    u8 pad088[0x8];
    u8 m90[0x10];
    f32 mA0;
    f32 mA4;
    f32 mA8;
    char mAC[0x20];
};

s32 EventCameraCmdOrbitCastSet_255630(struct Obj0 *p0, struct Obj1 *p1)
{
    p1->m80 = p0->m30;
    p1->m84 = p0->m34;
    sceVu0CopyVector(p1->m90, p0->m20);
    p1->mA0 = p0->m10;
    p1->mA4 = p0->m14;
    p1->mA8 = p0->m18;
    strcpy(p1->mAC, p0->m3C);
    p1->m50 = p1->m60 + p1->mA8 * Sinf_128fd0(p1->mA0);
    p1->m54 = p1->mA4 + p1->m64;
    p1->m58 = p1->m68 + p1->mA8 * Cosf_128d30(p1->mA0);
    p1->m70 = p1->mA0;
    p1->m74 = p1->mA4;
    p1->m78 = p1->mA8;
    p1->m7C = 1;
    return 0;
}
