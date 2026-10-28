#include "types.h"
typedef rg_u128 u128;

typedef struct V4 { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct Chr { u8 pad0[0x180]; V4 pos; u8 pad190[0x33C]; f32 m4CC; } Chr;

class Obj {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v094(V4 * a0) { VCM(void, (void *, V4 *), 0x94, a0); }
    void v098(V4 * a0) { VCM(void, (void *, V4 *), 0x98, a0); }
    u8 padC4[0x13C];
    f32 m200;
    f32 m204;
    f32 m208;
    u8 pad20C[0x6C];
    s32 m278;
    s32 m27C;
    u8 m280;
    u8 pad281[0xF];
    V4 m290;
};

extern "C" {
extern void VecNormalize_13bd90(V4 *, V4 *);
extern void VecScale_13be00(V4 *, V4 *, f32);
extern void VecSub_13be40(V4 *, V4 *, V4 *);
extern f32 VecLength_13d4a0(V4 *);
extern Chr *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void CameraFollowLeaderStepMaybe_3081e0(Obj *, s32, V4 *, s32, s32, V4 *);
extern f32 D_0047D7CC;
}

extern "C" void CameraTwoTargetFollow_307b40(Obj *self, s32 id)
{
    V4 p1 __attribute__((aligned(16)));
    V4 p0 __attribute__((aligned(16)));
    V4 d __attribute__((aligned(16)));
    V4 t __attribute__((aligned(16)));
    V4 q70 __attribute__((aligned(16)));
    V4 q60 __attribute__((aligned(16)));
    V4 r __attribute__((aligned(16)));
    Chr *a;
    Chr *b;
    f32 hi;
    f32 lo;
    f32 f;
    f32 af;

    a = ObjRecGetLiveObject_1c4a90(id, self->m278);
    b = ObjRecGetLiveObject_1c4a90(id, self->m27C);
    *(u128 *)&d = 0;
    if (self->m280 != 0) {
        if (a != 0) {
            *(u128 *)&p1 = *(u128 *)&a->pos;
            *(u128 *)&p0 = *(u128 *)&self->m290;
            p0.y = p1.y;
            VecSub_13be40(&d, &p0, &p1);
            VecScale_13be00(&d, &d, 0.5f);
            t.x = self->m200;
            t.y = self->m204;
            t.z = self->m208;
            *(s32 *)&t.w = 0;
            VecSub_13be40(&d, &d, &t);
            VecScale_13be00(&d, &d, 0.0625f);
        }
    } else if (a != 0 && b != 0) {
        *(u128 *)&p1 = *(u128 *)&a->pos;
        *(u128 *)&p0 = *(u128 *)&b->pos;
        if (1.0f < a->m4CC && 1.0f < b->m4CC) {
            p1.y = p1.y + D_0047D7CC * a->m4CC;
            p0.y = p0.y + D_0047D7CC * b->m4CC;
        }
        hi = 20.0f + p1.y;
        if (hi < p0.y) {
            p0.y = hi;
        }
        lo = p1.y - 8.0f;
        if (p0.y < lo) {
            p0.y = lo;
        }
        VecSub_13be40(&d, &p0, &p1);
        if (VecLength_13d4a0(&d) < 200.0f) {
            VecScale_13be00(&d, &d, 0.5f);
            t.x = self->m200;
            t.y = self->m204;
            t.z = self->m208;
            *(s32 *)&t.w = 0;
            VecSub_13be40(&d, &d, &t);
            VecScale_13be00(&d, &d, 0.0625f);
        }
    }
    self->v098(&q70);
    self->v094(&q60);
    VecSub_13be40(&r, &q60, &q70);
    f = (VecLength_13d4a0(&r) - 70.0f) / 16.0f;
    af = (f < 0.0f) ? -f : f;
    if (af > D_0047D7CC) {
        VecNormalize_13bd90(&r, &r);
        VecScale_13be00(&r, &r, f);
    } else {
        *(u128 *)&r = 0;
    }
    CameraFollowLeaderStepMaybe_3081e0(self, id, &r, 0, 0, &d);
}
