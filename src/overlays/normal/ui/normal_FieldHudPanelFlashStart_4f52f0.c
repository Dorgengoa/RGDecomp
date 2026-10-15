#include "types.h"
/* normal 0x004F52F0 -- stores 1.0f into a 4-byte-stride array at 0x2C0.  The
 * constant is materialised in a GPR (`lui 0x3F80`) and written with `sw`. */

typedef struct Obj { u8 pad000[0x2C0]; f32 f2C0[1]; } Obj;

extern void normal_FieldHudPanelFlashStart_4f52f0(Obj *p, s32 i);

void normal_FieldHudPanelFlashStart_4f52f0(Obj *p, s32 i)
{
    p->f2C0[i] = 1.0f;
}
