#include "types.h"

class ObjC0 {
    u8 pad[0xC0];
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
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4(f32 *);
};

extern "C" {
s32 GetDrawCtx_15de80(void);
ObjC0 *ObjRecGetLiveObject_1c3bc0(void *, s32);
void *GetCurrentScene_1f5be0(void);
s32 GetGameData_1fede0(void);
void ObjRecUpdateDistLightMaybe_319f60(void *, f32 *, s32);
s32 InsectBattleGet_31a8d0(void);
void func_50A520(s32);
extern f32 D_0047F250;
extern f32 D_0047F254;
extern f32 D_0047F258;
extern f32 D_0047F25C;
}

extern "C" void InsectDrawPre_319e70(void) {
    f32 v[4];
    s32 i;
    s32 r;
    void *temp_17;
    ObjC0 *temp_2;

    temp_17 = GetCurrentScene_1f5be0();
    GetDrawCtx_15de80();
    GetGameData_1fede0();
    v[0] = D_0047F250;
    v[1] = D_0047F254;
    v[2] = D_0047F258;
    v[3] = D_0047F25C;
    temp_2 = ObjRecGetLiveObject_1c3bc0(temp_17, *(s32 *)((u8 *)temp_17 + 0x4344));
    if (temp_2 != NULL) {
        temp_2->vA4(v);
    }
    i = 0x80;
    do {
        ObjRecUpdateDistLightMaybe_319f60(temp_17, v, i);
        i += 1;
    } while (i <= 0x9B);
    i = 0xC0;
    do {
        ObjRecUpdateDistLightMaybe_319f60(temp_17, v, i);
        i += 1;
    } while (i <= 0xDF);
    r = InsectBattleGet_31a8d0();
    if (r != 0) {
        func_50A520(r);
    }
}
