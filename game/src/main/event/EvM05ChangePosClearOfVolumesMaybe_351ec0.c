/* rgp:protos */
#define RGP_SELF_EvM05ChangePosClearOfVolumesMaybe_351ec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xD0];
    s32 unkD0;
    u8 padD4[0xC];
    s32 unkE0[2];
    s32 unkE8;
    s32 unkEC;
} Obj00351ec0;

/*rgp*/

s32 EvM05ChangePosClearOfVolumesMaybe_351ec0(Obj00351ec0 *arg0, s32 arg1, f32 fparg0) {
    s32 *list;
    s32 ok;
    s32 var_17;
    s32 var_16;
    ok = !((arg0->unkD0 & 0x80000000) != 0);
    if (!ok) {
        return 1;
    }
    if (!(arg0->unkD0 & 0x02000000)) {
        return 1;
    }
    list = arg0->unkE0;
    if (list == NULL) {
        return 1;
    }
    var_17 = arg0->unkE8;
    for (var_16 = 0; var_16 < arg0->unkEC; var_16++, var_17 += 0x140) {
        if (EvTargetSphereInVolumes_352740(var_17, arg1, arg0->unkE0[var_16 & 1], fparg0) != 0) {
            return 0;
        }
    }
    return 1;
}
