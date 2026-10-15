#include "types.h"

/* MSL C++ runtime: void *operator new(size_t size)
 *   if (!size) size = 1; loop malloc (Malloc_130dd8) until it succeeds, calling the
 *   installed new_handler (D_004853C8) between tries; with no handler, throw
 *   std::bad_alloc when the throws-bad_alloc flag (D_00445E80) is set, else return 0.
 * Built as C++ with exceptions on: the throw expression is what gives mwcc its
 * frame-pointer frame (bad_alloc temporary at fp+0x3C).  Retail carries no EH
 * table, so objfix drops .exceptix; the throw-type string goes to the retail copy
 * D_004554E0 (config/objfix.txt).  bad_alloc's vtable/dtor and __throw are retail
 * D_0046FD80 / BadAllocDtor_100920 / ThrowException_1025c0 (config/aliases.txt).
 * Built -O4,p (config/toolchain.txt): the `b; nop; nop` and `beqz; nop; nop` tails. */
#pragma cplusplus on
#pragma exceptions on

namespace std {
class exception {
public:
    exception() {}
    virtual ~exception();
    virtual const char *what() const;
};
class bad_alloc : public exception {
public:
    bad_alloc() {}
    virtual ~bad_alloc();
    virtual const char *what() const;
};
}

typedef void (*NewHandler)(void);
extern "C" NewHandler D_004853C8[];
extern "C" s8 D_00445E80[];
extern "C" void *Malloc_130dd8(u32);

extern "C" void *OperatorNew_100990(u32 size)
{
    void *p;

    if (size == 0) size = 1;
    while ((p = Malloc_130dd8(size)) == 0) {
        if (D_004853C8[0]) {
            D_004853C8[0]();
        } else if (D_00445E80[0]) {
            throw std::bad_alloc();
        } else {
            return 0;
        }
    }
    return p;
}
