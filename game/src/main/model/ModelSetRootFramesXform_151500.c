/* rgp:protos */
#define RGP_SELF_ModelSetRootFramesXform_151500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x100];
    s32 unk104;
    u8 pad108[4];
    s32 unk10C;
    s32 *unk110;
} S151500;

/*rgp*/
/*rgp*/

void ModelSetRootFramesXform_151500(S151500 *self, s32 arg1)
{
    s32 i;
    s32 r;

    if (self->unk110 == 0 || self->unk0 == 0 || arg1 == 0) {
        return;
    }
    for (i = 0; i < self->unk10C; i++) {
        r = ArrayGetChecked_152fd0(self->unk104, self->unk110[i]);
        if (r != 0) {
            FrameCopyXform_148ae0(arg1, r);
        }
    }
}
