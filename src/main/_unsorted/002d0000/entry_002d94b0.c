#include "types.h"

/* Eight small accessors laid out back to back (each 16-aligned); retail's
   symbol table names only the first, so the rest are extra entries _e1.._e7. */

typedef struct Obj {
    u8 pad000[0x1FC];
    s32 m1FC;
    u8 m200[0x3C];
    s16 m23C;
    s16 m23E;
    u8 pad240[4];
    s32 m244;
} Obj;

s32 entry_002d94b0(Obj *self) { return self->m1FC; }
s16 entry_002d94b0_e1(Obj *self) { return self->m23C; }
s16 entry_002d94b0_e2(Obj *self) { return self->m23E; }
void *entry_002d94b0_e3(Obj *self) { return self->m200; }
s32 entry_002d94b0_e4(Obj *self) { return self->m244; }
void entry_002d94b0_e5(Obj *self) { }
s32 entry_002d94b0_e6(Obj *self) { return 0; }
s32 entry_002d94b0_e7(Obj *self) { return 0; }
