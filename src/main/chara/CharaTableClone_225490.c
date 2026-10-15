#include "types.h"

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern s32 ActDataClone_225d40(void);
extern void CharaTableEntryCopy_226250(s32, s32, s32, s32);
extern s32 StrPoolIntern_302fd0(s32, s32, s32);
extern void CharaTableEntryCtor_226440(void);

s32 CharaTableClone_225490(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4)
{
    s16 n;
    s32 i;
    s32 r;
    f32 f;

    *(s32 *)(arg0 + 0x10) = 0;
    *(s16 *)(arg0 + 0x26) = 0;
    *(s64 *)(arg0 + 0) = 0;
    *(s64 *)(arg0 + 8) = 0;
    *(s32 *)(arg0 + 0x14) = 0;
    *(s16 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x18) = 0;
    *(s16 *)(arg0 + 0x22) = 0;
    *(s32 *)(arg0 + 0x1C) = 0;
    *(s16 *)(arg0 + 0x24) = 0;
    *(s32 *)(arg0 + 0x28) = 0;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s16 *)(arg0 + 0x30) = 0;
    *(f32 *)(arg0 + 0x34) = 1.0f;
    *(s16 *)(arg0 + 0x32) = 0;
    if (arg3 == 0 || arg4 == 0 || arg1 == 0 || arg2 == NULL || *(s32 *)(arg2 + 0x28) == 0) {
        return 0;
    }
    if (ActDataClone_225d40() == 0) {
        return 0;
    }
    if (*(s32 *)(arg2 + 0x2C) != 0) {
        n = *(s16 *)(arg2 + 0x30);
        if (n > 0) {
            r = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x44 + 0x10, arg3), CharaTableEntryCtor_226440, 0, 0x44, n);
            *(s32 *)(arg0 + 0x2C) = r;
            if (r == 0) {
                return 0;
            }
            *(s16 *)(arg0 + 0x30) = *(s16 *)(arg2 + 0x30);
            for (i = 0; i < *(s16 *)(arg0 + 0x30); i++) {
                CharaTableEntryCopy_226250(*(s32 *)(arg0 + 0x2C) + i * 0x44, *(s32 *)(arg2 + 0x2C) + i * 0x44, arg3, arg4);
            }
        }
    }
    r = StrPoolIntern_302fd0(arg4, *(s32 *)(arg2 + 0x28), arg3);
    *(s32 *)(arg0 + 0x28) = r;
    if (r == 0) {
        return 0;
    }
    f = *(f32 *)(arg2 + 0x34);
    *(f32 *)(arg0 + 0x34) = f;
    if (f <= 0.0f) {
        *(f32 *)(arg0 + 0x34) = 1.0f;
    }
    *(s16 *)(arg0 + 0x32) = *(s16 *)(arg2 + 0x32);
    return 1;
}
