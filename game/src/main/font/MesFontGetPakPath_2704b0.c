/* rgp:protos */
#define RGP_SELF_MesFontGetPakPath_2704b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern char D_0045F640[];
extern char D_0045F660[];
extern u8 D_004820B8;

extern void Sprintf_1343b8(void *dst, const char *fmt);
extern char *strcpy(char *dst, const char *src);

void MesFontGetPakPath_2704b0(s32 kind, void *buf)
{
    if (buf == NULL) {
        return;
    }
    D_004820B8 = kind;
    switch (kind) {
    case 0:
        strcpy((char *)buf, D_0045F640);
        return;
    default:
    case 1:
        Sprintf_1343b8(buf, D_0045F660);
        break;
    }
}
