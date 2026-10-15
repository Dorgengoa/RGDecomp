#include "types.h"
/* insmenu 0x004F4230 (pass-27 window) -- clear a gp flag, return 1 */
extern s16 D_0048439C;
s32 insmenu_InsectVsTeamCommitEnterCb_4f4230(void) { D_0048439C = 0; return 1; }
