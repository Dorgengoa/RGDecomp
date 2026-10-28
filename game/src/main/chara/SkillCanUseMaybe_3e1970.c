/* rgp:protos */
#define RGP_SELF_SkillCanUseMaybe_3e1970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E {
    s16 m00;
    s16 m02;
    s16 m04;
    u8 pad006[0x2];
    f32 m08;
    u8 pad00C[0x4];
    f32 m10;
    f32 m14;
};

struct S {
    s16 m00;
    u8 pad002[0x2A];
    s16 m2C;
};

extern struct E D_004E9800[];

u8 SkillCanUseMaybe_3e1970(s32 a, struct S *p)
{
    struct E *e;
    s32 i;
    u8 rv;

    rv = 1;
    e = D_004E9800;
    for (i = 0; i < 0x40; i++, e++) {
        if (e->m00 == p->m00) {
            rv = 0;
            break;
        }
        if (e->m04 != p->m2C) {
            continue;
        }
        if (e->m08 < e->m10) {
            rv = 0;
            break;
        }
        if (a == e->m02) {
            if (e->m08 < e->m14) {
                rv = 0;
                break;
            }
        }
    }
    return rv;
}
