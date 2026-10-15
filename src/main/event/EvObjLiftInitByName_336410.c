#include "types.h"

typedef struct T336410 {
    u8  pad00[0xE0];
    s32 fE0;
    s32 fE4;
    s16 fE8;
    s16 fEA;
    s32 fEC;
    s32 fF0;
} T336410;

extern void EvObjLiftReset_336500(T336410 *);
extern void EvObjInitByName_2f9de0(T336410 *, s32, s32, s32);
extern void TargetRefSetMapObj_2e6470(void *, s32, s32, f32);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 EventObjMgrFindVolumeRecByName_2e9bc0(s32, s32);
extern s32 EventObjMgrFindPathRecByName_2e9c90(s32, s32);

void EvObjLiftInitByName_336410(T336410 *o, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                  s32 a6, s32 a7, s32 s0, s32 s1, s32 s2, s32 s3)
{
    EvObjLiftReset_336500(o);
    EvObjInitByName_2f9de0(o, a1, a2 | 0x08000000, a3);
    TargetRefSetMapObj_2e6470((u8 *)o + 0xA0, a4, a5, 0.0f);
    o->fEC = EventObjMgrFindVolumeRecByName_2e9bc0(GetEventObjMgr_2d1960(), a6);
    o->fF0 = EventObjMgrFindPathRecByName_2e9c90(GetEventObjMgr_2d1960(), a7);
    o->fE0 = s0;
    o->fE8 = (s16)s1;
    o->fE4 = s2;
    o->fEA = (s16)s3;
}
