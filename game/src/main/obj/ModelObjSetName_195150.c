/* rgp:protos */
#define RGP_SELF_ModelObjSetName_195150 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode on

extern void strcpy(void *, const char *);
extern u32 strlen(const char *);

void ModelObjSetName_195150(void *arg0, const char *arg1) {
    if (arg1 == NULL) {
        return;
    }
    if (strlen(arg1) > 0x1FU) {
        return;
    }
    strcpy((u8 *)arg0 + 0x6C, arg1);
}
