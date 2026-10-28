/* rgp:protos */
#define RGP_SELF_MemcardBuildSavePath_376380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void Sprintf_1343b8(void *, const void *, s32);
extern char *strcat(char *, const char *);
extern char *strcpy(char *, const char *);
extern u8 D_00463A00[];

void MemcardBuildSavePath_376380(s32 arg0, char *arg1) {
    char spB0[0x80] __attribute__((aligned(16)));
    char sp30[0x80] __attribute__((aligned(16)));

    Sprintf_1343b8(spB0, D_00463A00, arg0);
    Sprintf_1343b8(sp30, D_00463A00, arg0);
    if (arg1 != 0) {
        strcpy(arg1, spB0);
        strcat(arg1, sp30);
    }
}
