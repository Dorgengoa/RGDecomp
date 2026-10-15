#include "types.h"

extern s32 StrEqualNonNull_1ca6c0(void *arg0, void *arg1);
extern void *GetGameData_1fede0(void);
extern s32 ProgressValueGet_3cd2c0(s32 arg0, s32 arg1, s32 arg2);
extern s32 StateGetChapter_3cd5b0(s32 arg0);
extern u8 D_0045B418[0x10];
extern u8 D_0045B420[0x400];

typedef struct { u8 pad[0x10]; s32 unk10; } T1df;
void *MapBlockGetStoryName_1dffb0(void *arg0)
{
    T1df *temp_2;

    temp_2 = GetGameData_1fede0();
    if (((StateGetChapter_3cd5b0(temp_2->unk10) >= 7) ||
         ((StateGetChapter_3cd5b0(temp_2->unk10) == 6) &&
          (ProgressValueGet_3cd2c0(temp_2->unk10, 6, 0) >= 0x1E))) &&
        (StrEqualNonNull_1ca6c0(*(void **)((u8 *)arg0 + 0x54), D_0045B418) != 0)) {
        return &(*(u8 *)D_0045B420);
    }
    return *(void **)((u8 *)arg0 + 0x54);
}
