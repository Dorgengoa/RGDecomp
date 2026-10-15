#include "types.h"

extern char *strcpy(char *, const char *);

void CharaGetName_3ad2b0(void *arg0, char *arg1) {
    void *t;

    if (arg1 == 0 || (t = *(void **)((u8 *)arg0 + 0x230)) == 0) {
        return;
    }
    strcpy(arg1, *(char **)((u8 *)t + 4));
}
