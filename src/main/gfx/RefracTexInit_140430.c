#include "types.h"

typedef struct {
    u8 pad0[0x3BD8];
    u8 sub[0x3C];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} O140430;

extern void NameTableNodeReset_15ada0(void *arg0);
extern void NameTableNodeSetImage_15a640(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4,
                          s32 arg5, s32 arg6, s32 arg7, s64 arg8, s64 arg9);
extern u8 D_00458A50[0x400];

void RefracTexInit_140430(O140430 *arg0) {
    s32 flag;

    flag = 0;
    NameTableNodeReset_15ada0(&arg0->sub);
    NameTableNodeSetImage_15a640(arg0->sub, -0xA, D_00458A50, 0, 0x100, 0x100, 0x20, 0, flag, flag);
    arg0->b2 = flag;
}
