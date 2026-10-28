/* rgp:protos */
#define RGP_SELF_MesWinCountLabelChars_24e460 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *, void *, s32);
extern s32 strlen(s8 *);
extern u8 D_0045EC38[];
extern u8 D_0045EC40[];

s32 MesWinCountLabelChars_24e460(s32 arg0)
{
    s8 *p;
    s32 n;
    s32 d;
    s8 buf[0x400] __attribute__((aligned(16)));

    n = 0;
    if ((arg0 != 0) && (MesWinGetLabelText_274e10((void *)arg0) != 0)) {
        memcpy(buf, MesWinGetLabelText_274e10(arg0), 0x400);
        p = ((s8 *)Strstr_135138(buf, D_0045EC38));
        if (p != NULL) {
            *p = 0;
            n = strlen(buf);
            for (p = buf; p != NULL; p++) {
                if ((*p == 0x20) || (*p == 0xD) || (*p == 0xA) || (*p == 9)) {
                    n -= 1;
                }
                d = StrPrefixLen_24e570(p, D_0045EC40);
                if (d > 0) {
                    n -= d;
                }
                if (*p == 0) {
                    break;
                }
            }
            n = n / 2;
        }
    }
    return n;
}
