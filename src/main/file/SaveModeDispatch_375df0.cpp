#include "types.h"

class C375 {
public:
    u8 pad0[0x4DC];
    s32 m4DC;
    s32 m4E0;
};
typedef s32 (C375::*PMF375)(void);

extern "C" {
extern PMF375 D_00463840[];
extern void McSetErrorResult_375890(C375 *, s32);
extern void SaveSetMode_375a10(C375 *, s32);

s32 SaveModeDispatch_375df0(C375 *arg0) {
    s32 idx;
    s32 t;
    s32 r;

    idx = arg0->m4DC;
    r = 0;
    if (idx >= 0) {
        t = (arg0->*D_00463840[idx])();
        if (t == 1) {
            arg0->m4E0 = 0;
            SaveSetMode_375a10(arg0, 1);
        } else if (t != 0) {
            McSetErrorResult_375890(arg0, t);
        }
    }
    if (idx != arg0->m4DC) {
        r = 1;
    }
    return r;
}

}
