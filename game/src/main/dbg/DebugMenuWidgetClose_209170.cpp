/* rgp:protos */
#line 1
#include "types.h"

class VE {
public:
    u8 pad00[0x2A];
    u16 unk2A;
    VC_VPTR_MEMBER;
    
    
    void v3() { VCM0(void, 0x14); }
    
    
    void v6(u16 a0) { VCM(void, (void *, u16), 0x20, a0); }
};

extern "C" void *DebugMenuWidgetGetCurrentChild_209dd0(VE *);
extern "C" s32 DebugMenuWidgetIsStickyMaybe_209df0(int);

/* MATCH: retail's `daddiu $16,0,1` needs the flag REGISTER-RESIDENT u16
   (per [[mwcc-daddiu-unsigned-narrow]]), which needs THREE things together:
   the parameter itself u16, the guard spelled as a bare truth test (`arg1`,
   not `arg1 != 0` -- the andi re-narrow escape), and the virtual callee
   v6 declared u16 too (the call-site promotion escape). Any one or two of
   these alone cost a length-changing extra word; s20 tried pairs, not all
   three together. */
extern "C" void DebugMenuWidgetClose_209170(VE *arg0, u16 arg1)
{
    VE *temp_2;

    if (arg0->unk2A & 0x40) {
        if (arg1 || (((unsigned char)DebugMenuWidgetIsStickyMaybe_209df0((int)arg0)) == 0)) {
            arg0->v3();
            arg1 = 1;
        }
        temp_2 = (VE *)DebugMenuWidgetGetCurrentChild_209dd0(arg0);
        if (temp_2 != NULL) {
            temp_2->v6(arg1);
        }
    }
}
