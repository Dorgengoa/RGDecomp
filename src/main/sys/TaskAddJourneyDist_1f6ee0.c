#include "types.h"

typedef struct { f32 m[4]; } A_001f6ee0;
typedef struct { f32 m[4]; } B_001f6ee0;

typedef struct { u8 pad[0x18]; void *f18; } G_001f6ee0;
extern G_001f6ee0 *GetGameData_1fede0(void);
extern void *ActionMgrFindById_233b50(u8 *, s32);
extern void CharaGetPos_2388d0(void *, A_001f6ee0 *);
extern void SrtGetPosThunk_1c7430(void *, B_001f6ee0 *);
extern f32 VecDistXZ_1cb3f0(A_001f6ee0 *, B_001f6ee0 *);
extern void PartyAddJourneyDist_3c96c0(void *, f32);
extern u8 D_004B8680[];

void TaskAddJourneyDist_1f6ee0(void)
{
    A_001f6ee0 a;
    B_001f6ee0 b;
    G_001f6ee0 *g;
    void *x;
    void *r;

    g = GetGameData_1fede0();
    x = g->f18;
    r = ActionMgrFindById_233b50(D_004B8680, *(s16 *)((s32)x + 0x18E));
    if (r == 0) return;
    CharaGetPos_2388d0(r, &a);
    SrtGetPosThunk_1c7430(r, &b);
    PartyAddJourneyDist_3c96c0(g->f18, VecDistXZ_1cb3f0(&a, &b));
}
