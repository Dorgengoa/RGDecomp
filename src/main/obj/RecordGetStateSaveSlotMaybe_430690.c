#include "types.h"

typedef struct {
    u8 pad[8];
    s32 x8;
} Sub;

typedef struct {
    u8 pad[0x1188];
    Sub *p;
} Obj;

extern s32 RecordGetPayloadIfKind3F_430ab0(Obj *);
extern s32 RecordGetPayloadIfKind3E_430ad0(Obj *);
extern s32 RecordGetPayloadIfKind3D_430af0(Obj *);
extern s32 RecordGetPayloadIfKind3C_430b10(Obj *);
extern s32 RecordGetPayloadIfKind32_430b30(Obj *);
extern s32 RecordGetPayloadIfKind28_430b50(Obj *);
extern s32 RecordGetPayloadIfKind1E_430b70(Obj *);

s32 RecordGetStateSaveSlotMaybe_430690(Obj *arg0)
{
    s32 id;
    s32 v;

    id = arg0->p->x8;
    v = RecordGetPayloadIfKind1E_430b70(arg0);
    if (v != 0) {
        if (id == 0x12F) {
            return v + 5;
        }
        if (id == 0x130) {
            return v + 9;
        }
        return 0;
    }
    v = RecordGetPayloadIfKind28_430b50(arg0);
    if (v != 0) {
        if (id == 0x192) {
            return v + 5;
        }
        if (id == 0x193) {
            return v + 9;
        }
        return 0;
    }
    v = RecordGetPayloadIfKind32_430b30(arg0);
    if (v != 0) {
        if (id == 0x1F6) {
            return v + 5;
        }
        if (id == 0x1F7) {
            return v + 9;
        }
        return 0;
    }
    v = RecordGetPayloadIfKind3C_430b10(arg0);
    if (v != 0) {
        if (id == 0x25A || id == 0x25D) {
            return v + 5;
        }
        return 0;
    }
    v = RecordGetPayloadIfKind3D_430af0(arg0);
    if (v != 0) {
        if (id == 0x264 || id == 0x268) {
            return v + 5;
        }
        if (id == 0x265) {
            return v + 0xEC;
        }
        return 0;
    }
    v = RecordGetPayloadIfKind3E_430ad0(arg0);
    if (v != 0) {
        if ((u32)(arg0->p->x8 - 0x26E) < 2) {
            return v + 5;
        }
        return 0;
    }
    v = RecordGetPayloadIfKind3F_430ab0(arg0);
    if (v != 0) {
        id = arg0->p->x8;
        if ((u32)(id - 0x278) < 2) {
            return v + 5;
        }
        if (id == 0x27A) {
            return v + 5;
        }
        return 0;
    }
    return 0;
}
