#include "types.h"

typedef struct {
    u8 pad0[0x22];
    u8 a : 1;
    u8 b : 2;
    u8 c : 5;
} Obj00156f40;

void GsTestSetZTest_156f40(Obj00156f40 *arg0, s32 arg1)
{
    arg0->a = 1;
    switch (arg1) {
    case 0:
    case 1:
        arg0->b = 1;
        break;
    case 2:
        arg0->b = 2;
        break;
    case 3:
        arg0->b = 3;
        break;
    }
}
