#include "types.h"

class C {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v65() { return VCM0(s32, 0x10C); }
    
    
    
    
    
    
    
    
    s32 v74(s32 f) { return VCM(s32, (void *, s32), 0x130, f); }
};

struct Ctx {
    u8    pad000[0x14];
    void *m14;
    u8    pad018[0x4];
    void *m1C;
};

extern "C" Ctx *GetGameData_1fede0(void);
extern "C" C *CharaMgrPoolFindById_3a8c60(void *t, s32 id);
extern "C" C *ObjFindById_3bb3a0(void *t, s32 id);

extern "C" s32 ActorGetMpById_2cd780(s32 id, s32 *out)
{
    Ctx *ctx;
    C   *o;
    s32  res;

    ctx = GetGameData_1fede0();
    res = 0;
    if (out != 0) {
        *out = 0;
    }
    if (id < 12) {
        o = CharaMgrPoolFindById_3a8c60(ctx->m14, id);
        if (o != 0) {
            res = o->v65();
            if (out != 0) {
                *out = o->v74(1);
            }
        }
    } else {
        o = ObjFindById_3bb3a0(ctx->m1C, id);
        if (o != 0) {
            res = o->v65();
            if (out != 0) {
                *out = o->v74(1);
            }
        }
    }
    return res;
}
