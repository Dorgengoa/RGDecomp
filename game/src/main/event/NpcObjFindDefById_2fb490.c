/* rgp:protos */
#define RGP_SELF_NpcObjFindDefById_2fb490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

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
            return ((s32)GroupGetRecordById_41c2a0(*(s32 *)((u8 *)*(void **)((u8 *)temp_2 + 8) + 0x6C), (long long)(*(s16 *)((u8 *)temp_4 + 0xC6)), (long long)(-1), 1

));
        }
        i++;
        rec++;
    }
    return 0;
}
