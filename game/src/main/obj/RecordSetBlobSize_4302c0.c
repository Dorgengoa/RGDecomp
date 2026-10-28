/* rgp:protos */
#define RGP_SELF_RecordSetBlobSize_4302c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#define RNG(x, k, n) ((u32)((x) - (k)) < (n))

typedef struct Info {
    u8 pad[8];
    s32 id;
} Info;

typedef struct Obj {
    u8 pad[0x1188];
    Info *info;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void RecordSetBlobSize_4302c0(Obj *self, s32 val)
{
    s32 id = self->info->id;
    u8 *p;
    if ((p = ((u8 *)RecordGetPayloadIfKind3C_430b10(self))) != 0) {
        if (id == 0x25A || id == 0x25D) {
            *(s32 *)(p + 0x17C) = val;
        }
        return;
    }
    if ((p = ((u8 *)RecordGetPayloadIfKind28_430b50(self))) != 0) {
        if (RNG(id, 0x192, 2)) {
            *(s32 *)(p + 0x3E4) = val;
        }
        return;
    }
    if ((p = ((u8 *)RecordGetPayloadIfKind32_430b30(self))) != 0) {
        if (RNG(id, 0x1F6, 2)) {
            *(s32 *)(p + 0x2F4) = val;
        }
        return;
    }
    if ((p = ((u8 *)RecordGetPayloadIfKind3D_430af0(self))) != 0) {
        if (id == 0x264 || id == 0x268) {
            *(s32 *)(p + 0x350) = val;
        }
        return;
    }
    if ((p = ((u8 *)RecordGetPayloadIfKind3E_430ad0(self))) != 0) {
        if (RNG(self->info->id, 0x26E, 2)) {
            *(s32 *)(p + 0xC) = val;
        }
        return;
    }
    if ((p = ((u8 *)RecordGetPayloadIfKind3F_430ab0(self))) != 0) {
        if (RNG(self->info->id, 0x278, 3)) {
            *(s32 *)(p + 0xC) = val;
        }
    }
}
