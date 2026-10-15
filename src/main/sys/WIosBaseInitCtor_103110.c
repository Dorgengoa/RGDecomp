#include "types.h"

/* MW C++ runtime (MSL iostreams): wide-char ios_base::Init-style constructor, C-linkage form
 * (wide twin of IosBaseInitCtor_102bd0).
 * Three function-local-static wide stdio buffers (guard byte / __register_global_object
 * chain node / object, dtor WFilebufDtor_1033c0) over the console FILEs D_00449858->[1..3],
 * then on the first Init: placement-new wcin/wcout/wcerr/wclog, wcin.tie(&wcout),
 * wcerr.setf(unitbuf), and setbuf(0, 0) on each buffer (virtual call -> $t9).
 * Built as C++ with exceptions on: each placement new gets a compiler cleanup region
 * (sp saved at fp+0xa4/0x84/0x64/0x44, dead `__throw(0,0,0)` rethrow, no __end__catch);
 * an explicit try/catch(...) would add __end__catch.  Inline ctors keep the jal on the
 * extern "C" constructors.  Retail carries no EH table, so objfix drops
 * .exceptix/.exception (config/objfix.txt).  Same code at -O4 and -O4,p (no toolchain row).
 */
#pragma cplusplus on
#pragma exceptions on

extern "C" void WFilebufCtor_105be0(void *buf, void *file);              /* wide stdio buffer ctor */
extern "C" void RegisterGlobalObject_100dc0(void *obj, void *dtor, void *chain); /* __register_global_object */
extern "C" void WistreamCtor_104000(void *self, s32 a, void *buf);       /* wistream ctor */
extern "C" void WostreamCtor_1044e0(void *self, s32 a, void *buf);       /* wostream ctor */
extern "C" void WFilebufDtor_1033c0(void);                               /* wide stdio buffer dtor */

inline void *operator new(unsigned int, void *p) { return p; }
inline void operator delete(void *, void *) {}

struct StreamBuf {
    virtual void v0(void);
    virtual void setbuf(s32 s, s32 n); /* vtable +0xC */
};
typedef struct StdioBuf { StreamBuf b; s32 pad[25]; } StdioBuf;

struct IStream { s32 x[28]; IStream(s32 a, void *buf) { WistreamCtor_104000(this, a, buf); } };
struct OStream { s32 x[24]; OStream(s32 a, void *buf) { WostreamCtor_1044e0(this, a, buf); } };

typedef struct { u8 *vb; s32 pad[15]; } Stream; /* vb = virtual base (ios) pointer */
typedef struct { s8 v; s8 pad[15]; } Guard;
typedef struct { s32 v[4]; } ChainNode;

extern struct { void **v; s32 pad[3]; } D_00449858; /* console FILEs: [1] in, [2] out, [3] err */
extern Guard D_004857F8, D_00485878, D_004858F8;
extern ChainNode D_00485800, D_00485880, D_00485900;
extern StdioBuf D_00485810, D_00485890, D_00485910;
extern struct { s32 v; s32 pad[3]; } D_004853E0; /* Init count */
extern Stream D_00485580, D_004855F0, D_00485650, D_004856B0; /* wcin, wcout, wclog, wcerr */

extern "C" void *WIosBaseInitCtor_103110(void *self)
{
    if (!D_004857F8.v) {
        WFilebufCtor_105be0(&D_00485810, D_00449858.v[1]);
        RegisterGlobalObject_100dc0(&D_00485810, (void *)WFilebufDtor_1033c0, &D_00485800);
        D_004857F8.v = 1;
    }
    if (!D_00485878.v) {
        WFilebufCtor_105be0(&D_00485890, D_00449858.v[2]);
        RegisterGlobalObject_100dc0(&D_00485890, (void *)WFilebufDtor_1033c0, &D_00485880);
        D_00485878.v = 1;
    }
    if (!D_004858F8.v) {
        WFilebufCtor_105be0(&D_00485910, D_00449858.v[3]);
        RegisterGlobalObject_100dc0(&D_00485910, (void *)WFilebufDtor_1033c0, &D_00485900);
        D_004858F8.v = 1;
    }
    if (D_004853E0.v++ == 0) {
        new (&D_00485580) IStream(1, &D_00485810);
        new (&D_004855F0) OStream(1, &D_00485890);
        new (&D_004856B0) OStream(1, &D_00485910);
        new (&D_00485650) OStream(1, &D_00485910);
        *(void **)(D_00485580.vb + 0x40) = &D_004855F0;  /* wcin.tie(&wcout) */
        *(u16 *)(D_004856B0.vb + 0x38) |= 0x2000;        /* wcerr unitbuf */
        D_00485810.b.setbuf(0, 0);
        D_00485890.b.setbuf(0, 0);
        D_00485910.b.setbuf(0, 0);
    }
    return self;
}
