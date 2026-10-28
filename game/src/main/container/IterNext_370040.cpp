#include "types.h"
extern "C" {

class VC_1 {
public:
    VC_VPTR_MEMBER;
    s32 f(s16 x0) { return VCM(s32, (void *, s16), 0xC, x0); }
};

typedef struct {
    VC_1 *obj;
    s16 unk4;
    s16 unk6;
} It;

static inline s32 first(It *arg0) {
    if (arg0->obj == NULL) {
        return 0;
    } else {
        if (arg0->unk4 > 0) {
            arg0->unk6 = 0;
            return arg0->obj->f(arg0->unk6);
        } else {
            arg0->unk6 = -1;
            return 0;
        }
    }
}

s32 IterNext_370040(It *arg0)
{
    if (arg0->obj == NULL) {
        return 0;
    }
    if (arg0->unk6 < 0) {
        return first(arg0);
    }
    if (arg0->unk6 < arg0->unk4 - 1) {
        arg0->unk6 = arg0->unk6 + 1;
        return arg0->obj->f(arg0->unk6);
    } else {
        return 0;
    }
}

}
