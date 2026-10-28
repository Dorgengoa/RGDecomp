/* rgp:protos */
#define RGP_SELF_FieldHudReshowMaybe_202d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub_FUN_00202d70 {
    u8 pad000[0x24C];
    u8 f24C;
} Sub_FUN_00202d70;

typedef struct Obj_FUN_00202d70 {
    u8 pad000[0x20];
    Sub_FUN_00202d70 *f20;
} Obj_FUN_00202d70;

extern u8 D_00527020[];
/*rgp*/
/*rgp*/
/*rgp*/

void FieldHudReshowMaybe_202d70(void)
{
    Obj_FUN_00202d70 *o;

    o = ((Obj_FUN_00202d70 *)GetGameData_1fede0());
    if ((o->f20->f24C & 1) != 0) {
        LeaderHudLeaderChangedThunk_503ff0();
        func_4F7A00(D_00527020);
    }
}
