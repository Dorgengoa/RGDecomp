#include "types.h"

/* MW C++ runtime (ExceptionPPC.cp): extern "C" void __unexpected(CatchInfo *catchinfo)
 *   Called from a throw()-spec handler.  Calls unexpected() (Unexpected_100cb0) inside a
 *   try; on any exception, rethrows it if its type is in the violated specification
 *   (catchinfo->stacktop = the spec action), else throws std::bad_exception if that is
 *   listed, else falls through to terminate() (Terminate_100ce0).
 * Built as C++ with exceptions on (#pragma exception_magic gives the catch(...) block
 * its CatchInfo at fp+0x50).  Retail carries no EH table, so objfix drops
 * .exceptix/.exception; the throw-type string goes to the retail copy D_00455570.
 * bad_exception vtable/dtor and __end__catch are retail D_0046FD90 / BadExceptionDtor_1016a0 /
 * EhEndCatch_101010 (config/aliases.txt).  Built -O4,p (config/toolchain.txt).
 * The union in IsInSpecification is what keeps the dead `sw catch_type` home store. */
#pragma cplusplus on
#pragma exceptions on

typedef struct CatchInfo {
    void *location;
    void *typeinfo;
    void *dtor;
    void *sublocation;
    s32 pointercopy;
    void *stacktop;
} CatchInfo;

typedef struct ex_specification {
    u32 specs;
    u32 pcoffset;
    s32 cinfo_ref;
    u8 *spec;
} ex_specification;

namespace std {
class exception {
public:
    exception() {}
    virtual ~exception();
    virtual const char *what() const;
};
class bad_exception : public exception {
public:
    bad_exception() {}
    virtual ~bad_exception();
    virtual const char *what() const;
};
}

extern "C" const char D_00455550[];
extern "C" void Unexpected_100cb0(void);
extern "C" void Terminate_100ce0(void);
extern "C" s32 EhCatchTypeCompare_100a60(char *throwtype, char *catchtype, s64 *offset_result);
extern "C" u8 *DecodeVarUInt_100ed0(u8 *p, u32 *pval);
extern "C" u8 *DecodeVarInt_100f70(u8 *p, s32 *pval);

static inline s32 IsInSpecification(char *extype, ex_specification *spec)
{
    u8 *p;
    u32 i;
    s64 offset;
    union { u32 v; char *p; } ct;

    for (i = 0, p = spec->spec; i < spec->specs; i++, p += 4) {
        ct.v = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
        if (EhCatchTypeCompare_100a60(extype, ct.p, &offset)) {
            return 1;
        }
    }
    return 0;
}

extern "C" void EhUnexpected_1014d0(CatchInfo *catchinfo)
{
    ex_specification spec;
    u8 *unexp = (u8 *)catchinfo->stacktop;
    u8 *p;
#pragma exception_magic

    try {
        Unexpected_100cb0();
    } catch (...) {
        p = DecodeVarUInt_100ed0(unexp + 1, &spec.specs);
        p = DecodeVarUInt_100ed0(p, &spec.pcoffset);
        spec.spec = DecodeVarInt_100f70(p, &spec.cinfo_ref);
        if (IsInSpecification((char *)((CatchInfo *)&__exception_magic)->typeinfo, &spec)) {
            throw;
        }
        if (IsInSpecification((char *)D_00455550, &spec)) {
            throw std::bad_exception();
        }
    }
    Terminate_100ce0();
}
