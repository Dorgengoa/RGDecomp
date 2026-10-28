/* MATCH (s41m). Stale pre-match note follows -- PARK: RIGHT LENGTH (33 words), 2 bad -- the SAME residue as its twin
   EvScriptCmdMapLoadWait_301e40 (see that file).  Fixed here: three parameters (retail reads
   the flag from $a2), the C++ virtual (vptr 0xDC, slot 8 = index 0), and the
   two guards as EARLY RETURNS. */
#include "types.h"

class VE301D {
public:
    u8 pad000[0xDC];
    VC_VPTR_MEMBER; s32 v0() { return VCM0(s32, 0x8); }
};

struct Arg301D { u8 pad0[4]; VE301D *unk4; };

extern "C" s32 LoaderCountQueued_1cd620(s32);
extern "C" s32 GetLoaderMgr_1f59d0(void);
extern "C" void EvObjLiftStallFrame_335a00(VE301D *);

extern "C" s32 EvScriptCmdBgLoadWait_301ed0(Arg301D *arg0, s32 arg1, s32 arg2) {
    VE301D *temp_16;

    if (arg2 != 0) {
        return 1;
    }
    if (LoaderCountQueued_1cd620(GetLoaderMgr_1f59d0()) <= 0) {
        return 1;
    }
    temp_16 = arg0->unk4;
    if (temp_16 != NULL) {
        switch (temp_16->v0()) {
        case 4:
            EvObjLiftStallFrame_335a00(temp_16);
            break;
        }
    }
    return 1;
}
