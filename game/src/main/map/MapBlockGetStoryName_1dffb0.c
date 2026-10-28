/* rgp:protos */
#define RGP_SELF_MapBlockGetStoryName_1dffb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045B418[0x10];
extern u8 D_0045B420[0x400];

typedef struct { u8 pad[0x10]; s32 unk10; } T1df;
void *MapBlockGetStoryName_1dffb0(void *arg0)
{
    T1df *temp_2;

    temp_2 = GetGameData_1fede0();
    if (((((short)StateGetChapter_3cd5b0(temp_2->unk10)) >= 7) ||
         ((((short)StateGetChapter_3cd5b0(temp_2->unk10)) == 6) &&
          (((short)ProgressValueGet_3cd2c0(temp_2->unk10, (long long)(6), (long long)(0), 0)) >= 0x1E))) &&
        (((unsigned char)StrEqualNonNull_1ca6c0(*(void **)((u8 *)arg0 + 0x54), D_0045B418)) != 0)) {
        return &(*(u8 *)D_0045B420);
    }
    return *(void **)((u8 *)arg0 + 0x54);
}
