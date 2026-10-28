#include "types.h"
#undef NULL
#define NULL 0

class Tbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v70(s16 a0) { return VCM(void *, (void *, s16), 0x70, a0); }
};

struct Holder {
    u8 pad[0xC];
    Tbl *t;
};

struct Game {
    u8 pad[0x60];
    Holder *h60;
    Holder *h64;
};

extern "C" {
s32 Sprintf_1343b8(s32, const char *, ...);
Game *GetWorldDataMgr_1fedf0(void);
}
extern "C" char D_0045EA20[];
extern "C" char D_0045ED30[];

static inline bool inRange(s32 x, s32 lo, s32 hi)
{
    return x >= lo && x < hi;
}

extern "C" s32 CharaIdMakeChrPath_2501d0(s32 arg0, s32 arg1)
{
    Game *g;
    u8 *r;
    u8 *q;

    g = GetWorldDataMgr_1fedf0();
    if (inRange(arg0, 11000, 12000)) {
        r = (u8 *)g->h60->t->v70(arg0);
        if (r == NULL) {
            return 0;
        }
        q = *(u8 **)(r + 0x8);
        if (q == NULL) {
            return 0;
        }
        Sprintf_1343b8(arg1, D_0045EA20, *(s32 *)(q + 0x20));
        return 1;
    }
    if (inRange(arg0, 12000, 14000)) {
        r = (u8 *)g->h64->t->v70(arg0);
        if (r == NULL) {
            return 0;
        }
        q = *(u8 **)(r + 0x20);
        if (q == NULL) {
            return 0;
        }
        Sprintf_1343b8(arg1, D_0045ED30, *(s32 *)(q + 0xC));
        return 1;
    }
    return 0;
}
