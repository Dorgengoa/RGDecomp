#pragma opt_propagation off
#include "types.h"

struct OV { u8 pad[0x98]; void *vp; };

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 *unk8;
} Obj0Arg0;

typedef struct {
    void (*unk84)(void *);
} VTab98;

class Sub {
    u8 pad[0x68];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
};

extern "C" {
extern void *MemStackNew_14e230(s32, s32);
extern void MapPartsGroupEntryCtorMaybe_189e00(u32);
extern s32 MapAreaGetRecTable_1dce90(Obj0Arg0 *);
extern void LoadHandleRelease_1dd160(u8 *);
extern s32 MapDataGetFileName_1e7be0(Obj0Arg0 *);
extern void MapAreaDataRequestFiles_1e8a70(u8 *, s32, s32, s32);
extern void FuncDataTableCtor_18fbf0(u8 *);
extern void MapSceneCfgInit_1937a0(u8 *);
extern void memset(void *, s32, s32);
extern u8 D_00470410[];
extern u8 D_00470480[];

}

class O17 {
public:
    u8 pad[0x1710];
    O17()
    {
        u8 *p;
        u8 *e;
        void *va = D_00470410;
        void *vb = D_00470480;
        ((OV *)this)->vp = va;
        p = (u8 *)this + 0x148;
        ((OV *)this)->vp = vb;
        e = (u8 *)this + 0x208;
        do {
            *(s32 *)(p + 0) = 0;
            *(s32 *)(p + 4) = 0;
            *(s32 *)(p + 8) = 0;
            p += 0xC;
        } while (p < e);
        MapSceneCfgInit_1937a0((u8 *)this + 0xA0);
        p = (u8 *)this + 0x2DC;
        do {
            MapPartsGroupEntryCtorMaybe_189e00((u32)p);
            p += 0x10;
        } while (p < (u8 *)this + 0x4DC);
        p = (u8 *)this + 0x5D0;
        e = (u8 *)this + 0xA50;
        do {
            *(s32 *)(p + 0x24) = 0;
            *(s32 *)(p + 0x20) = 0;
            *(s32 *)(p + 0x28) = 0;
            p += 0x30;
        } while (p < e);
        p = (u8 *)this + 0xA60;
        do {
            memset(p, 0, 0xC0);
            p += 0xC0;
        } while (p < (u8 *)this + 0x1660);
        FuncDataTableCtor_18fbf0((u8 *)this + 0x1694);
        ((Sub *)((u8 *)this + 0x30))->v84();
    }
    void *operator new(u32 sz, s32 a) { return MemStackNew_14e230(sz, a); }
};

extern "C" s32 MapAreaStartLoad_1d8370(Obj0Arg0 *arg0)
{
    O17 *o;
    s32 t;

    if (arg0->unk0 == 0) {
        return -1;
    }
    LoadHandleRelease_1dd160((u8 *)arg0 + 0xA8);
    o = new (arg0->unk0) O17;
    arg0->unk8 = (u8 *)o;
    if (o == 0) {
        return -1;
    }
    t = MapAreaGetRecTable_1dce90(arg0);
    MapAreaDataRequestFiles_1e8a70(arg0->unk8, t, MapDataGetFileName_1e7be0(arg0), arg0->unk0);
    return 2;
}
