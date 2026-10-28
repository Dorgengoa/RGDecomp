/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    f32 x, y, z, w;
} Vec4;

typedef struct {
    s32 h;          /* 0x00 */
    void *name;     /* 0x04 */
    s32 a, b, c;    /* 0x08 */
    s32 id;         /* 0x14 */
    s32 one;        /* 0x18 */
    s32 pad1C[4];   /* 0x1C */
    void *p0;       /* 0x2C */
    s32 n0;         /* 0x30 */
    s32 pad34;      /* 0x34 */
    void *p1;       /* 0x38 */
    s32 n1;         /* 0x3C */
    u8 buf0[0x20];  /* 0x40 */
    u8 buf1[0x28];  /* 0x60 */
} Desc;

struct VB { u8 d[0x1B0]; };
struct VO : VB {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f21() { VCM0(void, 0x5C); }
};

extern "C" {
void ModelSetPos_151110(u8 *, Vec4 *);
s32 ArchiveGetFileData_181dd0(s32, u8 *, s32);
void InfoCfgParseAll_1afd00(u8 *, Desc *);
void ModelObjExCopy_1aff40(u8 *, u8 *, s32);
s32 LoadHandleFindByName_28af30(s32, s32, s32);
s32 LoadHandleGetData_28b270(s32, s32);
s32 GetEffectMgr_2d9040(void);
void MenuObjSlotModelReset_3848f0(u8 *);
void MenuObjSetReset_384c80(u8 *);
void *memset(void *, s32, u32);
extern u8 D_00463EC8[];
extern u8 D_00463ED8[];
extern u8 D_00463EE8[];
extern u8 D_00463EF8[];
extern u8 D_00463F08[];
extern s32 D_0047E180;
extern f32 D_0047FBC0;
extern f32 D_0047FBC4;
extern f32 D_0047FBC8;
extern f32 D_0047FBCC;
extern s32 D_004802C4;
}

#define VCALL(p) (((VO *)(p))->f21())

extern "C" void InsectCageLoadFxModels_385390(u8 *self, s32 arg1, s32 arg2, s32 arg3) {
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Desc)) + (0x88) + (0x90)];
    volatile Vec4 v0 __attribute__((aligned(16)));
    volatile Vec4 v1 __attribute__((aligned(16)));
    volatile Vec4 v2 __attribute__((aligned(16)));
    volatile Vec4 v3 __attribute__((aligned(16)));
    s32 key;
    s32 h;
    s32 res;
    s32 e;
    s32 t;
    u8 *p;

    key = GetEffectMgr_2d9040() + 0x58;
    h = LoadHandleFindByName_28af30(D_004802C4, arg2, arg3);
    if (h != 0) {
        res = LoadHandleGetData_28b270(h, 0);
        memset(&(*(Desc *)(rgp_blk1 + 0x0)), 0, 0x88);
        (*(Desc *)(rgp_blk1 + 0x0)).a = arg1;
        (*(Desc *)(rgp_blk1 + 0x0)).n0 = 8;
        (*(Desc *)(rgp_blk1 + 0x0)).b = arg1;
        (*(Desc *)(rgp_blk1 + 0x0)).p0 = (*(Desc *)(rgp_blk1 + 0x0)).buf0;
        (*(Desc *)(rgp_blk1 + 0x0)).n1 = 8;
        (*(Desc *)(rgp_blk1 + 0x0)).p1 = (*(Desc *)(rgp_blk1 + 0x0)).buf1;
        (*(Desc *)(rgp_blk1 + 0x0)).name = D_00463EC8;
        (*(Desc *)(rgp_blk1 + 0x0)).c = arg1;
        (*(Desc *)(rgp_blk1 + 0x0)).id = 0x269;
        (*(Desc *)(rgp_blk1 + 0x0)).one = 1;
        VCALL(self + 0x13C0);
        MenuObjSlotModelReset_3848f0(self + 0x13B0);
        VCALL(self + 0x1B60);
        MenuObjSlotModelReset_3848f0(self + 0x1B50);
        e = ArchiveGetFileData_181dd0(res, D_00463ED8, 0);
        if (e != 0) {
            (*(Desc *)(rgp_blk1 + 0x0)).h = e;
            p = self + 0x13C0;
            VCALL(p);
            *(s32 *)(p + 0x53c) = key;
            if (key != 0) {
                t = D_0047E180; D_0047E180 = t + 1; *(s32 *)(p + 0x538) = t;
            }
            InfoCfgParseAll_1afd00(p, &(*(Desc *)(rgp_blk1 + 0x0)));
            v0.x = D_0047FBC0; v0.y = D_0047FBC4; v0.z = D_0047FBC8; v0.w = D_0047FBCC; v0.y = -50.0f; v0.x = 0.0f; v0.z = 0.0f;
            { Vec4 *pv = (Vec4 *)&v0; ModelSetPos_151110(p, pv); }
            ModelObjExCopy_1aff40(p, self + 0x1B60, arg1);
        }
        e = ArchiveGetFileData_181dd0(res, D_00463EE8, 0);
        if (e != 0) {
            (*(Desc *)(rgp_blk1 + 0x0)).h = e;
            
            VCALL((self + 0x22F0));
            *(s32 *)((self + 0x22F0) + 0x53c) = key;
            if (key != 0) {
                t = D_0047E180; D_0047E180 = t + 1; *(s32 *)((self + 0x22F0) + 0x538) = t;
            }
            InfoCfgParseAll_1afd00((self + 0x22F0), &(*(Desc *)(rgp_blk1 + 0x0)));
            v1.x = D_0047FBC0; v1.y = D_0047FBC4; v1.z = D_0047FBC8; v1.w = D_0047FBCC; v1.y = -50.0f; v1.x = 0.0f; v1.z = 0.0f;
            { Vec4 *pv = (Vec4 *)&v1; ModelSetPos_151110((self + 0x22F0), pv); }
            ModelObjExCopy_1aff40((self + 0x22F0), self + 0x2A80, arg1);
        }
        e = ArchiveGetFileData_181dd0(res, D_00463EF8, 0);
        if (e != 0) {
            (*(Desc *)(rgp_blk1 + 0x0)).h = e;
            
            VCALL((self + 0x3220));
            *(s32 *)((self + 0x3220) + 0x53c) = key;
            if (key != 0) {
                t = D_0047E180; D_0047E180 = t + 1; *(s32 *)((self + 0x3220) + 0x538) = t;
            }
            InfoCfgParseAll_1afd00((self + 0x3220), &(*(Desc *)(rgp_blk1 + 0x0)));
            v2.x = D_0047FBC0; v2.y = D_0047FBC4; v2.z = D_0047FBC8; v2.w = D_0047FBCC; v2.y = -50.0f; v2.x = 0.0f; v2.z = 0.0f;
            { Vec4 *pv = (Vec4 *)&v2; ModelSetPos_151110((self + 0x3220), pv); }
            
        }
        e = ArchiveGetFileData_181dd0(res, D_00463F08, 0);
        if (e != 0) {
            (*(Desc *)(rgp_blk1 + 0x0)).h = e;
            
            VCALL((self + 0x39C0));
            *(s32 *)((self + 0x39C0) + 0x53c) = key;
            if (key != 0) {
                t = D_0047E180; D_0047E180 = t + 1; *(s32 *)((self + 0x39C0) + 0x538) = t;
            }
            InfoCfgParseAll_1afd00((self + 0x39C0), &(*(Desc *)(rgp_blk1 + 0x0)));
            v3.x = D_0047FBC0; v3.y = D_0047FBC4; v3.z = D_0047FBC8; v3.w = D_0047FBCC; v3.y = -50.0f; v3.x = 0.0f; v3.z = 0.0f;
            { Vec4 *pv = (Vec4 *)&v3; ModelSetPos_151110((self + 0x39C0), pv); }
            
        }
        MenuObjSetReset_384c80(self);
    }
}
