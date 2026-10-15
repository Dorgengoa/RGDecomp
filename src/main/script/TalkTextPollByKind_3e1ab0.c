#include "types.h"

extern s32 NpcTalkTextPoll_41dca0(void *, void *);
extern s32 PtalkTextPoll_41f7b0(void *, void *);
extern s32 D_00483990;
extern void *D_00483994;

s32 TalkTextPollByKind_3e1ab0(s32 pad0, void *arg1) {
    s32 r;
    void *o;

    if (arg1 == NULL) {
        return 1;
    }
    if ((D_00483990 == 0) || (D_00483994 == NULL)) {
        return 1;
    }
    r = 1;
    if (*(s16 *)((u8 *)arg1 + 4) == 1) {
        o = *(void **)((u8 *)D_00483994 + 0x7C);
        if (o == NULL) {
            return r;
        }
        r = PtalkTextPoll_41f7b0(o, D_00483994);
        if (r == 3) {
            *(s32 *)((u8 *)arg1 + 0x20) = *(s32 *)((u8 *)o + 0x20);
        }
    } else if (*(s16 *)((u8 *)arg1 + 4) == 2) {
        o = *(void **)((u8 *)D_00483994 + 0x80);
        if (o == NULL) {
            return r;
        }
        r = NpcTalkTextPoll_41dca0(o, D_00483994);
        if (r == 3) {
            *(s32 *)((u8 *)arg1 + 0x20) = *(s32 *)((u8 *)o + 0x24);
        }
    }
    return r;
}
