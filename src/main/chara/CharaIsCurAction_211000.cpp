#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct S00211000 {
    u8 pad0[0xA0C];
    s8 *unkA0C;
    u8 pad10[0xA38 - 0xA10];
    s16 unkA38;
} S00211000;

extern s32 StrNotEqual_1f5300(s8 *, s8 *, s8 *);

u8 CharaIsCurAction_211000(S00211000 *arg0, s8 *arg1)
{
        void * arg_h1;

    bool result;
    s8 *temp;

    if (arg1 == NULL) {
        return 0;
    }
    if (arg0->unkA38 == 0) return 0;
    {
        result = 0;
        temp = arg0->unkA0C;
        if (*arg1 == *temp && StrNotEqual_1f5300(arg1 + 1, temp + 1, temp) == 0) {
            result = 1;
        }
        return result;
    }
    return 0;
}

}
