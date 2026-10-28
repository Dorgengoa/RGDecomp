/* rgp:protos */
#define RGP_SELF_ScriptFnStateFlag2Set_3d9bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct H_003d9bf0 {
    u8 pad000[0x10];
    void *f10;
} H_003d9bf0;

extern H_003d9bf0 *D_00483960;
extern s32 D_00483964;

/*rgp*/
/*rgp*/

void ScriptFnStateFlag2Set_3d9bf0(void *a0, s32 *a1)
{
    if (a0 == 0 || a1 == 0) {
        return;
    }
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    StateFlag2Set_3cc6d0(D_00483960->f10, *a1, ((signed char)VariantGetS8_36fe50((void *)a0)) != 0);
}
