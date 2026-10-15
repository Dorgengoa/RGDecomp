#include "types.h"

extern s32 ActCfgTableGetInfoNameById_223b40(s32, s32, s32);

typedef struct E002154c0 {
    s32 id;
    s32 a;
    s32 b;
} E002154c0;

s32 ActCfgTableGetInfoNameByModeList_2154c0(s32 arg0, E002154c0 *arg1, s32 arg2, s32 arg3)
{
    s32 r;

    if (arg0 == 0) {
        return arg3;
    }
    while (arg1->id >= 0) {
        if (arg1->id == arg2) {
            r = ActCfgTableGetInfoNameById_223b40(arg0, arg1->a, arg1->b);
            if (r != 0) {
                return r;
            }
        }
        arg1++;
    }
    return arg3;
}
