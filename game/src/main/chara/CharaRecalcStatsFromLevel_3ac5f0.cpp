/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK: length 0x164 vs retail 0x14C (0x18 over) after 1 round. Not re-tried. */
#include "types.h"

extern "C" {

extern void * CharaRecFindLevelRow_401880(s32, s32, s32, int);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x38); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x3C); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0, s32 x1) { VCM(void, (void *, s32, s32), 0x4EC, x0, x1); }
};
void CharaRecalcStatsFromLevel_3ac5f0(u8 *arg0)
{
    s32 i;
    s32 j;
    u8 *r;

    *(s32 *)(arg0 + 0x14) = 0;
    *(u16 *)(arg0 + 0x18) = 0;
    for (i = 0; i < 2; i++) {
        *(s32 *)(arg0 + i * 4 + 0x1C) = 0;
        *(u16 *)(arg0 + i * 2 + 0x24) = 0;
        *(u16 *)(arg0 + i * 2 + 0x30) = 0;
        *(u16 *)(arg0 + i * 2 + 0x34) = 0;
        *(u16 *)(arg0 + i * 2 + 0x38) = 0;
    }
    for (i = 1; i <= *(u16 *)(arg0 + 0x10); i++) {
        r = (u8 *)CharaRecFindLevelRow_401880(*(s32 *)(arg0 + 0x230), i, 0, 0);
        if (r != NULL) {
            for (j = 0; j < 2; j++) {
                *(s32 *)(arg0 + j * 4 + 0x1C) += *(u16 *)(r + 4);
                *(u16 *)(arg0 + j * 2 + 0x24) += *(u16 *)(r + 6);
                { u16 *q = &*(u16 *)(arg0 + j * 2 + 0x30); *q = *q + *(u16 *)(r + 0x8); }
                { u16 *q = &*(u16 *)(arg0 + j * 2 + 0x34); *q = *q + *(u16 *)(r + 0xA); }
                { u16 *q = &*(u16 *)(arg0 + j * 2 + 0x38); *q = *q + *(u16 *)(r + 0xC); }
            }
        }
    }
    ((VC_0 *)(arg0))->f();
    ((VC_1 *)(arg0))->f();
    ((VC_2 *)(arg0))->f(0, 0);
    *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x20);
    *(u16 *)(arg0 + 0x18) = *(u16 *)(arg0 + 0x26);
}

}
