/* rgp:protos */
#define RGP_SELF_TreasureBoxResolveRec_33b180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub0033b180 {
    u8 pad00[0x78];
    s32 unk78;
} Sub0033b180;

typedef struct Base0033b180 {
    u8 pad0[0x8];
    Sub0033b180 *unk8;
} Base0033b180;

typedef struct Obj0033b180 {
    u8 pad00[0x20];
    s16 unk20;
    s16 unk22;
    u8 pad24[0x68 - 0x24];
    s32 unk68;
} Obj0033b180;

/*rgp*/
/*rgp*/

s32 TreasureBoxResolveRec_33b180(Obj0033b180 *arg0)
{
    Base0033b180 *base;
    s32 result;

    base = GetGameData_1fede0();
    if (base == NULL) {
        return 0;
    }
    result = GroupGetRecordById_426dc0(base->unk8->unk78, arg0->unk20, arg0->unk22);
    arg0->unk68 = result;
    if (result != 0) {
        return result;
    }
    return 0;
}
