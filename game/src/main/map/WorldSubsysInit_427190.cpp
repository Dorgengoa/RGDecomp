/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    void v1(void *p, s32 z, s32 f, s32 z2) { VCM(void, (void *, void *, s32, s32, s32), 0xC, p, z, f, z2); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v17() { VCM0(void, 0x4C); }
};

struct This {
    void *m00;
    u8    pad04[0x4];
    Obj  *m08;
    Obj  *m0C;
};

extern "C" s32   D_004644A8;
extern "C" void *const D_004657F8;
extern "C" void *const D_00465800;

extern "C" void * MemStackNew_14e130(s32, void *);
extern "C" void *DataTableCtor_427e20(void *p);
extern "C" void *MemStackNew_14e0b0(s32 size, void *tag);
extern "C" void *ConstructNewArray_100710(void *mem, void *fn, s32 z, s32 stride, s32 n);
extern "C" void  DataTableCtor_427a30();

extern "C" s32 WorldSubsysInit_427190(This *self, void *a, u8 *b)
{
    void *t;
    void *m;
    Obj  *e;
    s32   i;
    s32   flag;
    void *arg;
    s32   n;

    if (a == 0) return 0;
    self->m00 = a;
    t = MemStackNew_14e130(0xA0, (void *)a);
    if (t != 0) t = DataTableCtor_427e20(t);
    self->m08 = (Obj *)t;
    if (t == 0) return 0;
    n = D_004644A8;
    m = ConstructNewArray_100710(MemStackNew_14e0b0(n * 0x98 + 0x10, self->m00),
                     (void *)DataTableCtor_427a30, 0, 0x98, n);
    self->m0C = (Obj *)m;
    if (m == 0) return 0;
    if (self->m08 != 0) {
        self->m08->v1(self->m00, 0, D_004657F8 != 0, 0);
    }
    e = self->m0C;
    if (e == 0) goto done;
    flag = D_00465800 != 0;
    for (i = 0; i < n; i++, e = (Obj *)((u8 *)e + 0x98)) {
        arg = a;
        if (b != 0) arg = (void *)(b + i * 88);
        e->v17();
        e->v1(arg, 0, flag, 0);
    }
done:
    return 1;
}
