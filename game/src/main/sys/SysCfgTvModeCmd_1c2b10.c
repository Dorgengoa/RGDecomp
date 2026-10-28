/* rgp:protos */
#define RGP_SELF_SysCfgTvModeCmd_1c2b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 strcmp(const char *a, const char *b);
extern char D_0045B008[];

s32 SysCfgTvModeCmd_1c2b10(void *arg0, s32 arg1) {
    if (arg1 != 1) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x0) == 0) {
        if (strcmp(*(const char **)((u8 *)arg0 + 0x4), D_0045B008) == 0) {
            SetAspectMode_1c6a90(1);
            goto gpt_return;
        }
        SetAspectMode_1c6a90(0);
        return 1;
    }
    switch (VariantGetInt_1c2bd0((void *)arg0)) {
    case 1:
        SetAspectMode_1c6a90(1);
        break;
    default:
        SetAspectMode_1c6a90(0);
        break;
    }
    goto gpt_return;

gpt_return: return 1;
}
