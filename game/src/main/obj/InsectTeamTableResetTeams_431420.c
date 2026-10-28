/* rgp:protos */
#define RGP_SELF_InsectTeamTableResetTeams_431420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0x4]; s32 m04; };
struct Obj1 { u8 pad000[0x10]; u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; u8 rest : 4; };

s32 InsectTeamTableResetTeams_431420(struct Obj0 *p0)
{
    struct Obj1 *q;
    s32 i;

    p0->m04 = 0;
    i = 0;
    q = (struct Obj1 *)((u8 *)p0 + 8);
    do {
        q->b0 = 0;
        q->b3 = 0;
        i = i + 1;
        q = (struct Obj1 *)((u8 *)q + 0xE0);
    } while (i < 0x14);
    return 1;
}
