/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    bool f(s32 x0, void *x1) { return (vc_u8)VCM(vc_u32, (void *, s32, void *), 0x358, x0, x1) != 0; }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * g(s16 x0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(void *, (void *, s16, int, int), 0x70, x0, rgp_fwd2, rgp_fwd3); }
};
struct Mgr {
    u8 pad[0xC];
    VC_2 *tbl;
};
extern "C" VC_1 *CharaCreateByKind_3a8e70(void *, s16);
extern "C" Mgr *D_004837F0;

extern "C" VC_1 *CharaCreateFromPcDef_3a8d80(void *arg0, s32 arg1, s32 arg2, int rgp_a3) {
    void *e;
    VC_1 *o;

    if (arg1 < 0 || arg2 < 0) {
        return NULL;
    }
    if (D_004837F0 == NULL || *(s32 *)((u8 *)arg0 + 8) == 0) {
        return NULL;
    }
    e = D_004837F0->tbl->g(arg2, (int)(long)(arg2), (int)(long)(rgp_a3));
    if (e == NULL) {
        return NULL;
    }
    if (*(s32 *)((u8 *)e + 0x30) == 0) {
        return NULL;
    }
    o = CharaCreateByKind_3a8e70(arg0, *(s16 *)((u8 *)e + 2));
    if (o == NULL) {
        return NULL;
    }
    if (o->f(arg1, e) != 0) {
        return o;
    }
    o = NULL;
    return o;
}
