#include "types.h"

extern void StringCtorFromCStr_1a2110(void *, s32);
extern void StrMapFind_1a4d90(void **, void *, void *);
extern void StringDtor_107b00(void *, s32);

void StrMapGetValue_1b13e0(s32 *arg0, u8 *arg1, s32 arg2) {
    void *sp3C;
    u8 sp30[12];

    StringCtorFromCStr_1a2110(sp30, arg2);
    StrMapFind_1a4d90((void **)&sp3C, arg1 + 0x24, sp30);
    StringDtor_107b00(sp30, -1);
    if (sp3C == arg1 + 0x28) {
        *arg0 = 0;
    } else {
        *arg0 = *(s32 *)((u8 *)sp3C + 0x18);
    }
}
