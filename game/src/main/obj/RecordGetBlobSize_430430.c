/* rgp:protos */
#define RGP_SELF_RecordGetBlobSize_430430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[8];
    s32 id;
} Info;

typedef struct {
    u8 pad0[0x1188];
    Info *info;
} A;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u8 *RecordGetBlobSize_430430(A *arg0)
{
    s32 id;
    u8 *p;

    id = arg0->info->id;
    p = ((u8 *)RecordGetPayloadIfKind3C_430b10(arg0));
    if (p != NULL) {
        if (id == 0x25A || id == 0x25D) {
            return *(u8 **)(p + 0x17C);
        }
        return NULL;
    }
    p = ((u8 *)RecordGetPayloadIfKind28_430b50(arg0));
    if (p != NULL) {
        if ((u32)(id - 0x192) < 2) {
            return *(u8 **)(p + 0x3E4);
        }
        return NULL;
    }
    p = ((u8 *)RecordGetPayloadIfKind32_430b30(arg0));
    if (p != NULL) {
        if ((u32)(id - 0x1F6) < 2) {
            return *(u8 **)(p + 0x2F4);
        }
        return NULL;
    }
    p = ((u8 *)RecordGetPayloadIfKind3D_430af0(arg0));
    if (p != NULL) {
        if (id == 0x264 || id == 0x268) {
            return *(u8 **)(p + 0x350);
        }
        return NULL;
    }
    p = ((u8 *)RecordGetPayloadIfKind3E_430ad0(arg0));
    if (p != NULL) {
        if ((u32)(arg0->info->id - 0x26E) < 2) {
            return *(u8 **)(p + 0xC);
        }
        return NULL;
    }
    p = ((u8 *)RecordGetPayloadIfKind3F_430ab0(arg0));
    if (p != NULL) {
        if ((u32)(arg0->info->id - 0x278) < 3) {
            return *(u8 **)(p + 0xC);
        }
        return NULL;
    }
    return NULL;
}
