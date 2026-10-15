#include "types.h"

typedef struct R_001e4150 {
    u8 pad000[0x8];
    void *f08;
    void *f0C;
} R_001e4150;

typedef struct Q_001e4150 {
    u8 pad000[0x34];
    R_001e4150 *f34;
} Q_001e4150;

typedef struct P_001e4150 {
    u8 pad000[0x8];
    Q_001e4150 *f08;
} P_001e4150;

extern P_001e4150 *GetGameData_1fede0(void);
extern s16 *TableFindByName_416750(void *a, s32 b);
extern void MapSetSkyId_1e41b0(void *o, s32 v);

void MapSetSkyIdByName_1e4150(void *o, s32 idx)
{
    s16 *p;
    s32 v;

    p = TableFindByName_416750(GetGameData_1fede0()->f08->f34->f0C, idx);
    if (p != 0) {
        v = *p;
    } else {
        v = -1;
    }
    MapSetSkyId_1e41b0(o, v);
}
