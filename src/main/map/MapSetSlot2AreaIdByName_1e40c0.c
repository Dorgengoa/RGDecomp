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

extern P_001e40c0 *GetGameData_1fede0(void);
extern s16 *TableFindByName_416b00(void *a, s32 b);
extern void MapSetSlot2AreaId_1e4120(void *o, s32 v);

void MapSetSlot2AreaIdByName_1e40c0(void *o, s32 idx)
{
    s16 *p;
    s32 v;

    p = TableFindByName_416b00(GetGameData_1fede0()->f08->f34->f08, idx);
    if (p != 0) {
        v = *p;
    } else {
        v = -1;
    }
    MapSetSlot2AreaId_1e4120(o, v);
}
