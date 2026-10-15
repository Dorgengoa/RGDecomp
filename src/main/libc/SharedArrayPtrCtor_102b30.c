#include "types.h"

/* MW C++ runtime: reference-counted pointer constructor (ptr, count), C-linkage form.
 *   self->ptr = p; self->count = 0;
 *   try { if (ptr) count = new s32(1); }  -- operator new (OperatorNew_100990) + null check
 *   catch (...) { delete ptr (OperatorDeleteArray_100820); throw; }
 * Built as C++ with exceptions on: the try/catch(...) is what gives mwcc its
 * frame-pointer frame (sp saved at fp+0x44, CatchInfo at fp+0x30, rethrow =
 * __throw(0,0,0), then __end__catch -- config/aliases.txt).  Retail carries no EH
 * table, so objfix drops .exceptix/.exception (config/objfix.txt).
 * Same code at -O4 and -O4,p (no toolchain row). */
#pragma cplusplus on
#pragma exceptions on

typedef struct RcPtr {
    void *ptr;
    s32 *count;
} RcPtr;

extern "C" void *OperatorNew_100990(u32 size);
extern "C" void OperatorDeleteArray_100820(void *p);

extern "C" RcPtr *SharedArrayPtrCtor_102b30(RcPtr *self, void *p)
{
    self->ptr = p;
    self->count = 0;
    try {
        if (self->ptr) {
            s32 *c = (s32 *)OperatorNew_100990(4);
            if (c) *c = 1;
            self->count = c;
        }
    } catch (...) {
        OperatorDeleteArray_100820(self->ptr);
        throw;
    }
    return self;
}
