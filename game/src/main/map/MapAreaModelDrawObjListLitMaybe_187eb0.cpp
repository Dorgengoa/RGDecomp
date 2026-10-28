#include "types.h"

/* jalr $25: the vptr lands at +0x68 of the element, so the class carries
   0x68 bytes before its first virtual.  Slot = 8 + 4*index. */
struct E {
    u8  pad000[0x32];
    s16 m32;
    u8  pad034[0x68 - 0x34];
    VC_VPTR_MEMBER;
    
    
    
    
    void v5(f32 f) { VCM(void, (void *, f32), 0x1C, f); }
    
    
    void v8() { VCM0(void, 0x28); }
};

struct Self {
    u8   pad000[0x524];
    s32  m524;
    E  **m528;
};

extern "C" void NodeObjIsInView_194200(E *e);

extern "C" void MapAreaModelDrawObjListLitMaybe_187eb0(Self *self)
{
    E  **arr;
    s32  n;
    s32  i;
    E   *e;

    arr = self->m528;
    n = self->m524;
    for (i = 0; i < n; i++) {
        e = arr[i];
        if (e == 0) {
            continue;
        }
        if (e->m32 == 0) {
            continue;
        }
        NodeObjIsInView_194200(e);
        e->v5(1.0f);
        e->v8();
    }
}
