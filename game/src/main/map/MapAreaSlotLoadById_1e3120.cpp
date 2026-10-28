/* rgp:protos */
#line 1
#include "types.h"

/* C++ VIRTUAL: vptr +0, slot 0x70 = virtual #26, taking an s16.
   NOTE this image passes the 5th and 6th arguments in $8/$9, so MapAreaSlotLoad_1e2fd0
   really takes SIX. [[levers.d/jalr-is-cpp-virtual]]. */

class VE1E3120;
class VE1E3120 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v26(s16 a) { return VCM(void *, (void *, s16), 0x70, a); }
};
extern "C" {
void *GetGameData_1fede0(void);
int MapAreaSlotLoad_1e2fd0(s32, s32, void *, s32, s32, s32);
}

extern "C" int MapAreaSlotLoadById_1e3120(s32 arg0, s32 arg1, s64 arg2, s32 arg3, s32 arg4)
{
    VE1E3120 *self;
    void *p;

    self = *(VE1E3120 **)((u8 *)*(void **)((u8 *)*(void **)((u8 *)GetGameData_1fede0() + 8) + 0x34) + 8);
    p = self->v26((s16)arg2);
    return MapAreaSlotLoad_1e2fd0(arg0, arg1, p, arg3, arg4, -1);
}
