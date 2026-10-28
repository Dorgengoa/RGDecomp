/* rgp:protos */
#line 1
#include "types.h"

class Node43C {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v274() { VCM0(void, 0x274); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v43C(void * a0, s32 a1, s32 a2) { VCM(void, (void *, void *, s32, s32), 0x43C, a0, a1, a2); }
};
class Node494 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v274() { VCM0(void, 0x274); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v43C() { VCM0(void, 0x43C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v494(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x494, a0, a1, a2); }
};
class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v274(s32 a0) { return VCM(s32, (void *, s32), 0x274, a0); }
};

typedef struct Self { u8 pad0[0x424]; s16 m424; u8 pad426[0x602]; u8 mA28; u8 padA29[0xD]; s16 mA36; } Self;

extern "C" {
extern Node43C * ActorCastToUnit_3b8770(Obj *, int, int, int);
extern Node494 * ActorCastToChara_3b87b0(Obj *, int, int, int);
}

extern "C" s32 CharaUseActionGaugeOnce_214010(Self *self, Obj *obj, void *arg2)
{
    s32 r;
    Node43C *n;
    Node494 *m;

    if (obj == 0) {
        return 0;
    }
    r = obj->v274(-1) & 0xFF;
    if (self->mA28 != 0) {
        return r;
    }
    if (self->m424 >= 0 && self->m424 < 12) {
        switch (self->mA36) {
        case 7:
        case 9:
        case 12:
            m = ActorCastToChara_3b87b0(obj, 0, 0, 0);
            if (m != 0) {
                m->v494(0, 0, -1);
            }
            break;
        case 8:
        case 10:
            m = ActorCastToChara_3b87b0(obj, 0, 0, 0);
            if (m != 0) {
                m->v494(1, 0, -1);
            }
            break;
        case 11:
            break;
        case 13:
        case 14:
            if (self->m424 != 6) {
                m = ActorCastToChara_3b87b0(obj, 0, 0, 0);
                if (m != 0) {
                    m->v494(0, 0, -1);
                }
            } else {
                m = ActorCastToChara_3b87b0(obj, 0, 0, 0);
                if (m != 0) {
                    m->v494(1, 0, -1);
                }
            }
            break;
        }
    } else {
        n = ActorCastToUnit_3b8770(obj, 0, 0, 0);
        if (n != 0) {
            n->v43C(arg2, 0, -1);
        }
    }
    self->mA28 = 1;
    return r;
}
