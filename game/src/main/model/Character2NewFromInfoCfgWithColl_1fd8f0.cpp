/* rgp:protos */
#line 1
#include "types.h"

class VO {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x50); }
};

extern "C" {

typedef struct {
    s32 w0;
    void *p4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0x10];
    void *p2C;
    s32 w30;
    u8 pad34[4];
    void *p38;
    s32 w3C;
    u8 buf40[0x20];
    u8 buf60[0x28];
} Desc;

typedef struct {
    u8 **pp0;
    s32 *p4;
    s32 w8;
    s32 wC;
    u8 b10;
} Arg;

extern void ModelResRelocate_14bfd0(s32 *, s32);
extern u8 *MemStackNew_14e230(s32, s32);
extern s32 CollFrameTreeBuild_16ba00(s32 *, s32);
extern void InfoCfgParseAll_1afd00(u8 *, Desc *);
extern s32 ArchiveGetFileByPath_1c2800(s32, s32, s32 *);
extern void ModelObjExCtor_1c4920(u8 *, int, int, int);
extern void *memset(void *, s32, u32);
extern u8 D_0045BEA0[0x10];
extern u8 D_00470F50[0x400];

s32 Character2NewFromInfoCfgWithColl_1fd8f0(Arg *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Desc)) + (0x88) + (0x90)];
    s32 spF0[2];
    s32 cnt;
    s32 heap;
    u8 *o;
    s32 r;

    if (arg0 == NULL || arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    heap = arg0->w8;
    if (heap == 0) {
        return 0;
    }    if (arg0->pp0 == NULL) {
        goto skip;
    }
    {
        o = MemStackNew_14e230(0x790, heap);
        if (o != NULL) {
            ModelObjExCtor_1c4920(o, 0, 0, 0);
            *(u8 **)(o + 0x1B0) = D_00470F50;
        }
        *arg0->pp0 = o;
        memset(&(*(Desc *)(rgp_blk1 + 0x0)), 0, 0x88);
        (*(Desc *)(rgp_blk1 + 0x0)).w30 = 8;
        (*(Desc *)(rgp_blk1 + 0x0)).p2C = (*(Desc *)(rgp_blk1 + 0x0)).buf40;
        (*(Desc *)(rgp_blk1 + 0x0)).w3C = 8;
        (*(Desc *)(rgp_blk1 + 0x0)).w0 = arg1;
        (*(Desc *)(rgp_blk1 + 0x0)).p38 = (*(Desc *)(rgp_blk1 + 0x0)).buf60;
        (*(Desc *)(rgp_blk1 + 0x0)).p4 = D_0045BEA0;
        (*(Desc *)(rgp_blk1 + 0x0)).w8 = heap;
        (*(Desc *)(rgp_blk1 + 0x0)).wC = heap;
        (*(Desc *)(rgp_blk1 + 0x0)).w10 = heap;
        (*(Desc *)(rgp_blk1 + 0x0)).w14 = arg0->wC;
        (*(Desc *)(rgp_blk1 + 0x0)).w18 = arg0->b10;
        o = *arg0->pp0;
        ((VO *)o)->f();
        InfoCfgParseAll_1afd00(*arg0->pp0, &(*(Desc *)(rgp_blk1 + 0x0)));
        *(s32 *)(*arg0->pp0 + 0x4DC) = (*(Desc *)(rgp_blk1 + 0x0)).w14;
    }
skip:
    if (arg0->p4 != NULL && arg3 != 0) {
        r = ArchiveGetFileByPath_1c2800(arg1, arg3, &cnt);
        if (r != 0 && cnt > 0) {
            spF0[0] = 0;
            ModelResRelocate_14bfd0(spF0, r);
            *arg0->p4 = CollFrameTreeBuild_16ba00(spF0, heap);
        }
    }
    return 1;
}
}
