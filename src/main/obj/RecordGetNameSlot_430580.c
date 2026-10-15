#include "types.h"

typedef struct {
    u8 pad0[0x1188];
    struct { u8 pad0[8]; s32 unk8; } *unk1188;
} Obj00430580;

s32 RecordGetPayloadIfKind3D_430af0(Obj00430580 *);                    /* extern */
s32 RecordGetPayloadIfKind3C_430b10(Obj00430580 *);                    /* extern */
s32 RecordGetPayloadIfKind32_430b30(Obj00430580 *);                    /* extern */
s32 RecordGetPayloadIfKind28_430b50();                                 /* extern */

s32 RecordGetNameSlot_430580(Obj00430580 *arg0, s32 arg1) {
    s32 temp_17;
    s32 p;
    s32 v;

    temp_17 = arg0->unk1188->unk8;
    p = RecordGetPayloadIfKind28_430b50();
    if (p != 0) {
        if ((u32) (temp_17 - 0x193) < 3U) {
            v = p + 0x270;
        } else {
            v = 0;
        }
        return v;
    }
    p = RecordGetPayloadIfKind32_430b30(arg0);
    if (p != 0) {
        if (temp_17 == 0x1F6) {
            return p + 0x10;
        }
        if (temp_17 == 0x1F7) {
            return p + 0xF0;
        }
        if ((u32) (temp_17 - 0x194) < 2U) {
            v = p + (arg1 * 0xE0) + 0x10;
        } else {
            v = 0;
        }
        return v;
    }
    p = RecordGetPayloadIfKind3C_430b10(arg0);
    if (p != 0) {
        if ((u32) (temp_17 - 0x25B) < 3U) {
            v = p + 0xC;
        } else {
            v = 0;
        }
        return v;
    }
    p = RecordGetPayloadIfKind3D_430af0(arg0);
    if (p != 0) {
        if ((u32) (temp_17 - 0x266) < 3U) {
            v = p + 0xC;
        } else {
            v = 0;
        }
        return v;
    }
    return 0;
}
