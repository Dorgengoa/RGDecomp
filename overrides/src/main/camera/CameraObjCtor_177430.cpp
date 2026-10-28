/* rg-override: replaces game/src/main/camera/CameraObjCtor_177430.cpp sha256 eba8ed77567046c1ee26f18b7282accd74936bf5bef0b4fc64d9d3a912deba92
 * why: the one real C++ constructor (PLAN transform 3 exception).  De-virtualised
 * classes have no implicit vptr stores, so the ctor becomes the C-linkage game
 * symbol its callers use, with the two vptr stores spelled out (docs/DEVIRT.md). */
#include "types.h"
#include "vu0inline.h"

extern "C" u8 D_00470090[];
extern "C" u8 D_00470340[];

typedef struct P177430 {
    f32 f0, f4, f8, fC, f10, f14, f18, f1C, f20, f24;
    s32 f28;
} P177430;

class B177430 {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;   
       
       
      
    void Init() { VCM0(void, 0x44); }
    P177430 * Params() { return VCM0(P177430 *, 0x48); }
    void Setup() { VCM0(void, 0x4C); }
    B177430() { Init(); }
};
class O177430 : public B177430 {
public:
    
    
    
    u8 padC4[0xD0 - 0xC4];
    u8 vD0[0x10];
    u8 vE0[0x10];
    u8 vF0[0x8];
    f32 fF8;
    u8 padFC[4];
    f32 f100;
    f32 f104;
    s32 f108;
    s32 f10C;
    s32 f110;
    u8 pad114[0x120 - 0x114];
    u8 v120[0x10];
    u8 pad130[0x158 - 0x130];
    s32 f158;
    u8 pad15C[0x184 - 0x15C];
    s32 f184;
};

extern "C" void CameraObjCtor_177430(O177430 *o)
{ RG_VU0_FRAME;
    P177430 *p;

    /* what mwcc's O177430::O177430() did implicitly: the inlined base ctor
       stores the base vtable and calls Init() through it, then the derived
       vtable is stored (README case 5; config/aliases.txt __vt__7B177430 =
       0x470090, __vt__7O177430 = 0x470340) */
    VC_SET_VPTR(o, 0xC0, D_00470090);
    o->Init();
    VC_SET_VPTR(o, 0xC0, D_00470340);

    o->f158 = 0;
    o->f184 = 0;
    p = o->Params();
    p->f0 = 100.0f;
    p->f4 = 160.0f;
    p->f8 = 18.0f;
    p->fC = 10.0f;
    p->f14 = 40.0f;
    p->f18 = -15.0f;
    p->f1C = 20.0f;
    p->f20 = -15.0f;
    p->f10 = p->f20;
    p->f24 = 25.0f;
    p->f28 = 0;
    Vu0UnitVector(o->vD0);
    Vu0UnitVector(o->vE0);
    Vu0UnitVector(o->vF0);
    Vu0UnitVector((u8 *)o + 0x50);
    Vu0UnitVector((u8 *)o + 0x60);
    Vu0UnitVector(o->v120);
    *(f32 *)((u8 *)o + 0x68) = 1.0f;
    o->fF8 = 1.0f;
    *(s32 *)((u8 *)o + 0x70) = 0;
    o->f108 = 1;
    o->f100 = 8.0f;
    o->f104 = 2.0f;
    o->f10C = 1;
    o->f110 = 0;
    o->Setup();
}
