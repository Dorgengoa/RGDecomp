#include "types.h"

typedef struct O58 { char name[0x10]; u8 pad10[0x48]; } O58;
typedef struct O1C { u8 d[0x1C]; } O1C;
typedef struct O28 { u8 d[0x28]; } O28;
typedef struct O20 { u8 d[0x20]; } O20;
typedef struct OC { u8 d[0xC]; } OC;

typedef struct Sys {
    u8 pad0[0x4];
    s32 x4;
    O58 *x8;
    O1C *xC;
    O58 *x10;
    O58 *x14;
    O28 *x18;
    O58 *x1C;
    O20 *x20;
    O58 *x24;
    void *x28;
    O58 *x2C;
    OC *x30;
    void *x34;
    void *x38;
    void *x3C;
    void *x40;
    void *x44;
    void *x48;
    void *x4C;
    void *x50;
    void *x54;
    void *x58;
    void *x5C;
    void *x60;
    void *x64;
    void *x68;
    void *x6C;
    void *x70;
    void *x74;
    void *x78;
    void *x7C;
    void *x80;
    void *x84;
    void *x88;
    void *x8C;
    void *x90;
    void *x94;
    void *x98;
    void *x9C;
    void *xA0;
    void *xA4;
    void *xA8;
} Sys;

extern void *ConstructNewArray_100710(void *, void *, void *, s32, s32);
extern void *MemStackNew_14e0b0(s32, s32);
extern void *MemStackNew_14e130(s32, s32);
extern s32 MemStackAllocQw_14d950(s32, s32);
extern void MemStackInit_14d810(O58 *, s32, s32);
extern void MemStackHeapInit_14dee0(O58 *, s32, s32);
extern O58 *MemStackCtor_14e030(O58 *);
extern void StrCacheEntryCtor_3f3ea0(void);
extern void HandleEntryCtor_3f3ed0(void);
extern void HandleEntryCtor_3f3f00(void);
extern void HandleEntryCtor_3f3f30(void);
extern void HandleEntryInit_3f4230(O1C *);
extern void HandleEntryInit_3f4160(O28 *);
extern void HandleEntryInit_3f40a0(O20 *);
extern void WorldDataRequestInit_3f4060(void *);
extern u32 strlen(const char *);
extern char *strcpy(char *, const char *);
extern void *WorldSubsysCtor_4127d0(void *);
extern void *WorldSubsysCtor_405580(void *);
extern void *WorldSubsysCtor_428660(void *);
extern void *WorldSubsysCtor_40c660(void *);
extern void *WorldSubsysCtor_3f4560(void *);
extern void *WorldSubsysCtor_3fa160(void *);
extern void *WorldSubsysCtor_3fc420(void *);
extern void *WorldSubsysCtor_3f8150(void *);
extern void *WorldSubsysCtor_3f9410(void *);
extern void *WorldSubsysCtor_3fe3e0(void *);
extern void *WorldSubsysCtor_429510(void *);
extern void *WorldSubsysCtor_4006e0(void *);
extern void *WorldSubsysCtor_419c50(void *);
extern void *WorldSubsysCtor_40a670(void *);
extern void *WorldSubsysCtor_41c830(void *);
extern void *WorldSubsysCtor_402840(void *);
extern void *WorldSubsysCtor_425b30(void *);
extern void *WorldSubsysCtor_427340(void *);
extern void *WorldSubsysCtor_420140(void *);
extern void *WorldSubsysCtor_41e7b0(void *);
extern void *WorldSubsysCtor_40f260(void *);
extern void *WorldSubsysCtor_410c40(void *);
extern void *WorldSubsysCtor_4084e0(void *);
extern void *WorldSubsysCtor_3fd4d0(void *);
extern void *WorldSubsysCtor_406df0(void *);
extern void *WorldSubsysCtor_3ff5c0(void *);
extern void *WorldSubsysCtor_3f6a70(void *);
extern void *WorldSubsysCtor_40b460(void *);
extern void *WorldSubsysCtor_405e70(void *);
extern void *WorldSubsysCtor_424770(void *);
extern void WorldSubsysInit_411fb0(void *, s32, s32);
extern void WorldSubsysInit_4054e0(void *, s32);
extern void WorldSubsysInit_4285c0(void *, s32);
extern void WorldSubsysInit_40c5c0(void *, s32);
extern void WorldSubsysInit_3f4460(void *, s32);
extern void WorldSubsysInit_3f9fc0(void *, s32);
extern void WorldSubsysInit_3fc380(void *, s32);
extern void WorldSubsysInit_3f8060(void *, s32);
extern void WorldSubsysInit_3f9370(void *, s32);
extern void WorldSubsysInit_3fe340(void *, s32);
extern void WorldSubsysInit_429470(void *, s32);
extern void WorldSubsysInit_400570(void *, s32);
extern void WorldSubsysInit_419ae0(void *, s32);
extern void WorldSubsysInit_40a570(void *, s32);
extern void WorldSubsysInit_41c680(void *, s32, s32);
extern void WorldSubsysInit_402640(void *, s32, s32);
extern void WorldSubsysInit_425980(void *, s32, s32);
extern void WorldSubsysInit_427190(void *, s32, s32);
extern void WorldSubsysInit_41ff60(void *, s32, s32);
extern void WorldSubsysInit_41e580(void *, s32, s32);
extern void WorldSubsysInit_40efa0(void *, s32, s32);
extern void WorldSubsysInit_410b90(void *, s32, void *);
extern void WorldSubsysInit_4083d0(void *, s32, void *);
extern void WorldSubsysInit_3fd3b0(void *, s32, void *);
extern void WorldSubsysInit_406d30(void *, s32, void *);
extern void WorldSubsysInit_3ff4a0(void *, s32, void *);
extern void WorldSubsysInit_3f6890(void *, s32, void *);
extern void WorldSubsysInit_40b3b0(void *, s32, void *);
extern void WorldSubsysInit_405d50(void *, s32, void *);
extern void WorldSubsysInit_4246c0(void *, s32, void *);
extern s32 D_00464490[];
extern s32 D_00464498[];
extern s32 D_004644A0[];
extern s32 D_004644A8[];
extern s32 D_004644B0[];
extern s32 D_004644C0[];
extern s32 D_004644C8[];
extern s32 D_004644D0[];
extern s32 D_004644E0[];
extern s32 D_004644E8[];
extern s32 D_004644F0[];
extern char D_00466D40[];
extern char D_00466D50[];
extern char D_00466D60[];
extern char D_00466D70[];
extern char D_00466D80[];

#define SETNAME(o, s) { char *d_ = (o)->name; if (strlen(s) < 0x10) strcpy(d_, s); }

s32 WorldDataMgrInit_3f3060(Sys *a, s32 heap) {
    s32 i1;
    s32 id;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r;
    s32 i;
    s32 n;
    s32 id2;
    O58 *p;
    void *q;
    s32 i0;
    s32 r1;
    O58 *p1;
    s32 n1;
    s32 ida;
    s32 idb;
    s32 n2;
    s32 i2;
    s32 n3;
    s32 i3;
    O58 *p3;
    s32 n4;
    s32 i4;
    s32 n5;

    if (heap == 0) {
        return 0;
    }
    a->x4 = heap;
    a->x8 = (O58 *)ConstructNewArray_100710(MemStackNew_14e0b0(0xC0, a->x4), MemStackCtor_14e030, 0, 0x58, 2);
    if (a->x8 == 0) {
        return 0;
    }
    id = D_00464490[0];
    r = MemStackAllocQw_14d950(a->x4, id);
    if (r == 0) {
        return 0;
    }
    SETNAME(&a->x8[0], D_00466D40);
    MemStackInit_14d810(&a->x8[0], r, id);
    id = D_00464498[0];
    r2 = MemStackAllocQw_14d950(a->x4, id);
    if (r2 == 0) {
        return 0;
    }
    SETNAME(&a->x8[1], D_00466D40);
    MemStackInit_14d810(&a->x8[1], r2, id);
    a->xC = (O1C *)ConstructNewArray_100710(MemStackNew_14e0b0(0x48, a->x4), HandleEntryCtor_3f3f30, 0, 0x1C, 2);
    if (a->xC == 0) {
        return 0;
    }
    for (i0 = 0; i0 < 2; i0++) {
        HandleEntryInit_3f4230(&a->xC[i0]);
    }
    n1 = D_004644A8[0];
    a->x10 = (O58 *)ConstructNewArray_100710(MemStackNew_14e0b0(n1 * 0x58 + 0x10, a->x4), MemStackCtor_14e030, 0, 0x58, n1);
    if (a->x10 == 0) {
        return 0;
    }
    a->x14 = (O58 *)ConstructNewArray_100710(MemStackNew_14e0b0(n1 * 0x58 + 0x10, a->x4), MemStackCtor_14e030, 0, 0x58, n1);
    if (a->x14 == 0) {
        return 0;
    }
    ida = D_004644B0[0];
    i1 = 0;
    idb = D_004644C0[0];
    for (; i1 < n1; i1++) {
        r1 = MemStackAllocQw_14d950(a->x4, ida);
        if (r1 == 0) {
            return 0;
        }
        p1 = &a->x10[i1];
        SETNAME(p1, D_00466D50);
        MemStackInit_14d810(p1, r1, ida);
        r1 = MemStackAllocQw_14d950(a->x4, idb);
        if (r1 == 0) {
            return 0;
        }
        MemStackInit_14d810(&a->x14[i1], r1, idb);
    }
    n2 = D_004644A0[0];
    a->x18 = (O28 *)ConstructNewArray_100710(MemStackNew_14e0b0(n2 * 0x28 + 0x10, a->x4), HandleEntryCtor_3f3f00, 0, 0x28, n2);
    if (a->x18 == 0) {
        return 0;
    }
    for (i2 = 0; i2 < n2; i2++) {
        HandleEntryInit_3f4160(&a->x18[i2]);
    }
    n3 = D_004644D0[0];
    a->x1C = (O58 *)ConstructNewArray_100710(MemStackNew_14e0b0(n3 * 0x58 + 0x10, a->x4), MemStackCtor_14e030, 0, 0x58, n3);
    if (a->x1C == 0) {
        return 0;
    }
    for (i3 = 0; i3 < n3; i3++) {
        p3 = &a->x1C[i3];
        SETNAME(p3, D_00466D60);
        MemStackInit_14d810(p3, 0, 0);
    }
    n4 = D_004644C8[0];
    a->x20 = (O20 *)ConstructNewArray_100710(MemStackNew_14e0b0(n4 * 0x20 + 0x10, a->x4), HandleEntryCtor_3f3ed0, 0, 0x20, n4);
    if (a->x20 == 0) {
        return 0;
    }
    for (i4 = 0; i4 < n4; i4++) {
        HandleEntryInit_3f40a0(&a->x20[i4]);
    }
    p = (O58 *)MemStackNew_14e130(0x58, a->x4);
    if (p != 0) {
        p = MemStackCtor_14e030(p);
    }
    a->x24 = p;
    if (a->x24 == 0) {
        return 0;
    }
    id = D_004644E0[0];
    r3 = MemStackAllocQw_14d950(a->x4, id);
    if (r3 == 0) {
        return 0;
    }
    SETNAME(a->x24, D_00466D70);
    MemStackInit_14d810(a->x24, r3, id);
    q = MemStackNew_14e130(0x18, a->x4);
    if (q != 0) {
        WorldDataRequestInit_3f4060(q);
    }
    a->x28 = q;
    if (a->x28 == 0) {
        return 0;
    }
    WorldDataRequestInit_3f4060(a->x28);
    p = (O58 *)MemStackNew_14e130(0x58, a->x4);
    if (p != 0) {
        p = MemStackCtor_14e030(p);
    }
    a->x2C = p;
    if (a->x2C == 0) {
        return 0;
    }
    id = D_004644E8[0];
    r4 = MemStackAllocQw_14d950(a->x4, id);
    if (r4 == 0) {
        return 0;
    }
    SETNAME(a->x2C, D_00466D80);
    MemStackHeapInit_14dee0(a->x2C, r4, id);
    n5 = D_004644F0[0];
    a->x30 = (OC *)ConstructNewArray_100710(MemStackNew_14e0b0(n5 * 0xC + 0x10, a->x4), StrCacheEntryCtor_3f3ea0, 0, 0xC, n5);
    if (a->x30 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x54, heap);
    if (q != 0) {
        q = WorldSubsysCtor_4127d0(q);
    }
    a->x34 = q;
    if (a->x34 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, heap);
    if (q != 0) {
        q = WorldSubsysCtor_405580(q);
    }
    a->x38 = q;
    if (a->x38 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, heap);
    if (q != 0) {
        q = WorldSubsysCtor_428660(q);
    }
    a->x3C = q;
    if (a->x3C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, heap);
    if (q != 0) {
        q = WorldSubsysCtor_40c660(q);
    }
    a->x40 = q;
    if (a->x40 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x10, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3f4560(q);
    }
    a->x44 = q;
    if (a->x44 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x18, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3fa160(q);
    }
    a->x48 = q;
    if (a->x48 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3fc420(q);
    }
    a->x4C = q;
    if (a->x4C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x10, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3f8150(q);
    }
    a->x50 = q;
    if (a->x50 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3f9410(q);
    }
    a->x54 = q;
    if (a->x54 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3fe3e0(q);
    }
    a->x58 = q;
    if (a->x58 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xC, heap);
    if (q != 0) {
        q = WorldSubsysCtor_429510(q);
    }
    a->x5C = q;
    if (a->x5C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x14, heap);
    if (q != 0) {
        q = WorldSubsysCtor_4006e0(q);
    }
    a->x60 = q;
    if (a->x60 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x14, heap);
    if (q != 0) {
        q = WorldSubsysCtor_419c50(q);
    }
    a->x64 = q;
    if (a->x64 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x10, heap);
    if (q != 0) {
        q = WorldSubsysCtor_40a670(q);
    }
    a->x68 = q;
    if (a->x68 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0xD4, heap);
    if (q != 0) {
        q = WorldSubsysCtor_41c830(q);
    }
    a->x6C = q;
    if (a->x6C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x14, heap);
    if (q != 0) {
        q = WorldSubsysCtor_402840(q);
    }
    a->x70 = q;
    if (a->x70 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x10, heap);
    if (q != 0) {
        q = WorldSubsysCtor_425b30(q);
    }
    a->x74 = q;
    if (a->x74 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x10, heap);
    if (q != 0) {
        q = WorldSubsysCtor_427340(q);
    }
    a->x78 = q;
    if (a->x78 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x28, heap);
    if (q != 0) {
        q = WorldSubsysCtor_420140(q);
    }
    a->x7C = q;
    if (a->x7C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x2C, heap);
    if (q != 0) {
        q = WorldSubsysCtor_41e7b0(q);
    }
    a->x80 = q;
    if (a->x80 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x18, heap);
    if (q != 0) {
        q = WorldSubsysCtor_40f260(q);
    }
    a->x84 = q;
    if (a->x84 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x10, heap);
    if (q != 0) {
        q = WorldSubsysCtor_410c40(q);
    }
    a->x88 = q;
    if (a->x88 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x14, heap);
    if (q != 0) {
        q = WorldSubsysCtor_4084e0(q);
    }
    a->x8C = q;
    if (a->x8C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x18, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3fd4d0(q);
    }
    a->x94 = q;
    if (a->x94 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x1C, heap);
    if (q != 0) {
        q = WorldSubsysCtor_406df0(q);
    }
    a->x90 = q;
    if (a->x90 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x14, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3ff5c0(q);
    }
    a->x98 = q;
    if (a->x98 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x1C, heap);
    if (q != 0) {
        q = WorldSubsysCtor_3f6a70(q);
    }
    a->x9C = q;
    if (a->x9C == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x10, heap);
    if (q != 0) {
        q = WorldSubsysCtor_40b460(q);
    }
    a->xA0 = q;
    if (a->xA0 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x14, heap);
    if (q != 0) {
        q = WorldSubsysCtor_405e70(q);
    }
    a->xA4 = q;
    if (a->xA4 == 0) {
        return 0;
    }
    q = MemStackNew_14e130(0x18, heap);
    if (q != 0) {
        q = WorldSubsysCtor_424770(q);
    }
    a->xA8 = q;
    if (a->xA8 == 0) {
        return 0;
    }
    if (a->x34 != 0) {
        WorldSubsysInit_411fb0(a->x34, heap, 0);
    }
    if (a->x38 != 0) {
        WorldSubsysInit_4054e0(a->x38, heap);
    }
    if (a->x3C != 0) {
        WorldSubsysInit_4285c0(a->x3C, heap);
    }
    if (a->x40 != 0) {
        WorldSubsysInit_40c5c0(a->x40, heap);
    }
    if (a->x44 != 0) {
        WorldSubsysInit_3f4460(a->x44, heap);
    }
    if (a->x48 != 0) {
        WorldSubsysInit_3f9fc0(a->x48, heap);
    }
    if (a->x4C != 0) {
        WorldSubsysInit_3fc380(a->x4C, heap);
    }
    if (a->x50 != 0) {
        WorldSubsysInit_3f8060(a->x50, heap);
    }
    if (a->x54 != 0) {
        WorldSubsysInit_3f9370(a->x54, heap);
    }
    if (a->x58 != 0) {
        WorldSubsysInit_3fe340(a->x58, heap);
    }
    if (a->x5C != 0) {
        WorldSubsysInit_429470(a->x5C, heap);
    }
    if (a->x60 != 0) {
        WorldSubsysInit_400570(a->x60, heap);
    }
    if (a->x64 != 0) {
        WorldSubsysInit_419ae0(a->x64, heap);
    }
    if (a->x68 != 0) {
        WorldSubsysInit_40a570(a->x68, heap);
    }
    if (a->x6C != 0) {
        WorldSubsysInit_41c680(a->x6C, heap, 0);
    }
    if (a->x70 != 0) {
        WorldSubsysInit_402640(a->x70, heap, 0);
    }
    if (a->x74 != 0) {
        WorldSubsysInit_425980(a->x74, heap, 0);
    }
    if (a->x78 != 0) {
        WorldSubsysInit_427190(a->x78, heap, 0);
    }
    if (a->x7C != 0) {
        WorldSubsysInit_41ff60(a->x7C, heap, 0);
    }
    if (a->x80 != 0) {
        WorldSubsysInit_41e580(a->x80, heap, 0);
    }
    if (a->x84 != 0) {
        WorldSubsysInit_40efa0(a->x84, heap, 0);
    }
    if (a->x88 != 0) {
        WorldSubsysInit_410b90(a->x88, heap, a->x24);
    }
    if (a->x8C != 0) {
        WorldSubsysInit_4083d0(a->x8C, heap, a->x24);
    }
    if (a->x94 != 0) {
        WorldSubsysInit_3fd3b0(a->x94, heap, a->x24);
    }
    if (a->x90 != 0) {
        WorldSubsysInit_406d30(a->x90, heap, a->x24);
    }
    if (a->x98 != 0) {
        WorldSubsysInit_3ff4a0(a->x98, heap, a->x24);
    }
    if (a->x9C != 0) {
        WorldSubsysInit_3f6890(a->x9C, heap, a->x24);
    }
    if (a->xA0 != 0) {
        WorldSubsysInit_40b3b0(a->xA0, heap, a->x24);
    }
    if (a->xA4 != 0) {
        WorldSubsysInit_405d50(a->xA4, heap, a->x24);
    }
    if (a->xA8 != 0) {
        WorldSubsysInit_4246c0(a->xA8, heap, a->x24);
    }
    return 1;
}
