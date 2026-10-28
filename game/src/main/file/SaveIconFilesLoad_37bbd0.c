/* rgp:protos */
#define RGP_SELF_SaveIconFilesLoad_37bbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x60];
    s32 unk60;
} Obj0037BBD0;

/*rgp*/
extern void strcpy(void *, void *);
extern char D_00463B30[32];

void SaveIconFilesLoad_37bbd0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 i;
    Obj0037BBD0 *p;

    i = 0;
    do {
        strcpy((void *)(arg0 + (i << 5)), D_00463B30);
        p = (Obj0037BBD0 *)(arg0 + (i * 4));
        temp_2 = ((s32)ArchiveGetFileByPath_1c2800(arg1, D_00463B30, (u8 *)p + 0x6C));
        i += 1;
        p->unk60 = temp_2;
    } while (i < 3);
}
