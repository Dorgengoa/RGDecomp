#include "types.h"

/* MW C++ runtime (MSL iostreams): ios_base::Init-style constructor, C-linkage form.
 * Three function-local-static stdio buffers (guard byte / __register_global_object
 * chain node / object, dtor FilebufDtor_102e80) over the console FILEs D_00449858->[1..3],
 * then on the first Init: placement-new cin/cout/cerr/clog, cin.tie(&cout),
 * cerr.setf(unitbuf), and setbuf(0, 0) on each buffer (virtual call -> $t9).
 * Built as C++ with exceptions on: each placement new gets a compiler cleanup region
 * (sp saved at fp+0xa4/0x84/0x64/0x44, dead `__throw(0,0,0)` rethrow, no __end__catch);
 * an explicit try/catch(...) would add __end__catch.  Inline ctors keep the jal on the
 * extern "C" constructors.  Retail carries no EH table, so objfix drops
 * .exceptix/.exception (config/objfix.txt).  Same code at -O4 and -O4,p (no toolchain row).
 * WIosBaseInitCtor_103110 is the wide-char twin (wcin/wcout/...). */
#pragma cplusplus on
#pragma exceptions on

extern "C" void FilebufCtor_105040(void *buf, void *file);              /* stdio buffer ctor */
extern "C" void RegisterGlobalObject_100dc0(void *obj, void *dtor, void *chain); /* __register_global_object */
extern "C" void IstreamCtor_103f50(void *self, s32 a, void *buf);       /* istream ctor */
extern "C" void OstreamCtor_104270(void *self, s32 a, void *buf);       /* ostream ctor */
extern "C" void FilebufDtor_102e80(void);                               /* stdio buffer dtor */

inline void *operator new(unsigned int, void *p) { return p; }
inline void operator delete(void *, void *) {}

struct StreamBuf {
    virtual void v0(void);
    virtual void setbuf(s32 s, s32 n); /* vtable +0xC */
};
typedef struct StdioBuf { StreamBuf b; s32 pad[13]; } StdioBuf;

struct IStream { s32 x[28]; IStream(s32 a, void *buf) { IstreamCtor_103f50(this, a, buf); } };
struct OStream { s32 x[24]; OStream(s32 a, void *buf) { OstreamCtor_104270(this, a, buf); } };

typedef struct { u8 *vb; s32 pad[15]; } Stream; /* vb = virtual base (ios) pointer */
typedef struct { s8 v; s8 pad[15]; } Guard;
typedef struct { s32 v[4]; } ChainNode;

extern struct { void **v; s32 pad[3]; } D_00449858; /* console FILEs: [1] in, [2] out, [3] err */
extern Guard D_00485708, D_00485758, D_004857A8;
extern ChainNode D_00485710, D_00485760, D_004857B0;
extern StdioBuf D_00485720, D_00485770, D_004857C0;
extern struct { s32 v; s32 pad[3]; } D_004853D8; /* Init count */
extern Stream D_004853F0, D_00485460, D_004854C0, D_00485520; /* cin, cout, clog, cerr */

extern "C" void *IosBaseInitCtor_102bd0(void *self)
{
    if (!D_00485708.v) {
        FilebufCtor_105040(&D_00485720, D_00449858.v[1]);
        RegisterGlobalObject_100dc0(&D_00485720, (void *)FilebufDtor_102e80, &D_00485710);
        D_00485708.v = 1;
    }
    if (!D_00485758.v) {
        FilebufCtor_105040(&D_00485770, D_00449858.v[2]);
        RegisterGlobalObject_100dc0(&D_00485770, (void *)FilebufDtor_102e80, &D_00485760);
        D_00485758.v = 1;
    }
    if (!D_004857A8.v) {
        FilebufCtor_105040(&D_004857C0, D_00449858.v[3]);
        RegisterGlobalObject_100dc0(&D_004857C0, (void *)FilebufDtor_102e80, &D_004857B0);
        D_004857A8.v = 1;
    }
    if (D_004853D8.v++ == 0) {
        new (&D_004853F0) IStream(1, &D_00485720);
        new (&D_00485460) OStream(1, &D_00485770);
        new (&D_00485520) OStream(1, &D_004857C0);
        new (&D_004854C0) OStream(1, &D_004857C0);
        *(void **)(D_004853F0.vb + 0x40) = &D_00485460;  /* cin.tie(&cout) */
        *(u16 *)(D_00485520.vb + 0x38) |= 0x2000;        /* cerr unitbuf */
        D_00485720.b.setbuf(0, 0);
        D_00485770.b.setbuf(0, 0);
        D_004857C0.b.setbuf(0, 0);
    }
    return self;
}
