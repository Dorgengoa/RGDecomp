#include "types.h"

extern void *GetGameData_1fede0(void);
extern s32 GroupGetRecordById_41c2a0(s32, s16, s32, s32);

s32 NpcObjFindDefById_2fb490(void *arg0, s32 arg1)
{
    void **rec;
    s32 i;
    void *temp_2;
    void *temp_4;

    if (*(s32 *)((u8 *)arg0 + 4) == 0) {
        return 0;
    }
    temp_2 = GetGameData_1fede0();
    rec = (void **)((u8 *)arg0 + 0xC);
    i = 0;
    while (i < *(s16 *)((u8 *)arg0 + 0x20C)) {
        temp_4 = *rec;
        if ((*(u16 *)((u8 *)temp_4 + 0) & 1) &&
            (*(s16 *)((u8 *)temp_4 + 0xC4) == arg1)) {
            return GroupGetRecordById_41c2a0(
                *(s32 *)((u8 *)*(void **)((u8 *)temp_2 + 8) + 0x6C),
                *(s16 *)((u8 *)temp_4 + 0xC6), -1, 1);
        }
        i++;
        rec++;
    }
    return 0;
}
