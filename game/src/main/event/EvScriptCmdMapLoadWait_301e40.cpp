/* rgp:protos */
#line 1
#include "types.h"

/* PARK: RIGHT LENGTH (34 words), 2 bad.  Fixed this session: the vtable
   call is a real C++ virtual (vptr 0xDC, slot 8 = index 0) and the first two
   guards must be EARLY RETURNS (the nested form is 2 words short).
   Residue: retail's `b <tail>` has an EMPTY delay slot and the shared
   `li v0,1` sits at the join; mwcc sinks the `li v0,1` into the branch and
   jumps straight to the epilogue.  Eight shapes (goto/else/nested,
   both == 4 and != 4 polarities) are two objects at 32 and 34 words. */
class VE301 {
public:
    u8 pad000[0xDC];
    VC_VPTR_MEMBER; s32 v0() { return VCM0(s32, 0x8); }
};

struct Arg301 { u8 pad0[4]; VE301 *unk4; };

extern "C" s32 MapLoadIsSettledMaybe_1e4e10(s32, s32);
extern "C" s32 GetMapMgr_201a90(void);
extern "C" void EvObjLiftStallFrame_335a00(VE301 *);

extern "C" s32 EvScriptCmdMapLoadWait_301e40(Arg301 *arg0, s32 arg1, s32 arg2) {
    VE301 *temp_16;

    if (arg2 != 0) {
        return 1;
    }
    if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(GetMapMgr_201a90(), 0)) != 0) {
        return 1;
    }
    temp_16 = arg0->unk4;
    if (temp_16 != NULL) {
        switch (temp_16->v0()) {
        case 4:
            EvObjLiftStallFrame_335a00(temp_16);
        }
    }
    return 1;
}
