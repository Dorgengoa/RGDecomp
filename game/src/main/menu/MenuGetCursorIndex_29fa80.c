/* rgp:protos */
#define RGP_SELF_MenuGetCursorIndex_29fa80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

struct Obj1 {
    s8 m00;
    s8 m01;
};

/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuGetCursorIndex_29fa80(s32 p0)
{
    struct Obj0 *r0;
    struct Obj1 *r1;
    s32 r2;

    r0 = ((struct Obj0 *)GetGameData_1fede0());
    r1 = ((struct Obj1 *)MenuGetCursorPos_29fae0(p0));
    r2 = PartyCountMembers_3c2010(r0->m18, 1, 1);
    return r1->m00 + r1->m01 * r2;
}
