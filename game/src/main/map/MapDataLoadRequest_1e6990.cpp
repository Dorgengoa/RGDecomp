#pragma opt_propagation off
#include "types.h"

class VS {
public:
    u8 pad[0x68];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v84() { VCM0(void, 0x84); }
};


extern "C" {
extern void MemStackInit_14d810(void *, s32, s32);
extern void MemStackReset_14d830(void *);
extern void MemStackClear_14dff0(void *);
extern void *MemStackNew_14e230(s32, void *);
extern void MapPartsGroupEntryCtorMaybe_189e00(void *);
extern void FuncDataTableCtor_18fbf0(void *);
extern void MapSceneCfgInit_1937a0(void *);
extern s32 PtrAddAligned16_1cac90(void *, s32);
extern u32 AlignUp16_1cacd0(s32);
extern void MapDataUnload_1e6690(void *, s32);
extern void MapDataSetState_1e72c0(void *, s32);
extern s32 MapAreaDataRequestFiles_1e8a70(void *, s32, char *, void *);
extern void *memset(void *, s32, u32);
extern char *strcpy(char *, const char *);
extern u32 strlen(const char *);
extern u8 D_00470410[];
extern u8 D_00470480[];

}

struct OV { u8 pad[0x98]; void *vp; };

extern "C" s32 MapDataLoadRequest_1e6990(void **arg0, void *arg1, s32 arg2, char *arg3, void *arg4, s32 arg5)
{
    u8 *o;
    s32 n;
    u8 *p;
    u8 *e;

    if (arg1 == 0) return 0;
    if (arg4 == 0) return 0;
    n = AlignUp16_1cacd0(0x58) >> 4;
    if (n < arg5) {
        arg0[1] = arg1;
        arg0[0] = arg4;
        MemStackClear_14dff0(arg4);
        MemStackInit_14d810(arg0[0], PtrAddAligned16_1cac90(arg4, n << 4), arg5 - n);
        p = (u8 *)arg0[0];
        if (strlen(arg3) < 0x10) {
            strcpy((char *)p, arg3);
        }
        MemStackReset_14d830(arg0[0]);
        if ((o = (u8 *)MemStackNew_14e230(0x1710, arg0[0])) != 0) {
            ((OV *)o)->vp = D_00470410;
            ((OV *)o)->vp = D_00470480;
            p = o + 0x148;
            e = o + 0x208;
            do {
                *(s32 *)(p + 0) = 0;
                *(s32 *)(p + 4) = 0;
                *(s32 *)(p + 8) = 0;
                p += 0xC;
            } while (p < e);
            MapSceneCfgInit_1937a0(o + 0xA0);
            p = o + 0x2DC;
            do {
                MapPartsGroupEntryCtorMaybe_189e00(p);
                p += 0x10;
            } while (p < o + 0x4DC);
            p = o + 0x5D0;
            e = o + 0xA50;
            do {
                *(s32 *)(p + 0x24) = 0;
                *(s32 *)(p + 0x20) = 0;
                *(s32 *)(p + 0x28) = 0;
                p += 0x30;
            } while (p < e);
            p = o + 0xA60;
            do {
                memset(p, 0, 0xC0);
                p += 0xC0;
            } while (p < o + 0x1660);
            FuncDataTableCtor_18fbf0(o + 0x1694);
            ((VS *)(o + 0x30))->v84();
        }
        arg0[2] = o;
        if (o != 0 && MapAreaDataRequestFiles_1e8a70(o, arg2, arg3, arg0[0]) != 0) {
            MapDataSetState_1e72c0(arg0, 1);
            return 1;
        }
    }
    MapDataUnload_1e6690(arg0, 1);
    MapDataSetState_1e72c0(arg0, -1);
    return 0;
}
