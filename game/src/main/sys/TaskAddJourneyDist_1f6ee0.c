/* rgp:protos */
#define RGP_SELF_TaskAddJourneyDist_1f6ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 m[4]; } A_001f6ee0;
typedef struct { f32 m[4]; } B_001f6ee0;

typedef struct { u8 pad[0x18]; void *f18; } G_001f6ee0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B8680[];

void TaskAddJourneyDist_1f6ee0(void)
{
    A_001f6ee0 a __attribute__((aligned(16)));
    B_001f6ee0 b __attribute__((aligned(16)));
    G_001f6ee0 *g;
    void *x;
    void *r;

    g = ((G_001f6ee0 *)GetGameData_1fede0());
    x = g->f18;
    r = ActionMgrFindById_233b50(D_004B8680, *(s16 *)((s32)x + 0x18E));
    if (r == 0) return;
    CharaGetPos_2388d0(r, &a);
    SrtGetPosThunk_1c7430(r, &b);
    PartyAddJourneyDist_3c96c0(g->f18, VecDistXZ_1cb3f0(&a, &b));
}
