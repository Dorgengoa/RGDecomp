#include "types.h"

extern s32 ActCfgTableGetInfoNameById_223b40(s32, s32, s32);
extern char *strcpy(char *, const char *);

void ActCfgTableGetInfoNameByMode_21f5b0(s32 arg0, char *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 var_16;
    s32 var_2;

    var_16 = arg7;
    switch (arg2) {
    case 0:
        var_2 = ActCfgTableGetInfoNameById_223b40(arg0, arg3, 0);
        if (var_2 != 0) {
            var_16 = var_2;
        }
        break;
    case 1:
        var_2 = ActCfgTableGetInfoNameById_223b40(arg0, arg4, 0);
        if (var_2 != 0) {
            var_16 = var_2;
        }
        break;
    case 2:
        var_2 = ActCfgTableGetInfoNameById_223b40(arg0, arg5, 0);
        if (var_2 != 0) {
            var_16 = var_2;
        }
        break;
    case 3:
        var_2 = ActCfgTableGetInfoNameById_223b40(arg0, arg6, 0);
        if (var_2 != 0) {
            var_16 = var_2;
        }
        break;
    }
    strcpy(arg1, (const char *)var_16);
}
