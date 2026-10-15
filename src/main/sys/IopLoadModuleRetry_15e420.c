#pragma optimization_level 3
#include "types.h"

extern s32 sceSifLoadModule_11f7a0(s8 *arg0, s32 arg1, s32 arg2);
extern void strcat(s8 *arg0, s8 *arg1);
extern void strcpy(s8 *arg0, s8 *arg1);
extern s32 strlen(s8 *arg0);
extern u8 D_00458CB8[0x400];
extern s32 D_0047DF38;

static inline s32 toupper_i(s32 c) { if (c >= 0x61 && c <= 0x7A) { return c - 0x20; } return c; }
static inline s8 toupper_(s8 c) { if (c >= 0x61 && c < 0x7B) { return c - 0x20; } return c; }

void IopLoadModuleRetry_15e420(s8 *arg0, s8 *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s8 *var_3;
    s8 *var_16;
    s8 c;
    u32 var_2;
    s8 sp50[0x100];

    var_2 = 0x100;
    var_3 = sp50;
    if (var_3 != NULL) {
        do {
            *var_3 = 0;
            var_2 -= 1;
            var_3 += 1;
        } while (var_2 != 0);
    }
    if (arg1 != 0) {
        strcpy(sp50, arg1);
    }
    var_16 = sp50 + strlen(sp50);
    strcat(sp50, arg0);
    if (arg2 != 0) {
        while (*var_16 != 0) {
            c = *var_16;
            if (c >= 0x61) {
                if (c <= 0x7A) {
                    c = c - 0x20;
                }
            }
            if (c == 0x2F) {
                c = 0x5C;
            }
            *var_16 = c;
            var_16++;
        }
        strcat(sp50, (s8 *)D_00458CB8);
    }
    while (sceSifLoadModule_11f7a0(sp50, arg3, arg4) < 0) {
        if (D_0047DF38 == 0) {
            break;
        }
    }
}
