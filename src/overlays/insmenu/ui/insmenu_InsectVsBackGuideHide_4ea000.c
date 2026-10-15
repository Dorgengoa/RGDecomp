#include "types.h"
/* insmenu 0x004EA000 -- TAIL CALL `j func_290690` with five arguments.
 * D_0047D3D8 is gp - 0x7D98, inside the gp window, so it is NOT const; the
 * 0.0f and -1.0f are inline literals. */
extern const u8 D_004FA180[];
extern f32 D_0047D3D8;
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsBackGuideHide_4ea000(void) { func_290690(D_004FA180, 0x59, 0.0f, D_0047D3D8, -1.0f); }
