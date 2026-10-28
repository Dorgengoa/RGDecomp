/* rgp:protos */
#define RGP_SELF_MakeCdPath_17fe90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern char D_0049B6D0[];
extern char D_00459720[];
extern char D_00459728[];

extern u32 strlen(const char *s);
extern char *strcpy(char *d, const char *s);
extern char *strcat(char *d, const char *s);

void MakeCdPath_17fe90(const char *s)
{
    if (strlen(s) < 0x38) {
        D_0049B6D0[0] = 0;
    }
    strcpy(D_0049B6D0, D_00459720);
    strcat(D_0049B6D0, s);
    strcat(D_0049B6D0, D_00459728);
}
