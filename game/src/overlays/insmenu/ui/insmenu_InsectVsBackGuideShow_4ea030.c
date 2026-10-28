/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsBackGuideShow_4ea030 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EA030 -- 004EA000 with a 1.0f first float, so that literal
 * needs its own lui/mtc1 pair: 10 words instead of 9. */
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D240;
/*rgp*/
void insmenu_InsectVsBackGuideShow_4ea030(void) { UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x59, 1.0f, D_0047D240, -1.0f); }
