/* rgp:protos */
#define RGP_SELF_MesWinLoadFile_265cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void memcpy(void *, void *, s32);
extern s32 D_00481F78;
extern s32 D_004BD980[];

s32 MesWinLoadFile_265cf0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp4C;
    s32 h;
    void *buf;
    void *src;

    if (arg1 == 0) {
        return 0;
    }
    if (arg2 == 0) {
        return 0;
    }
    sp4C = 0;
    if (arg0 != 0) {
        src = ArchiveGetFileByPath_1c2800(arg0, arg1, &sp4C);
    } else {
        src = FileLoadCached_26a6c0(arg1, &sp4C);
    }
    if (src == 0) return 0;
    if (arg3 >= 0) {
    h = ((s32)RecStackGetSlot_1c4330(D_00481F78, D_004BD980[arg3]));
    MemStackAlign64_14d8e0(h);
    buf = MemStackAllocAligned64_14da10(h, sp4C / 16 + 1);
    if (buf == 0) return 0;
    memcpy(buf, src, sp4C);
    MesWinSetTextFile_274e50(arg2, buf, sp4C);
    return 1;
    }
    return 0;
}
