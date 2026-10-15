#include "types.h"
#include "vec.h"

class VC_0 {
public:
    u8 pad[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual f32 f();
};

typedef struct {
    u8 pad0[0x4];
    s16 x4;
    u8 pad6[0x30 - 0x6];
    s16 x30;
    u8 pad32[0x18E - 0x32];
    s16 x18E;
} G18_0039a620;

typedef struct {
    u8 pad0[0x18];
    G18_0039a620 *x18;
} G_0039a620;

typedef struct {
    u8 pad0[0x180C];
    s32 x180C;
    u8 pad1810[0x4344 - 0x1810];
    s32 x4344;
} W_0039a620;

typedef struct {
    u8 pad0[0x448];
    f32 x448;
} C0_0039a620;

typedef struct {
    u8 pad0[0x40];
    s16 x40;
    u8 pad42[0x44 - 0x42];
    s16 x44;
    s16 x46;
    u8 pad48[0x54 - 0x48];
    s32 x54;
    u8 pad58[0x60 - 0x58];
} Item_0039a620;

typedef struct {
    u8 pad0[6];
    s16 x6;
} Hit_0039a620;

typedef struct {
    Vec4 mx;
    Vec4 mn;
} Box_0039a620;

typedef struct {
    u8 sub[3][0x30];                    /* 0x00 */
    u8 pad90[0xB0 - 0x90];
    f32 xB0;                            /* 0xB0 */
    f32 xB4;
    f32 xB8;
    u8 padBC[0xC0 - 0xBC];
    Vec4 xC0;                           /* 0xC0 */
    Vec4 xD0;                           /* 0xD0 */
    Vec4 xE0;                           /* 0xE0 */
    s32 xF0;                            /* 0xF0 */
    s32 xF4;                            /* 0xF4 */
} Self_0039a620;

extern "C" {
void InsectCageSlotUpdate_39b560(void *, f32);
s32 InsectCageMgrFindSlotById_39b0c0(Self_0039a620 *, s32);
G_0039a620 *GetGameData_1fede0(void);
s32 GetActionMgr_1fdb50(void);
s32 GetMapMgr_201a90(void);
W_0039a620 *GetCurrentScene_1f5be0(void);
s32 InsectCageSlotGetCageRec_39b480(s32);
C0_0039a620 *InsectCageSlotGetModel_39b470(s32);
VC_0 *ObjRecGetLiveObject_1c3bc0(W_0039a620 *, s32);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(s32, Vec4 *);
void VecCopy_1cbe30(Vec4 *, Vec4 *);
u32 AlignUp16_1cacd0(s32);
Item_0039a620 *MemStackHeapAllocFront_14dd10(s32, u32);
s32 MapSlotsCollectCollTrisMaybe_1e35b0(s32, Item_0039a620 *, s32, Box_0039a620 *);
s32 CollTriIsWaterMaybe_1ce5c0(Item_0039a620 *);
f32 PadGetAnalogLXNorm_183af0(void *);
f32 PadGetAnalogLYNorm_183a50(void *);
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
f32 VecLengthSqXZ_1cb450(Vec4 *);
void VecScaleToLength_1cb510(Vec4 *, Vec4 *, f32);
s32 CollSphereSweepNearest_1c8880(Vec4 *, Vec4 *, Item_0039a620 *, s32, s32, Vec4 *, Vec4 *, f32 *, f32);
void VecScale_1cbca0(Vec4 *, Vec4 *, f32);
void VecAddXyzW1_1cbd80(Vec4 *, Vec4 *, Vec4 *);
s32 MapSlotsFindById_1e4b90(s32, s32, s32);
s32 MapDataIsDorgenark_1e7a30(s32);
s32 PadIsHeld_183a20(void *, s32);
f32 AngleWrap_1cbf30(f32);
void InsectCageSlotSetPos_39b290(s32, f32, f32, f32);
void InsectCageSlotSetRot_39b2f0(s32, Vec4 *);
s32 GetEventObjMgr_2d1960(void);
s32 EventObjMgrFindFirstHit_2e8560(s32, Hit_0039a620 *, s32, Vec4 *, Vec4 *, s32);
void EventObjMgrGetPosRecPosById_2e8950(s32, Vec4 *, s32);
f32 VecLengthSq_1cb470(Vec4 *);
void MemStackHeapFree_14dcb0(s32, Item_0039a620 *);
s32 PadIsTriggered_1839f0(void *, s32);
void CageRecSetPlacement_3d0bc0(s32, s16, s32, f32, f32, f32, f32);
void GameSceneSoundSlot0PlaySeVol_1d05f0(W_0039a620 *, s32, f32);
void CagePlaceCursorEnd_39af30(Self_0039a620 *);
s32 CageRecIsPlaced_3d0d20(s32);
extern f32 D_0045B080[];
extern f32 D_0047D344;
extern f32 D_0047DADC;
extern f32 D_0047DB50;
extern f32 D_0047DC50;
extern f32 D_0047DC54;
extern u8 D_004B2570[];
}

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" void InsectCageMgrUpdate_39a620(Self_0039a620 *self, f32 t)
{
    f32 t1EC;
    f32 t1E8;
    Hit_0039a620 hit;
    Vec4 p;
    Vec4 v1C0;
    Box_0039a620 box;
    Vec4 v190;
    Vec4 v180;
    Vec4 v170;
    Vec4 v160;
    Vec4 a150;
    Vec4 b140;
    Vec4 v130;
    Vec4 a120;
    Vec4 b110;
    Vec4 v100;
    s32 i;
    s32 cam;
    G_0039a620 *g;
    s32 h;
    s32 col;
    s32 c2;
    W_0039a620 *w;
    s32 spF8;
    C0_0039a620 *spC0;
    VC_0 *vc;
    s32 e;
    s32 spE0;
    bool flag;
    Item_0039a620 *list;
    f32 s;
    f32 r;
    s32 n;
    Item_0039a620 *it;
    f32 ang;
    f32 ax;
    f32 ay;
    f32 s2;
    f32 k3;
    f32 k1;
    f32 k2;
    f32 sn;
    f32 cs;
    s32 id;
    s32 hi;
    s32 off;
    s32 o;
    s32 typ;
    f32 d;
    f32 f;

    for (i = 0; i < 3; i++) {
        InsectCageSlotUpdate_39b560(self->sub[i], t);
    }
    cam = InsectCageMgrFindSlotById_39b0c0(self, self->xF0);
    if (cam == 0) {
        return;
    }
    g = GetGameData_1fede0();
    h = GetActionMgr_1fdb50();
    col = GetMapMgr_201a90();
    w = GetCurrentScene_1f5be0();
    spF8 = InsectCageSlotGetCageRec_39b480(cam);
    spC0 = InsectCageSlotGetModel_39b470(cam);
    id = (s32)ObjRecGetLiveObject_1c3bc0(w, w->x4344);
    e = ActionMgrFindById_233b50(h, g->x18->x18E);
    spE0 = w->x180C;
    if (spF8 != 0 && spC0 != 0 && e != 0 && id != 0 && spE0 != 0) {
    CharaGetPos_2388a0(e, &p);
    VecCopy_1cbe30(&v1C0, &self->xD0);
    flag = false;
    list = MemStackHeapAllocFront_14dd10(spE0, AlignUp16_1cacd0(0x18000) >> 4);
    if (list != 0) {
        s = D_0045B080[0];
        r = 5.0f * s;
        VecCopy_1cbe30(&box.mn, &p);
        VecCopy_1cbe30(&box.mx, &p);
        box.mn.x -= r;
        box.mn.y -= r;
        box.mn.z -= r;
        box.mx.x += r;
        box.mx.y += r;
        box.mx.z += r;
        n = MapSlotsCollectCollTrisMaybe_1e35b0(col, list, 0x400, &box);
        for (i = 0; i < n; i++) {
            it = &list[i];
            if (CollTriIsWaterMaybe_1ce5c0(it) != 0) {
                it->x46 &= ~0xE;
            }
        }
        ang = ((VC_0 *)id)->f();
        ax = 1.5f * PadGetAnalogLXNorm_183af0(D_004B2570);
        ay = 1.5f * PadGetAnalogLYNorm_183a50(D_004B2570);
        s2 = D_0045B080[0];
        k3 = 3.0f * s2;
        k1 = D_0047D344 * s2;
        k2 = D_0047DC54 * s2;
        VecCopy_1cbe30(&v190, &self->xD0);
        { f32 t = p.y + k1; v190.y = t + s2; }
        ZERO(&v180, 0x10);
        v180.x = ax * Cosf_128d30(ang) + ay * Sinf_128fd0(ang);
        v180.z = -ax * Sinf_128fd0(ang) + ay * Cosf_128d30(ang);
        VecAdd_1cbdc0(&v170, &v190, &v180);
        v190.x = p.x;
        v190.z = p.z;
        VecSub_1cbd00(&v160, &v170, &v190);
        if (!(VecLengthSqXZ_1cb450(&v160) <= k3 * k3)) {
            VecScaleToLength_1cb510(&v160, &v160, k3);
        }
        if (CollSphereSweepNearest_1c8880(&a150, &b140, list, n, 0xE, &v190, &v160, &t1EC, k1) >= 0) {
            VecScale_1cbca0(&v160, &v160, t1EC);
        }
        VecAddXyzW1_1cbd80(&v190, &v190, &v160);
        id = -1;
        ZERO(&v130, 0x10);
        v130.y = -3.0f * s;
        hi = CollSphereSweepNearest_1c8880(&a120, &b110, list, n, 0xE, &v190, &v130, &t1E8, k2);
        if (hi >= 0) {
            off = hi;
            o = MapSlotsFindById_1e4b90(col, list[off].x54, 0);
            typ = list[off].x44;
            if (typ != 2 && typ != 8) {
                if (o == 0 || MapDataIsDorgenark_1e7a30(o) == 0) {
                    flag = true;
                }
            }
            VecScale_1cbca0(&v130, &v130, t1E8);
            id = list[off].x40;
        } else {
            VecScale_1cbca0(&v130, &v130, 0.0f);
            v130.y = -1.0f * s;
        }
        VecAddXyzW1_1cbd80(&self->xD0, &v190, &v130);
        d = 0.0f;
        self->xD0.y -= k2;
        if (PadIsHeld_183a20(D_004B2570, 8) != 0) {
            d -= D_0047DADC;
        } else if (PadIsHeld_183a20(D_004B2570, 4) != 0) {
            d += D_0047DADC;
        }
        self->xE0.y = AngleWrap_1cbf30(self->xE0.y + d);
        sn = Sinf_128fd0(D_0047DC50 * ((f32)self->xF4 / 45.0f - 0.5f));
        InsectCageSlotSetPos_39b290(cam, self->xD0.x, 15.0f + (self->xD0.y + 2.0f * sn), self->xD0.z);
        InsectCageSlotSetRot_39b2f0(cam, &self->xE0);
        c2 = GetEventObjMgr_2d1960();
        if (EventObjMgrFindFirstHit_2e8560(c2, &hit, -1, &self->xD0, &self->xE0, 0) != 0 && (hit.x6 & 3)) {
            flag = false;
        }
        EventObjMgrGetPosRecPosById_2e8950(c2, &v100, id);
        if (VecLengthSq_1cb470(&v100) != 0.0f) {
            flag = false;
        }
    }
    f = 1.0f;
    if (!flag) {
        f = D_0047DB50;
    }
    spC0->x448 = f;
    MemStackHeapFree_14dcb0(spE0, list);
    if (PadIsTriggered_1839f0(D_004B2570, 0x40) != 0) {
        if (flag) {
            CageRecSetPlacement_3d0bc0(spF8, g->x18->x4, g->x18->x30, self->xD0.x, self->xD0.y, self->xD0.z, self->xE0.y);
            InsectCageSlotSetPos_39b290(cam, self->xD0.x, self->xD0.y, self->xD0.z);
            InsectCageSlotSetRot_39b2f0(cam, &self->xE0);
            GameSceneSoundSlot0PlaySeVol_1d05f0(w, 9, 1.0f);
            CagePlaceCursorEnd_39af30(self);
        } else {
            GameSceneSoundSlot0PlaySeVol_1d05f0(w, 6, 1.0f);
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x20) != 0) {
        if (CageRecIsPlaced_3d0d20(spF8) != 0) {
            InsectCageSlotSetPos_39b290(cam, self->xB0, self->xB4, self->xB8);
            InsectCageSlotSetRot_39b2f0(cam, &self->xC0);
        }
        GameSceneSoundSlot0PlaySeVol_1d05f0(w, 6, 1.0f);
        CagePlaceCursorEnd_39af30(self);
    }
    self->xF4++;
    self->xF4 = self->xF4 % 45;
    }
}
