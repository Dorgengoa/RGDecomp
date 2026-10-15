#include "types.h"

typedef struct {
    u8 pad0[0x21];
    u8 lo : 6;
    u8 b6 : 1;
    u8 b7 : 1;
} S00157010;

void GsTestSetDestAlphaMode_157010(S00157010 *arg0, s32 arg1) {
    if (arg1 == 0) {
        arg0->b6 = 0;
        arg0->b7 = 0;
    } else if (arg1 == 1) {
        arg0->b7 = 0;
    } else {
        arg0->b7 = 1;
    }
}
