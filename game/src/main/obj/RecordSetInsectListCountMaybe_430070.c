/* rgp:protos */
#define RGP_SELF_RecordSetInsectListCountMaybe_430070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s32 unk8;
} Obj1188;

typedef struct {
    u8 pad0[0x1188];
    Obj1188 *unk1188;
} Obj0Arg0;

typedef struct {
    u8 padD[0xD];
    s8 unkD;
    s8 unkE;
} Elem1;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
} Elem2;

typedef struct {
    u8 pad0[0xF0];
    s32 unkF0;
} Elem3;

/*rgp*/
/*rgp*/
/*rgp*/

void RecordSetInsectListCountMaybe_430070(Obj0Arg0 *arg0, s32 arg1, s32 arg2)
{
    s32 kind;
    Elem1 *e1;
    Elem2 *e2;
    Elem3 *e3;

    kind = arg0->unk1188->unk8;
    e1 = ((Elem1 *)RecordGetPayloadIfKind1E_430b70(arg0));
    if (e1 != NULL) {
        if (kind == 0x12F) {
            e1->unkD = arg1;
        } else if (kind == 0x130) {
            e1->unkE = arg1;
        } else if ((u32)(kind - 0x131) < 2U) {
            (&e1->unkD)[arg2] = arg1;
        }
        return;
    }
    e2 = ((Elem2 *)RecordGetPayloadIfKind28_430b50(arg0));
    if (e2 != NULL) {
        if (kind == 0x192 || (u32)(kind - 0x194) < 2U) {
            e2->unk10 = arg1;
        }
        return;
    }
    e3 = ((Elem3 *)RecordGetPayloadIfKind3D_430af0(arg0));
    if (e3 != NULL && (u32)(kind - 0x265) < 2U) {
        e3->unkF0 = arg1;
    }
}
