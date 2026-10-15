#include "types.h"

class Sub {
public:
    virtual void v08();
    virtual void Init(s32 heap, s32 a, bool b, s32 c);
};

typedef struct Obj {
    s32 heap;
    u8 pad4[4];
    Sub *m8;
    Sub *mC;
    Sub *m10;
    Sub *m14;
    Sub *m18;
    Sub *m1C;
} Obj;

extern "C" {
extern Sub *MemStackNew_14e130(s32, s32);
extern Sub *DataTableCtor_4217e0(Sub *);
extern Sub *DataTableCtor_421b60(Sub *);
extern Sub *DataTableCtor_421ee0(Sub *);
extern Sub *DataTableCtor_422320(Sub *);
extern Sub *DataTableCtor_422760(Sub *);
extern Sub *DataTableCtor_423460(Sub *);
extern s32 D_00465658[0x100];
extern s32 D_00465660[0x100];
extern s32 D_00465668[0x100];
extern s32 D_00465670[0x100];
extern s32 D_00465678[0x100];
extern s32 D_00465680[0x100];
}

extern "C" s32 StateTablesInit_421310(Obj *self, s32 heap) {
    Sub *p;

    if (heap == 0) {
        return 0;
    }
    self->heap = heap;
    p = MemStackNew_14e130(0xD0, heap);
    if (p != 0) {
        p = DataTableCtor_423460(p);
    }
    self->m8 = p;
    if (p == 0) {
        return 0;
    }
    p = MemStackNew_14e130(0xA4, self->heap);
    if (p != 0) {
        p = DataTableCtor_422760(p);
    }
    self->mC = p;
    if (p == 0) {
        return 0;
    }
    p = MemStackNew_14e130(0xA4, self->heap);
    if (p != 0) {
        p = DataTableCtor_422320(p);
    }
    self->m10 = p;
    if (p == 0) {
        return 0;
    }
    p = MemStackNew_14e130(0xA4, self->heap);
    if (p != 0) {
        p = DataTableCtor_421ee0(p);
    }
    self->m14 = p;
    if (p == 0) {
        return 0;
    }
    p = MemStackNew_14e130(0xA4, self->heap);
    if (p != 0) {
        p = DataTableCtor_421b60(p);
    }
    self->m18 = p;
    if (p == 0) {
        return 0;
    }
    p = MemStackNew_14e130(0x94, self->heap);
    if (p != 0) {
        p = DataTableCtor_4217e0(p);
    }
    self->m1C = p;
    if (p == 0) {
        return 0;
    }
    if (self->m8 != 0) {
        self->m8->Init(self->heap, 0, D_00465658[0] != 0, 0);
    }
    if (self->mC != 0) {
        self->mC->Init(self->heap, 0, D_00465660[0] != 0, 0);
    }
    if (self->m10 != 0) {
        self->m10->Init(self->heap, 0, D_00465668[0] != 0, 0);
    }
    if (self->m14 != 0) {
        self->m14->Init(self->heap, 0, D_00465670[0] != 0, 0);
    }
    if (self->m18 != 0) {
        self->m18->Init(self->heap, 0, D_00465678[0] != 0, 0);
    }
    if (self->m1C != 0) {
        self->m1C->Init(self->heap, 0, D_00465680[0] != 0, 0);
    }
    return 1;
}
