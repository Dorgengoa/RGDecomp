#include "types.h"
typedef struct P28E9E0 {
    u8 pad000[0x20];
    u8 b0 : 1;
    u8 b1 : 7;
} P28E9E0;
void MenuGridCursorRequestSe_28e9e0(P28E9E0 *p, s32 v)
{
    if ((v & 1) == 0) {
        p->b0 = 1;
    }
}
