/* rgp:protos */
#define RGP_SELF_MenuObjSetLightRecMaybe_387cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void memcpy(void *, void *, s32);
/*rgp*/

struct Obj0 { u8 pad000[0x108]; s32 m108; };

void MenuObjSetLightRecMaybe_387cf0(s32 p0, struct Obj0 *p1)
{
    s32 t0;
    u8 *r0;

    if (p1 != 0) {
        t0 = p1->m108;
        r0 = ((u8 *)ArrayGetChecked_1936d0((u8 *)p1 + 0x70, t0));
        memcpy((void *)(p0 + 0x790), r0, 0x1D0);
        Character2LightBlendSetTarget_1aebe0(p0, 0, r0 + 0x30, r0 + 0x70, r0 + 0x180, r0 + 0x190, 0);
        return;
    }
}
