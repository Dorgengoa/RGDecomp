/* rgp:protos */
#define RGP_SELF_ModelObjFadeSnap_186b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0x1C0]; s32 m1C0; u8 pad1C4[0x4]; s32 m1C8; u8 pad1CC[0x14]; s32 m1E0; };

void ModelObjFadeSnap_186b20(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    u8 b;

    t0 = p0->m1C0;
    if (t0 == 0) {
        p0->m1E0 = 0;
        return;
    }
    t1 = p0->m1C8;
    b = (t1 == 0);
    if (b) {
        p0->m1E0 = 0x3F800000;
    } else {
        p0->m1E0 = 0;
    }
    p0->m1E0 = 0xBF800000;
}
