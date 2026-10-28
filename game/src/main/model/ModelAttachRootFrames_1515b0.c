/* rgp:protos */
#define RGP_SELF_ModelAttachRootFrames_1515b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x4];
    s32 unk4;
    u8 pad8[0x28 - 0x8];
    s8 unk28;
} Elem00152fd0;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x100 - 0x8];
    s32 unk100;
    s32 unk104;
    u8 pad108[0x10C - 0x108];
    s32 unk10C;
    s32 *unk110;
} Obj001515b0;

/*rgp*/
/*rgp*/

void ModelAttachRootFrames_1515b0(Obj001515b0 *arg0, s32 arg1)
{
    s32 i;
    Elem00152fd0 *e;

    arg0->unk100 = 0;
    arg0->unk4 = 0;
    if (arg0->unk110 != 0 && arg0->unk0 != 0) {
        for (i = 0; i < arg0->unk10C; i++) {
            e = ((Elem00152fd0 *)ArrayGetChecked_152fd0(arg0->unk104, arg0->unk110[i]));
            if (e == NULL) {
                continue;
            }
            if (e->unk28 == 0) {
                continue;
            }
            e->unk4 = 0;
        }
    }
    arg0->unk4 = arg1;
    if (arg0->unk110 == 0 || arg0->unk0 == 0) {
        return;
    }
    for (i = 0; i < arg0->unk10C; i++) {
        e = ((Elem00152fd0 *)ArrayGetChecked_152fd0(arg0->unk104, arg0->unk110[i]));
        if (e != NULL) {
            e->unk28 = 1;
            e->unk4 = arg1;
            FrameSetDirty_14a5e0(e);
        }
    }
}
