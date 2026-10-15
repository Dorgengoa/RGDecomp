#include "types.h"

extern s32 NpcTalkTextRequest_41de00(s32 arg0, s16 arg1, s16 arg2);
extern s32 PtalkTextRequest_41f900(s32 arg0, s16 arg1, s16 arg2);
extern s32 D_00483990;
extern void *D_00483994;

s32 TalkTextRequestByKind_3e1b80(s32 pad0, void *arg1)
{
    s32 h;
    void *p;
    s32 r;
    s16 k;

    if (arg1 == NULL) {
        return 0;
    }
    if ((D_00483990 == 0) || (D_00483994 == NULL)) return 0;
    k = *(s16 *)((u8 *)arg1 + 4);
    if (k == 1) {
        h = *(s32 *)((u8 *)D_00483994 + 0x7C);
        if (h == 0) {
            return 0;
        }
        p = *(void **)((u8 *)arg1 + 0x14);
        if (p != NULL) {
            r = PtalkTextRequest_41f900(h, *(s16 *)((u8 *)arg1 + 6), *(s16 *)((u8 *)p + 0x10));
        } else {
            r = 0;
        }
        return r;
    } else if (k == 2) {
        h = *(s32 *)((u8 *)D_00483994 + 0x80);
        if (h == 0) {
            return 0;
        }
        p = *(void **)((u8 *)arg1 + 0x14);
        if (p != NULL) {
            r = NpcTalkTextRequest_41de00(h, *(s16 *)((u8 *)arg1 + 6), *(s16 *)((u8 *)p + 0xC));
        } else {
            r = 0;
        }
        return r;
    }
    return 1;
}
