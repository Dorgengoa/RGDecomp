/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0

class Obj {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f50() { VCM0(void, 0x50); }
};

struct Desc {
    void *m0;
    void *m4;
    s32 m8;
    s32 mC;
    s32 m10;
    s32 m14;
    s32 m18;
    u8 pad1C[0x10];
    void *m2C;
    s32 m30;
    s32 m34;
    void *m38;
    s32 m3C;
    u8 buf1[0x20];
    u8 buf2[0x28];
};

struct Rd {
    s32 m0;
    s32 m4;
    s32 m8;
};

struct Ctx {
    Obj *m0;
    s32 m4;
    s32 m8;
};

struct Arg3 {
    u8 pad[0xC];
    s32 mC;
};

extern "C" {
void MapAreaTreasureBoxSlotReset_1de8f0(Ctx *);
void ModelResRelocate_14bfd0(Rd *, void *);
Obj *MemStackNew_14e130(s32, s32);
s32 CollFrameTreeBuild_16ba00(Rd *, s32);
void InfoCfgParseAll_1afd00(Obj *, Desc *);
void *ArchiveGetFileByPath_1c2800(void *, s32, s32 *);
void ModelObjExCtor_1c4920(Obj *, int, int, int);
void *memset(void *, s32, u32);
extern u8 D_0045B398[0x10];
extern u8 D_00470F50[0x400];
}

extern "C" s32 Character2NewFromInfoCfgWithColl_1de710(Ctx *arg0, void *arg1, s32 arg2, Arg3 *arg3, s32 arg4, s32 arg5)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Desc)) + (0x88) + (0x90)];
    Rd h __attribute__((aligned(16)));
    s32 cnt;
    Obj *o;
    void *p;
    s32 r;

    MapAreaTreasureBoxSlotReset_1de8f0(arg0);
    {
        if (arg1 == NULL || arg2 <= 0 || arg3 == NULL || arg4 < 0 || arg5 == 0) {
            return 0;
        }
        o = MemStackNew_14e130(0x790, arg5);
            if (o != NULL) {
                ModelObjExCtor_1c4920(o, 0, 0, 0);
                *(void **)((u8 *)o + 0x1B0) = D_00470F50;
            }
            arg0->m0 = o;
            if (o == NULL) {
                return 1;
            }
            memset(&(*(Desc *)(rgp_blk1 + 0x0)), 0, sizeof((*(Desc *)(rgp_blk1 + 0x0))));
                (*(Desc *)(rgp_blk1 + 0x0)).m30 = 8;
                (*(Desc *)(rgp_blk1 + 0x0)).m2C = (*(Desc *)(rgp_blk1 + 0x0)).buf1;
                (*(Desc *)(rgp_blk1 + 0x0)).m3C = 8;
                (*(Desc *)(rgp_blk1 + 0x0)).m38 = (*(Desc *)(rgp_blk1 + 0x0)).buf2;
                (*(Desc *)(rgp_blk1 + 0x0)).m0 = arg1;
                (*(Desc *)(rgp_blk1 + 0x0)).m4 = D_0045B398;
                (*(Desc *)(rgp_blk1 + 0x0)).m8 = arg5;
                (*(Desc *)(rgp_blk1 + 0x0)).mC = arg5;
                (*(Desc *)(rgp_blk1 + 0x0)).m10 = arg5;
                (*(Desc *)(rgp_blk1 + 0x0)).m14 = arg4;
                (*(Desc *)(rgp_blk1 + 0x0)).m18 = 0;
                arg0->m0->f50();
            InfoCfgParseAll_1afd00(arg0->m0, &(*(Desc *)(rgp_blk1 + 0x0)));
            arg0->m8 = arg4;
            cnt = 0;
            p = ArchiveGetFileByPath_1c2800(arg1, arg3->mC, &cnt);
            if (p != NULL) {
                if (cnt > 0) {
                    h.m0 = 0;
                    ModelResRelocate_14bfd0(&h, p);
                    r = CollFrameTreeBuild_16ba00(&h, arg5);
                    arg0->m4 = r;
                    if (r == 0) {
                        return 0;
                    }
                }
            }
            return 1;
    }
    return 0;
}
