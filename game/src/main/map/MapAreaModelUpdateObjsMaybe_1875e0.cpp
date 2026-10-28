/* rgp:protos */
#line 1
#include "types.h"

struct Ctx1875 {
    f32 f;
    s32 x;
};

class Obj1875 {
public:
    u8 pad[0x68];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    void upd(Ctx1875 * a0, s32 a1) { VCM(void, (void *, Ctx1875 *, s32), 0x34, a0, a1); }
};

struct E1875 {
    s32 x0;
    u8 pad[0x3C];
};

extern "C" f32 TimeOfDayGetHour_18d920(void *);
extern "C" void FuncAnimeUpdate_191650(E1875 *, s32);
extern "C" s32 FuncDataRecIsActiveAt_192170(s32, Ctx1875 *);

extern "C" void MapAreaModelUpdateObjsMaybe_1875e0(u8 *arg0, s32 arg1)
{
    Ctx1875 c __attribute__((aligned(16)));
    s32 n;
    Obj1875 **arr;
    s32 i;
    E1875 *q;

    c.f = 0.0f;
    c.f = TimeOfDayGetHour_18d920((void *)arg0);
    c.x = *(s32 *)(arg0 + 0x1678);
    n = *(s32 *)(arg0 + 0x51C);
    arr = *(Obj1875 ***)(arg0 + 0x520);
    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->upd(&c, arg1);
        }
    }
    if (*(s32 *)(arg0 + 0x1640) <= 0 || (q = *(E1875 **)(arg0 + 0x1644)) == NULL) {
        return;
    }
    for (i = 0; i < *(s32 *)(arg0 + 0x1640); i++, q++) {
        if (q->x0 != 0) {
            if (FuncDataRecIsActiveAt_192170(q->x0, &c) != 0) {
                FuncAnimeUpdate_191650(q, arg1);
            }
        }
    }
}
