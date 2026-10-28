/* rgp:protos */
#define RGP_SELF_EvCmdRecordGetSubState_25f500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S8;
struct Obj0;
struct Obj1;
struct Obj2;

struct S8 {
    s32 a;
    s32 b;
};

/*rgp*/
/*rgp*/

struct Obj0 {
    u8 pad000[0x24];
    struct Obj1 *m24;
};

struct Obj1 {
    u8 pad000[0x1188];
    struct Obj2 *m1188;
};

struct Obj2 {
    u8 pad000[0xC];
    s32 m0C;
    u8 pad010[0xC];
    s32 m1C;
};

s32 EvCmdRecordGetSubState_25f500(struct S8 *p0, s32 p1)
{
    struct Obj0 *r0;
    s32 t2;
    s32 t3;

    r0 = (struct Obj0 *)GetGameData_1fede0();
    t3 = r0->m24->m1188->m0C;
    t2 = r0->m24->m1188->m1C;
    if (p1 > 0) {
        ScriptSetRefInt_26a1e0(p0++, t3);
    }
    if (p1 >= 2) {
        ScriptSetRefInt_26a1e0(p0, t2);
    }
    return 1;
}
