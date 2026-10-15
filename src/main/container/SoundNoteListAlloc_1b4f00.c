#include "types.h"

typedef struct Obj_FUN_001b4f00 {
    s32 f00;
    void *f04;
} Obj_FUN_001b4f00;

extern void *MemStackNew_14e1b0(s32 sz, s32 tag);
extern void *ConstructNewArray_100710(void *m, void *f, s32 b, s32 c, s32 d);
extern void SoundNoteCtor_1b4f90(void);

s32 SoundNoteListAlloc_1b4f00(Obj_FUN_001b4f00 *o, s32 n, s32 tag)
{
    void *m;

    if (tag == 0) {
        return 0;
    }
    m = MemStackNew_14e1b0(n * 20 + 0x10, tag);
    o->f04 = ConstructNewArray_100710(m, (void *)SoundNoteCtor_1b4f90, 0, 0x14, n);
    if (o->f04 == 0) {
        return 0;
    }
    o->f00 = n;
    return 1;
}
