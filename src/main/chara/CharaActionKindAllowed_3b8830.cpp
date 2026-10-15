/* PARK (round 0, not attempted): m2c fails - "Found jr instruction... but the
   corresponding jump table is not provided" - needs the .rodata jump table
   read alongside the raw asm and a manual switch reconstruction. Not
   started. */
/* s49m: MATCH jtbl rodata_check */
#include "types.h"

class Obj {
public:
    virtual bool v08();
    virtual bool v0C();
    virtual bool v10();
    virtual bool v14();
    virtual bool v18();
    virtual bool v1C();
    virtual bool v20();
    virtual bool v24();
    virtual bool v28();
    virtual bool v2C();
    virtual bool v30();
    virtual bool v34();
    virtual bool v38();
    virtual bool v3C();
    virtual bool v40();
    virtual bool v44();
    virtual bool v48();
    virtual bool v4C();
    virtual bool v50();
    virtual bool v54();
    virtual bool v58();
    virtual bool v5C();
    virtual bool v60();
    virtual bool v64();
    virtual bool v68();
    virtual bool v6C();
    virtual bool v70();
    virtual bool v74();
    virtual bool v78();
    virtual bool v7C();
    virtual bool v80();
    virtual bool v84();
    virtual bool v88();
    virtual bool v8C();
    virtual bool v90();
    virtual bool v94();
    virtual bool v98();
    virtual bool v9C();
    virtual bool vA0();
    virtual bool vA4();
    virtual bool vA8();
    virtual bool vAC();
    virtual bool vB0();
    virtual bool vB4();
    virtual bool vB8();
};

extern "C" bool CharaActionKindAllowed_3b8830(Obj *obj, u32 arg1)
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
    return r;
}
