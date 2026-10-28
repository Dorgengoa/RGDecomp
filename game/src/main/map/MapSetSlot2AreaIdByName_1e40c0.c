/* rgp:protos */
#define RGP_SELF_MapSetSlot2AreaIdByName_1e40c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R_001e40c0 {
    u8 pad000[0x8];
    void *f08;
    void *f0C;
} R_001e40c0;

typedef struct Q_001e40c0 {
    u8 pad000[0x34];
    R_001e40c0 *f34;
} Q_001e40c0;

typedef struct P_001e40c0 {
    u8 pad000[0x8];
    Q_001e40c0 *f08;
} P_001e40c0;

/*rgp*/
/*rgp*/
/*rgp*/

void MapSetSlot2AreaIdByName_1e40c0(void *o, s32 idx)
{
    s16 *p;
    s32 v;

    p = ((s16 *)TableFindByName_416b00(((P_001e40c0 *)GetGameData_1fede0())->f08->f34->f08, idx));
    if (p != 0) {
        v = *p;
    } else {
        v = -1;
    }
    MapSetSlot2AreaId_1e4120(o, v);
}
