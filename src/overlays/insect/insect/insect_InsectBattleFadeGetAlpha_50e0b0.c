#include "types.h"
/* insect 0x0050E0B0 -- 84 bytes, 21 instructions, a leaf with no frame.
 * The `bltzl` / `srl 1` / `andi 1` / `or` / `cvt.s.w` / `add.s x,x` chain is
 * mwcc's INLINE UNSIGNED-int-to-float conversion (cvt.s.w is signed), so the
 * expression being converted has type u32, not the u8 that `lbu` loads.
 */

typedef struct Obj {
    u8  pad0000[0x5EEF];
    u8  m5EEF[1];                   /* +0x5EEF */
} Obj;

f32 insect_InsectBattleFadeGetAlpha_50e0b0(Obj *o, s32 i)
{
    return (f32)(u32)o->m5EEF[i] / 128.0f;
}
