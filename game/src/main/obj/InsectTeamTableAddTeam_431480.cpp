#include "types.h"

#undef NULL
#define NULL 0
extern "C" {
typedef struct Item00431480 {
    u8 pad0[0x10];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 rest : 4;
    u8 pad11[0xE0 - 0x11];
} Item00431480;

typedef struct S00431480 {
    u8 pad0[4];
    s32 unk4;
    Item00431480 items[20];
} S00431480;

extern void memcpy(void *, void *, s32);

Item00431480 *InsectTeamTableAddTeam_431480(S00431480 *arg0, void *arg1, s32 arg2) {
    Item00431480 *var_4;
    Item00431480 *var_16;
    s32 var_3;

    if (arg1 == 0) {
        return NULL;
    }
    var_16 = NULL;
    if (arg2 >= 0) {
        var_16 = &arg0->items[arg2];
    } else {
        var_4 = arg0->items;
        for (var_3 = 0; var_3 < 20; var_3++, var_4++) {
            if (!(var_4->b0)) {
                var_16 = var_4;
                break;
            }
        }
        if (var_16 == NULL) {
            return NULL;
        }
    }
    memcpy(var_16, arg1, 0xE0);
    var_16->b0 = true;
    var_16->b3 = false;
    arg0->unk4++;
    return var_16;
}

}
