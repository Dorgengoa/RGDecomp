/* rgp:protos */
#define RGP_SELF_GameDataRunStartConfigMaybe_1fec40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A_FUN_001fec40 A_FUN_001fec40;
typedef struct S_FUN_001fec40 S_FUN_001fec40;
typedef struct G_FUN_001fec40 G_FUN_001fec40;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void GameDataRunStartConfigMaybe_1fec40(A_FUN_001fec40 *a)
{
    S_FUN_001fec40 *s;
    void *m;

    s = ((S_FUN_001fec40 *)GetReadBuffHeap_2025e0());
    m = MemStackHeapAlloc_14db10(s, 2, 0x6000, 0x40);
    if (m == 0) {
        return;
    }
    GameDataApplyStartConfigMaybe_3e69c0(((G_FUN_001fec40 *)GetGameData_1fede0()), a, m);
    MemStackReturnToOwnerMaybe_14dad0(s);
    MemStackHeapFree_14dcb0(s, m);
}
