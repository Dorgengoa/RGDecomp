#include "types.h"

typedef struct S1CF {
    u8  pad000[0x5968];
    s32 f5968;
    s32 f596C;
    f32 f5970;
    f32 f5974;
    f32 f5978;
    f32 f597C;
} S1CF;

void GameSceneDofReset_1cf200(S1CF *p)
{
    p->f5968 = 0;
    p->f596C = 1;
    p->f5970 = 1.0f;
    p->f5974 = (f32)3000;
    p->f5978 = 4000.0f;
    p->f597C = (f32)5000;
}
