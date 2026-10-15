#include "types.h"

typedef struct {
    u8 pad0[4];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
} Obj00373EA0;

typedef struct {
    u8 pad0[8];
    s32 unk8;
} Sub1188_00373EA0;

typedef struct {
    u8 pad0[0x1188];
    Sub1188_00373EA0 *unk1188;
} Sub24_00373EA0;

typedef struct {
    u8 pad0[0x24];
    Sub24_00373EA0 *unk24;
} Ctx00373EA0;

Ctx00373EA0 *GetGameData_1fede0();
Obj00373EA0 *RecordGetPayloadIfKind3D_430af0(Sub24_00373EA0 *, s32);
Obj00373EA0 *RecordGetPayloadIfKind28_430b50(Sub24_00373EA0 *, s32);
Obj00373EA0 *RecordGetPayloadIfKind1E_430b70(Sub24_00373EA0 *, s32);

void InsectVsRecSetSaveLoadedFlagsMaybe_373ea0(void) {
    Ctx00373EA0 *c;
    Sub24_00373EA0 *s;
    s32 k;
    Obj00373EA0 *p;
    s32 f;
    Sub1188_00373EA0 *q;

    c = GetGameData_1fede0();
    s = c->unk24;
    k = s->unk1188->unk8;
    if (k == 0x12F) goto c12f;
    if (k == 0x130) {
c12f:
        p = RecordGetPayloadIfKind1E_430b70(s, k);
        f = c->unk24->unk1188->unk8;
        if (p != NULL) {
            f = f != 0x12F;
            if (f == 0) {
                p->b1 = 1;
            } else if (f == 1) {
                p->b2 = 1;
            }
        }
    } else if (k == 0x265) {
        p = RecordGetPayloadIfKind3D_430af0(s, k);
        if (p != NULL) {
            p->b1 = 1;
            p->b2 = 0;
            p->b3 = 0;
            p->b4 = 0;
        }
    } else if (k == 0x192) {
        p = RecordGetPayloadIfKind28_430b50(s, k);
        if (p != NULL) {
            p->b0 = 1;
        }
    }
}
