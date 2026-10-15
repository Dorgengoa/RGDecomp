#include "types.h"

typedef struct Quad_FUN_00254a40 {
    u8 pad0[0x8];
    s32 unk8;           /* +0x8 */
    u8 pad1[0x4];
    s32 unk10;          /* +0x10 */
    u8 pad2[0x4];
    s32 unk18;          /* +0x18 */
    u8 pad3[0x4];
    s32 unk20;          /* +0x20 */
} Quad_FUN_00254a40;

s32 EventCameraIsIdle_254a40(Quad_FUN_00254a40 *arg0)
{
    if ((arg0->unk8 == 0) && (arg0->unk10 == 0) && (arg0->unk18 == 0) && (arg0->unk20 == 0)) {
        return 1;
    }
    return 0;
}
