#include "types.h"

class Sub {
public:
    VC_VPTR_MEMBER;
    void Init(void * a0, s32 a1, bool a2, s32 a3) { VCM(void, (void *, void *, s32, bool, s32), 0xC, a0, a1, a2, a3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Reset() { VCM0(void, 0x4C); }
};

class EA4 : public Sub {
public:
    u8 pad[0xA0];
};

class E9C : public Sub {
public:
    u8 pad[0x98];
};

class E98 : public Sub {
public:
    u8 pad[0x94];
};

class EB4 : public Sub {
public:
    u8 pad[0xB0];
};

class E2F8 : public Sub {
public:
    u8 pad[0x2F4];
};

typedef struct Res { u8 d[0x58]; } Res;

typedef struct Sys {
    Res *x0;
    u8 pad4[4];
    Sub *x8;
    Sub *xC;
    Sub *x10;
    Sub *x14;
    Sub *x18;
    Sub *x1C;
    Sub *x20;
    Sub *x24;
    Sub *x28;
    Sub *x2C;
    Sub *x30;
    Sub *x34;
    Sub *x38;
    EA4 *x3C;
    E9C *x40;
    void *x44;
    E98 *x48;
    EB4 *x4C;
    E2F8 *x50;
} Sys;

extern "C" {
extern void *ConstructNewArray_100710(void *, void *, void *, s32, s32);
extern void *MemStackNew_14e0b0(s32, void *);
extern void *MemStackNew_14e130(s32, void *);
extern void *DataTableCtor_417070(void *);
extern void *DataTableCtor_4169a0(void *);
extern void *DataTableCtor_416680(void *);
extern void *DataTableCtor_416450(void *);
extern void *DataTableCtor_415c40(void *);
extern void *DataTableCtor_415910(void *);
extern void *PlanetAreaQueryCtor_415440(void *);
extern void *DataTableCtor_4152f0(void *);
extern void *PlanetAreaMatrixQueryCtor_414f50(void *);
extern void *DataTableCtor_414e10(void *);
extern void *ZonePhaseSetQueryCtor_414aa0(void *);
extern void *DataTableCtor_414930(void *);
extern void *ZonePhaseMatrixQueryCtor_4144f0(void *);
extern void DataTableCtor_414380(void);
extern void DataTableCtor_413be0(void);
extern void *TwoTableViewCtor_4138f0(void *);
extern void DataTableCtor_413730(void);
extern void DataTableCtor_413480(void);
extern void DataTableCtor_412d50(void);
extern s32 D_00465688[];
extern s32 D_00465690[];
extern s32 D_00465698[];
extern s32 D_004656A0[];
extern s32 D_004656A8[];
extern s32 D_004656B0[];
extern s32 D_004656B8[];
extern s32 D_004656E8[];
extern s32 D_004656F0[];
extern s32 D_004656C0[];
extern s32 D_004656C8[];
extern s32 D_004656D0[];
extern s32 D_004656D8[];
extern s32 D_004656E0[];
}

extern "C" s32 WorldSubsysInit_411fb0(Sys *a, Res *heap, Res *arr) {
    void *q;
    EA4 *e3C;
    bool f;
    s32 i;
    Res *p;
    E9C *e40;
    E98 *e48;
    EB4 *e4C;
    E2F8 *e50;
    s32 i5;
    bool f5;
    Res *p5;

    if (heap == 0) {
        return 0;
    }
    a->x0 = heap;
    q = MemStackNew_14e130(0x94, a->x0);
    if (q != 0) {
        q = DataTableCtor_417070(q);
    }
    a->x8 = (Sub *)q;
    if (a->x8 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x94, a->x0);
    if (q != 0) {
        q = DataTableCtor_4169a0(q);
    }
    a->xC = (Sub *)q;
    if (a->xC == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x94, a->x0);
    if (q != 0) {
        q = DataTableCtor_416680(q);
    }
    a->x10 = (Sub *)q;
    if (a->x10 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xA0, a->x0);
    if (q != 0) {
        q = DataTableCtor_416450(q);
    }
    a->x14 = (Sub *)q;
    if (a->x14 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x94, a->x0);
    if (q != 0) {
        q = DataTableCtor_415c40(q);
    }
    a->x18 = (Sub *)q;
    if (a->x18 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x94, a->x0);
    if (q != 0) {
        q = DataTableCtor_415910(q);
    }
    a->x1C = (Sub *)q;
    if (a->x1C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, a->x0);
    if (q != 0) {
        q = PlanetAreaQueryCtor_415440(q);
    }
    a->x20 = (Sub *)q;
    if (a->x20 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x94, a->x0);
    if (q != 0) {
        q = DataTableCtor_4152f0(q);
    }
    a->x24 = (Sub *)q;
    if (a->x24 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, a->x0);
    if (q != 0) {
        q = PlanetAreaMatrixQueryCtor_414f50(q);
    }
    a->x28 = (Sub *)q;
    if (a->x28 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x94, a->x0);
    if (q != 0) {
        q = DataTableCtor_414e10(q);
    }
    a->x2C = (Sub *)q;
    if (a->x2C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, a->x0);
    if (q != 0) {
        q = ZonePhaseSetQueryCtor_414aa0(q);
    }
    a->x30 = (Sub *)q;
    if (a->x30 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x94, a->x0);
    if (q != 0) {
        q = DataTableCtor_414930(q);
    }
    a->x34 = (Sub *)q;
    if (a->x24 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, a->x0);
    if (q != 0) {
        q = ZonePhaseMatrixQueryCtor_4144f0(q);
    }
    a->x38 = (Sub *)q;
    if (a->x38 == 0) {
        return 0;
    }
    a->x3C = (EA4 *)ConstructNewArray_100710(MemStackNew_14e0b0(0x158, a->x0), (void *)DataTableCtor_414380, 0, 0xA4, 2);
    if (a->x3C == 0) {
        return 0;
    }
    a->x40 = (E9C *)ConstructNewArray_100710(MemStackNew_14e0b0(0x148, a->x0), (void *)DataTableCtor_413be0, 0, 0x9C, 2);
    if (a->x40 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x10, a->x0);
    if (q != 0) {
        q = TwoTableViewCtor_4138f0(q);
    }
    a->x44 = q;
    if (a->x44 == 0) {
        return 0;
    }
    a->x48 = (E98 *)ConstructNewArray_100710(MemStackNew_14e0b0(0x140, a->x0), (void *)DataTableCtor_413730, 0, 0x98, 2);
    if (a->x48 == 0) {
        return 0;
    }
    a->x4C = (EB4 *)ConstructNewArray_100710(MemStackNew_14e0b0(0x178, a->x0), (void *)DataTableCtor_413480, 0, 0xB4, 2);
    if (a->x4C == 0) {
        return 0;
    }
    a->x50 = (E2F8 *)ConstructNewArray_100710(MemStackNew_14e0b0(0x600, a->x0), (void *)DataTableCtor_412d50, 0, 0x2F8, 2);
    if (a->x50 == 0) {
        return 0;
    }
    a->x8->Init(a->x0, 0, D_00465688[0] != 0, 0);
    a->xC->Init(a->x0, 0, D_00465690[0] != 0, 0);
    a->x10->Init(a->x0, 0, D_00465698[0] != 0, 0);
    a->x14->Init(a->x0, 0, D_004656A0[0] != 0, 0);
    a->x18->Init(a->x0, 0, D_004656A8[0] != 0, 0);
    a->x1C->Init(a->x0, 0, D_004656B0[0] != 0, 0);
    a->x24->Init(a->x0, 0, D_004656B8[0] != 0, 0);
    a->x2C->Init(a->x0, 0, D_004656E8[0] != 0, 0);
    a->x34->Init(a->x0, 0, D_004656F0[0] != 0, 0);
    e3C = a->x3C;
    if (e3C != 0) {
        f = D_004656C0[0] != 0;
        for (i = 0; i < 2; i++, e3C++) {
            p = heap;
            if (arr != 0) {
                p = &arr[i];
            }
            e3C->Reset();
            e3C->Init(p, 0, f, 0);
        }
    }
    e40 = a->x40;
    if (e40 != 0) {
        f = D_004656C8[0] != 0;
        for (i = 0; i < 2; i++, e40++) {
            p = heap;
            if (arr != 0) {
                p = &arr[i];
            }
            e40->Reset();
            e40->Init(p, 0, f, 0);
        }
    }
    e48 = a->x48;
    if (e48 != 0) {
        f = D_004656D0[0] != 0;
        for (i = 0; i < 2; i++, e48++) {
            p = heap;
            if (arr != 0) {
                p = &arr[i];
            }
            e48->Reset();
            e48->Init(p, 0, f, 0);
        }
    }
    e4C = a->x4C;
    if (e4C != 0) {
        f = D_004656D8[0] != 0;
        for (i = 0; i < 2; i++, e4C++) {
            p = heap;
            if (arr != 0) {
                p = &arr[i];
            }
            e4C->Reset();
            e4C->Init(p, 0, f, 0);
        }
    }
    e50 = a->x50;
    if (e50 != 0) {
        f5 = D_004656E0[0] != 0;
        for (i5 = 0; i5 < 2; i5++, e50++) {
            p5 = heap;
            if (arr != 0) {
                p5 = &arr[i5];
            }
            e50->Reset();
            e50->Init(p5, 0, f5, 0);
        }
    }
    return 1;
}
