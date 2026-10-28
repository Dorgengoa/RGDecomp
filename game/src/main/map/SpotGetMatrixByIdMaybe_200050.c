/* rgp:protos */
#define RGP_SELF_SpotGetMatrixByIdMaybe_200050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x20]; f32 f20, f24, f28, f2C; } S_00200050;
typedef struct { u8 pad[0x30]; f32 f30, f34, f38, f3C; } T_00200050;

/*rgp*/
/*rgp*/
/*rgp*/

s32 SpotGetMatrixByIdMaybe_200050(T_00200050 *p, s32 id)
{
    void *g;
    void *x;
    S_00200050 *r;

    g = GetGameData_1fede0();
    x = *(void **)((s32)g + 8);
    r = ((S_00200050 *)GroupGetRecordById_425590(*(void **)((s32)x + 0x74), (s16)id));
    if (r == 0) return 0;
    MatRotY_1cb200(p, r->f2C);
    p->f30 = r->f20;
    p->f34 = r->f24;
    p->f38 = r->f28;
    p->f3C = 1.0f;
    return 1;
}
