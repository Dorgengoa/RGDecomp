#include "types.h"
typedef struct { u8 b0 : 1; u8 rest : 7; } BF;
typedef struct {
    u8 pad[0x23C];
    BF f23C;
    u8 pad23D[0x49C - 0x23D];
    s16 f49C;
    s16 f49E;
} OBJ;

s32 CharaPendingActStartMaybe_3ac5b0(OBJ *o, s16 arg1) {
    if (o->f23C.b0) {
        return 0;
    }
    o->f23C.b0 = 1;
    o->f49C = 0;
    o->f49E = arg1;
    return 1;
}
