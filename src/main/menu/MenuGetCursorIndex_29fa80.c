#include "types.h"

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

struct Obj1 {
    s8 m00;
    s8 m01;
};

extern struct Obj0 *GetGameData_1fede0(void);
extern struct Obj1 *MenuGetCursorPos_29fae0(s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);

s32 MenuGetCursorIndex_29fa80(s32 p0)
{
    struct Obj0 *r0;
    struct Obj1 *r1;
    s32 r2;

    r0 = GetGameData_1fede0();
    r1 = MenuGetCursorPos_29fae0(p0);
    r2 = PartyCountMembers_3c2010(r0->m18, 1, 1);
    return r1->m00 + r1->m01 * r2;
}
