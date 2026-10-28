/* rgp:protos */
#define RGP_SELF_CharaPcBuildPath_1f4ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_FUN_001f4ef0 {
    s16 f00;
} E_FUN_001f4ef0;

extern char D_0045B8C8[];
extern char D_0045B8D8[];
/*rgp*/
extern void Sprintf_1343b8(char *d, const char *f, ...);
extern s32 strlen(const char *s);

void CharaPcBuildPath_1f4ef0(char *dst, E_FUN_001f4ef0 *e)
{
    Sprintf_1343b8(dst, D_0045B8C8, ((s32)CharaPcResNameBuildMaybe_40dc60(e)));
    dst[strlen(dst) - 1] = 0;
    Sprintf_1343b8(dst, D_0045B8D8, dst, (e->f00 - 0x4082) * 2 + 2);
}
