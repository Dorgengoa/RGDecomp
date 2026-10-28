/* rgp:protos */
#define RGP_SELF_SoundNoteListPush_1b4cd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 SoundNoteListPush_1b4cd0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0, f32 fparg1)
{
    s32 sp6C;
    void *p;

    if (arg1 < 0 || arg2 < 0) {
        return 0;
    }
    arg1 = SoundMakeId_1bbf30(arg1, arg2);
    p = SoundNoteListFindSlot_1b4dc0(arg0, &sp6C, arg1, arg4);
    if (p == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)p + 0x0) = arg1;
    *(s16 *)((u8 *)p + 0x4) = arg3;
    *(f32 *)((u8 *)p + 0xC) = fparg0;
    *(f32 *)((u8 *)p + 0x10) = fparg1;
    if (sp6C != 0) {
        *(s16 *)((u8 *)p + 0x6) = 1;
    } else {
        *(s16 *)((u8 *)p + 0x6) = 0;
    }
    *(s16 *)((u8 *)p + 0x8) = arg4;
    return 1;
}
