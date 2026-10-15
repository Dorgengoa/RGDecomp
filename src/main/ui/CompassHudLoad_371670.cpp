#include "types.h"
#include "vec.h"

class Sub {
    u8 pad[0xE0];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
};

typedef struct {
    u8 *obj;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Out;

extern "C" {
void ModelResRelocate_14bfd0(s32 *, s32);
u8 *ArrayGetChecked_14c5e0(s32 *, s32);
s32 ModelResGetMaterialCount_14c640(s32 *);
u8 *MemStackAllocQw_14d950(s32, u32);
u8 *MemStackNew_14e230(s32, s32);
void ModelBuildFrames_1506c0(u8 *, s32 *, s32, s32);
void ModelSetPos_151110(u8 *, u128 *);
s32 ModelGetFrame_1511f0(u8 *, s32);
s32 ModelFindFrameIndexByName_151220(u8 *, u8 *);
void ModelInit_151d50(u8 *);
void NameTableRegisterImArchive_1594d0(s32, u8 *, s32, s32, s32);
s32 NameTableFindByName_159fb0(s32, u8 *, s32);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
s32 ArchiveGetFileByPath_1c2800(s32, u8 *, u32 *);
void *memcpy(void *, void *, u32);
extern u8 D_004637E0[];
extern u8 D_004637F0[];
extern u8 D_00463800[];
extern u8 D_00463808[];
extern u8 D_0046FFA0[];
extern u8 D_0046FFC0[];
}

extern "C" void CompassHudLoad_371670(Out *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u32 size;
    u128 v;
    s32 list[2];
    s32 w;
    s32 r;
    u8 *p;
    s32 a;
    s32 b;
    u32 n;
    u8 *buf;
    s32 cnt;
    s32 i;
    u8 *e;
    u8 *o;

    w = GetDrawCtx_15de80();
    r = GetDrawCtxNameTable_15de40();
    p = MemStackNew_14e230(0x1C0, arg3);
    if (p != NULL) {
        *(u8 **)(p + 0x1B0) = D_0046FFC0;
        *(u8 **)(p + 0xF0) = D_0046FFA0;
        ((Sub *)(p + 0x10))->v10();
    }
    arg0->obj = p;
    if (p == NULL) {
        return;
    }
    a = ArchiveGetFileByPath_1c2800(arg1, D_004637E0, 0);
    b = ArchiveGetFileByPath_1c2800(arg1, D_004637F0, &size);
    arg0->unk4 = arg4;
    n = (size & 0xF) ? (size >> 4) + 1 : size >> 4;
    buf = MemStackAllocQw_14d950(arg3, n);
    if (buf != NULL) {
        memcpy(buf, (void *)b, size);
        NameTableRegisterImArchive_1594d0(r, buf, arg0->unk4, 0, 0);
    }
    arg0->unk8 = NameTableFindByName_159fb0(r, D_00463800, -1);
    list[0] = 0;
    ModelResRelocate_14bfd0(list, a);
    cnt = ModelResGetMaterialCount_14c640(list);
    for (i = 0; i < cnt; i++) {
        e = ArrayGetChecked_14c5e0(list, i);
        if (e == NULL) {
            break;
        }
        *(u8 *)(e + 0x50) = 0;
    }
    ModelInit_151d50(arg0->obj);
    ModelBuildFrames_1506c0(arg0->obj, list, w, arg3);
    v = 0;
    ModelSetPos_151110(arg0->obj, &v);
    o = arg0->obj;
    arg0->unkC = ModelGetFrame_1511f0(o, ModelFindFrameIndexByName_151220(o, D_00463808));
}
