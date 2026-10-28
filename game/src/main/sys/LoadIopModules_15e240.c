/* rgp:protos */
#define RGP_SELF_LoadIopModules_15e240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

extern u8 D_00458B50[];
extern u8 D_00458B68[];
extern u8 D_00458B78[];
extern u8 D_00458B88[];
extern u8 D_00458B98[];
extern u8 D_00458BA8[];
extern u8 D_00458BB8[];
extern u8 D_00458BC8[];
extern u8 D_00458BD8[];
extern u8 D_00458BE8[];
extern u8 D_00458BF8[];
extern u8 D_00458C08[];
extern u8 D_00458C18[];
extern u8 D_00458C28[];
extern u8 D_00458C38[];
extern u8 D_00458C48[];
extern u8 D_00458C60[];
extern u8 D_00458C78[];
extern u8 D_00458C90[];
extern u8 D_00458CA8[];

void LoadIopModules_15e240(void) {
    void *base;

    base = D_00458B50;
    IopLoadModuleRetry_15e420(D_00458B68, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458B78, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458B88, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458B98, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458BA8, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458BB8, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458BC8, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458BD8, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458BE8, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458BF8, base, 1, 0, NULL);
    IopLoadModuleRetry_15e420(D_00458C08, base, 1, 0xC, D_00458C18);
    IopLoadModuleRetry_15e420(D_00458C28, base, 1, 0xC, D_00458C38);
    IopLoadModuleRetry_15e420(D_00458C48, base, 1, 0x16, D_00458C60);
    IopLoadModuleRetry_15e420(D_00458C78, base, 1, 0x16, D_00458C90);
    IopLoadModuleRetry_15e420(D_00458CA8, base, 1, 0, NULL);
}
