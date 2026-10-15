#include "types.h"

typedef struct Slot23 {
    s32 f[31];
} Slot23;

extern Slot23 *D_004BCE60[];
extern s16 D_004BCE8C[];
extern s32 ScriptParseIntStrArgs_23de60(s32 *, s32 *, s32, s32);
extern void CharaEffEntrySetRefPos_230120(Slot23 *, s32, s32);

s32 CharaEffEntrySetRefPosCmd_23dc10(s32 a0, s32 a1)
{
    Slot23 *p;
    s32 a;
    s32 b;

    if (a1 != 0 && a1 != 1 && a1 != 2) {
        return 0;
    }
    if (D_004BCE60[0] == 0 || D_004BCE8C[0] >= 0x80) {
        return 1;
    }
    p = &D_004BCE60[0][D_004BCE8C[0]];
    b = 0;
    a = -1;
    if (ScriptParseIntStrArgs_23de60(&a, &b, a0, a1) != 0) {
        CharaEffEntrySetRefPos_230120(p, a, b);
    }
    return 1;
}
