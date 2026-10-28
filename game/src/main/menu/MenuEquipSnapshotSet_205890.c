/* rgp:protos */
#define RGP_SELF_MenuEquipSnapshotSet_205890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004BB9B4[][4];

void MenuEquipSnapshotSet_205890(s32 a, s32 b, s32 v)
{
    D_004BB9B4[a][b] = v;
}
