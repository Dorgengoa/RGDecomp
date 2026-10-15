/* PARK s16d: 1 round trip, length 0x1A0 vs retail 0x194 (3 words over). */
#include "types.h"

extern void WorldSubsysSetupNop_3f6550(s32);
extern void WorldSubsysSetupRankingRecs_3fd160(s32);
extern void WorldSubsysSetupLinkAll_3ff360(s32);
extern void WorldSubsysSetupLinkAll_405c40(s32);
extern void WorldSubsysSetupGama_406bd0(s32);
extern void WorldSubsysSetupLinkAll_4081b0(s32);
extern void WorldSubsysSetupLinkAll_4081e0(s32);
extern void WorldSubsysSetupLinkAll_40b2f0(s32);
extern void WorldSubsysSetupNop_410af0(s32);
extern void WorldSubsysSetupShopRows_424500(s32);

s32 WorldDataMgrSetupPurpose_3f0450(void *arg0)
{
    s16 *p28;
    s32 v88;
    s32 v8c;
    s32 v94;
    s32 v90;
    s32 v98;
    s32 v9c;
    s32 va0;
    s32 va4;
    s32 va8;

    p28 = *(s16 **)((u8 *)arg0 + 0x28);
    if (p28 == NULL) {
        return 0;
    }
    v88 = *(s32 *)((u8 *)arg0 + 0x88);
    if (v88 != 0 && *p28 == 0) {
        WorldSubsysSetupNop_410af0(v88);
    }
    v8c = *(s32 *)((u8 *)arg0 + 0x8C);
    if (v8c != 0) {
        if (*p28 == 1) {
            WorldSubsysSetupLinkAll_4081e0(v8c);
        } else if (*p28 == 8) {
            WorldSubsysSetupLinkAll_4081b0(v8c);
        }
    }
    v94 = *(s32 *)((u8 *)arg0 + 0x94);
    if (v94 != 0 && *p28 == 2) {
        WorldSubsysSetupRankingRecs_3fd160(v94);
    }
    v90 = *(s32 *)((u8 *)arg0 + 0x90);
    if (v90 != 0 && *p28 == 3) {
        WorldSubsysSetupGama_406bd0(v90);
    }
    v98 = *(s32 *)((u8 *)arg0 + 0x98);
    if (v98 != 0 && *p28 == 4) {
        WorldSubsysSetupLinkAll_3ff360(v98);
    }
    v9c = *(s32 *)((u8 *)arg0 + 0x9C);
    if (v9c != 0 && *p28 == 5) {
        WorldSubsysSetupNop_3f6550(v9c);
    }
    va0 = *(s32 *)((u8 *)arg0 + 0xA0);
    if (va0 != 0 && *p28 == 6) {
        WorldSubsysSetupLinkAll_40b2f0(va0);
    }
    va4 = *(s32 *)((u8 *)arg0 + 0xA4);
    if (va4 != 0 && *p28 == 7) {
        WorldSubsysSetupLinkAll_405c40(va4);
    }
    va8 = *(s32 *)((u8 *)arg0 + 0xA8);
    if (va8 != 0 && *p28 == 8) {
        WorldSubsysSetupShopRows_424500(va8);
    }
    return 1;
}
