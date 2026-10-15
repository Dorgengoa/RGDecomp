#include "types.h"

typedef struct {
    u8 pad0[8];
    s32 id;
} Info;

typedef struct {
    u8 pad0[0x1188];
    Info *info;
} A;

extern u8 *RecordGetPayloadIfKind3F_430ab0(A *);
extern u8 *RecordGetPayloadIfKind3E_430ad0(A *);
extern u8 *RecordGetPayloadIfKind3D_430af0(A *);
extern u8 *RecordGetPayloadIfKind3C_430b10(A *);
extern u8 *RecordGetPayloadIfKind32_430b30(A *);
extern u8 *RecordGetPayloadIfKind28_430b50(A *);

u8 *RecordGetBlobData_430170(A *arg0)
{
    s32 id;
    u8 *p;

    id = arg0->info->id;
    p = RecordGetPayloadIfKind3C_430b10(arg0);
    if (p != NULL) {
        if (id == 0x25A || id == 0x25D) {
            return p + 0x180;
        }
        return NULL;
    }
    p = RecordGetPayloadIfKind28_430b50(arg0);
    if (p != NULL) {
        if ((u32)(id - 0x192) < 2) {
            return p + 0x3E8;
        }
        return NULL;
    }
    p = RecordGetPayloadIfKind32_430b30(arg0);
    if (p != NULL) {
        if ((u32)(id - 0x1F6) < 2) {
            return p + 0x2F8;
        }
        return NULL;
    }
    p = RecordGetPayloadIfKind3D_430af0(arg0);
    if (p != NULL) {
        if (id == 0x264 || id == 0x268) {
            return p + 0x354;
        }
        return NULL;
    }
    p = RecordGetPayloadIfKind3E_430ad0(arg0);
    if (p != NULL) {
        if ((u32)(arg0->info->id - 0x26E) < 2) {
            return p + 0x10;
        }
        return NULL;
    }
    p = RecordGetPayloadIfKind3F_430ab0(arg0);
    if (p != NULL) {
        if ((u32)(arg0->info->id - 0x278) < 3) {
            return p + 0x10;
        }
        return NULL;
    }
    return NULL;
}
