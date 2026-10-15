#include "types.h"
/* insmenu 0x004EA030 -- 004EA000 with a 1.0f first float, so that literal
 * needs its own lui/mtc1 pair: 10 words instead of 9. */
extern const u8 D_004FA180[];
extern f32 D_0047D240;
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsBackGuideShow_4ea030(void) { func_290690(D_004FA180, 0x59, 1.0f, D_0047D240, -1.0f); }
