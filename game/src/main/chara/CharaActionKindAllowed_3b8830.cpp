/* PARK (round 0, not attempted): m2c fails - "Found jr instruction... but the
   corresponding jump table is not provided" - needs the .rodata jump table
   read alongside the raw asm and a manual switch reconstruction. Not
   started. */
/* s49m: MATCH jtbl rodata_check */
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    bool v70() { return (vc_u8)VCM0(vc_u32, 0x70) != 0; }
    bool v74() { return (vc_u8)VCM0(vc_u32, 0x74) != 0; }
    bool v78() { return (vc_u8)VCM0(vc_u32, 0x78) != 0; }
    bool v7C() { return (vc_u8)VCM0(vc_u32, 0x7C) != 0; }
    bool v80() { return (vc_u8)VCM0(vc_u32, 0x80) != 0; }
    bool v84() { return (vc_u8)VCM0(vc_u32, 0x84) != 0; }
    bool v88() { return (vc_u8)VCM0(vc_u32, 0x88) != 0; }
    bool v8C() { return (vc_u8)VCM0(vc_u32, 0x8C) != 0; }
    bool v90() { return (vc_u8)VCM0(vc_u32, 0x90) != 0; }
    bool v94() { return (vc_u8)VCM0(vc_u32, 0x94) != 0; }
    bool v98() { return (vc_u8)VCM0(vc_u32, 0x98) != 0; }
    bool v9C() { return (vc_u8)VCM0(vc_u32, 0x9C) != 0; }
    bool vA0() { return (vc_u8)VCM0(vc_u32, 0xA0) != 0; }
    bool vA4() { return (vc_u8)VCM0(vc_u32, 0xA4) != 0; }
    
    
    
    
    bool vB8() { return (vc_u8)VCM0(vc_u32, 0xB8) != 0; }
};

extern "C" u32 CharaActionKindAllowed_3b8830(Obj *obj, u32 arg1)
{
    bool r;

    switch (arg1) {
    case 0:
        r = obj->v70();
        break;
    case 9:
        r = obj->v74();
        break;
    case 12:
        r = obj->v78();
        break;
    case 3:
        r = obj->v90();
        break;
    case 4:
        r = obj->v94();
        break;
    case 5:
        r = obj->v7C();
        break;
    case 6:
        r = obj->v80();
        break;
    case 7:
        r = obj->v84();
        break;
    case 8:
        r = obj->v88();
        break;
    case 13:
        r = obj->v8C();
        break;
    case 15:
        r = obj->v98();
        break;
    case 16:
        r = obj->v9C();
        break;
    case 17:
        r = obj->vA0();
        break;
    case 18:
        r = obj->vA4();
        break;
    case 19:
        r = obj->vB8();
        break;
    case 2:
        r = true;
        break;
    case 14:
        r = true;
        break;
    default:
        r = false;
        break;
    }
    return (bool)(r);
}
