#include "types.h"
/* insmenu 0x004F5B50 (pass-27 window) -- clear a gp flag, return 1 */
extern s32 D_00484394;
s32 insmenu_InsectVsLoadConfirmEnterCb_4f5b50(void) { D_00484394 = 0; return 1; }
