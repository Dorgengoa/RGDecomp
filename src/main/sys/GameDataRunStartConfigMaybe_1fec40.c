#include "types.h"

typedef struct A_FUN_001fec40 A_FUN_001fec40;
typedef struct S_FUN_001fec40 S_FUN_001fec40;
typedef struct G_FUN_001fec40 G_FUN_001fec40;

extern S_FUN_001fec40 *GetReadBuffHeap_2025e0(void);
extern void *MemStackHeapAlloc_14db10(S_FUN_001fec40 *s, s32 a, s32 b, s32 c);
extern G_FUN_001fec40 *GetGameData_1fede0(void);
extern void GameDataApplyStartConfigMaybe_3e69c0(G_FUN_001fec40 *g, A_FUN_001fec40 *a, void *m);
extern void MemStackReturnToOwnerMaybe_14dad0(S_FUN_001fec40 *s);
extern void MemStackHeapFree_14dcb0(S_FUN_001fec40 *s, void *m);

void GameDataRunStartConfigMaybe_1fec40(A_FUN_001fec40 *a)
{
    S_FUN_001fec40 *s;
    void *m;

    s = GetReadBuffHeap_2025e0();
    m = MemStackHeapAlloc_14db10(s, 2, 0x6000, 0x40);
    if (m == 0) {
        return;
    }
    GameDataApplyStartConfigMaybe_3e69c0(GetGameData_1fede0(), a, m);
    MemStackReturnToOwnerMaybe_14dad0(s);
    MemStackHeapFree_14dcb0(s, m);
}
