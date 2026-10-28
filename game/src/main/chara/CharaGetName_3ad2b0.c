/* rgp:protos */
#define RGP_SELF_CharaGetName_3ad2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern char *strcpy(char *, const char *);

void CharaGetName_3ad2b0(void *arg0, char *arg1) {
    void *t;

    if (arg1 == 0 || (t = *(void **)((u8 *)arg0 + 0x230)) == 0) {
        return;
    }
    strcpy(arg1, *(char **)((u8 *)t + 4));
}
