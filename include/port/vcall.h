/* port/vcall.h (promoted from probes/vtable/vcall.h) -- explicit virtual dispatch through the game's own (mwcc-layout) vtables.
 *
 * mwcc (CodeWarrior PS2 3.0.1) vtable ABI, settled from retail (see README.md):
 *
 *   vtable symbol D_xxxxxxxx (generated data C, u32[]):
 *     +0x0  u32  RTTI pointer   (0 in every game class; MSL classes carry a typeinfo ptr)
 *     +0x4  u32  offset word    (0 in every vtable observed, primary or secondary)
 *     +0x8  u32  slot 0
 *     +0x8+4k    slot k
 *   object:  the vptr holds the vtable SYMBOL address (not an Itanium "address point"),
 *            stored at byte offset VOFF inside the object (VOFF = size of the data
 *            members declared before the first virtual function).
 *   call:    fn = *(u32 *)(*(u32 *)((u8 *)this + VOFF) + SOFF);  fn(this, args...)
 *            SOFF = 8 + 4*k.  `this` is the pointer the vptr was loaded through
 *            (mwcc folds sub-object offsets into VOFF; it never adjusts `this` at the
 *            call site).  Multiple-inheritance adjustment lives in game-code thunks
 *            stored in the secondary vtable, not in the call sequence.
 *   struct return: hidden result pointer FIRST, `this` second (MIPS $4/$5).
 *
 * Port side: slots are u32 (i686 only -- D1), implementations are extern "C" cdecl
 * functions taking `this` as their first parameter.  These macros never use the C++
 * virtual mechanism, so they mean the same thing in .c and .cpp and under any compiler.
 */
#ifndef PORT_VCALL_H
#define PORT_VCALL_H

/* Calling convention of every game function (explicit, so a member-function default
 * such as MSVC's __thiscall can never leak into a slot call). */
#if defined(_M_IX86) || defined(__i386__)
#  if defined(_MSC_VER) || defined(_WIN32)
#    define VC_CC __cdecl
#  else
#    define VC_CC __attribute__((cdecl))
#  endif
#else
#  define VC_CC
#endif

typedef unsigned int  vc_u32;   /* one vtable word (generated data is u32[]) */
typedef unsigned char vc_u8;

#define VC_HDR       8u                       /* RTTI word + offset word          */
#define VC_SLOT_OFF(k) (VC_HDR + 4u * (vc_u32)(k)) /* byte offset of slot k        */

/* The vtable address held by the object (== the D_ vtable symbol). */
#define VC_VPTR(obj, voff) \
    (*(const vc_u32 *)((const vc_u8 *)(obj) + (voff)))

/* Raw slot word: function address as u32. */
#define VC_SLOT(obj, voff, soff) \
    (*(const vc_u32 *)(VC_VPTR(obj, voff) + (vc_u32)(soff)))

/* Typed function pointer from a slot.  `ptypes` is the FULL parenthesised parameter
 * list of the implementation, `this` included, e.g. (void *, s32, f32). */
#define VC_FN(ret, ptypes, obj, voff, soff) \
    ((ret (VC_CC *) ptypes)(VC_SLOT(obj, voff, soff)))

/* VCALL(obj, voff, soff, ret, ptypes, args...) -> fn(obj, args...)
 * VCALL0(obj, voff, soff, ret)                  -> fn(obj)
 * `obj` is evaluated TWICE (vptr load + this argument): pass a plain identifier or
 * `this`.  The ingest transform only ever emits these inside generated thunks, where
 * the object is the implicit `this`, so the restriction never bites there. */
#define VCALL0(obj, voff, soff, ret) \
    (VC_FN(ret, (void *), obj, voff, soff)((void *)(obj)))
#define VCALL(obj, voff, soff, ret, ptypes, ...) \
    (VC_FN(ret, ptypes, obj, voff, soff)((void *)(obj), __VA_ARGS__))

/* VCALL_THIS: caller writes the whole argument list itself.  Used for the
 * struct-return case (result pointer first, this second) and anything irregular:
 *   VCALL_THIS(o, 0x0, 0x13C, void, (Bits48 *, void *))(&tmp, o);            */
#define VCALL_THIS(obj, voff, soff, ret, ptypes) \
    VC_FN(ret, ptypes, obj, voff, soff)

/* bool-returning virtual: mwcc's caller tests only the LOW BYTE of $2
 * (`andi $2,$2,0xFF`).  Call through a u32-returning type and narrow, so an
 * implementation declared s32 (most are) cannot leak upper bits into a C++ bool. */
#define VCALL_BOOL0(obj, voff, soff) \
    ((vc_u8)VCALL0(obj, voff, soff, vc_u32) != 0)
#define VCALL_BOOL(obj, voff, soff, ptypes, ...) \
    ((vc_u8)VCALL(obj, voff, soff, vc_u32, ptypes, __VA_ARGS__) != 0)

/* Single-evaluation forms (GNU statement expressions; clang/gcc only).  For
 * hand-written overrides where `obj` is an arbitrary expression. */
#if defined(__GNUC__) || defined(__clang__)
#  define VCALL0_SE(objexpr, voff, soff, ret) \
     ({ void *vc_o_ = (void *)(objexpr); VCALL0(vc_o_, voff, soff, ret); })
#  define VCALL_SE(objexpr, voff, soff, ret, ptypes, ...) \
     ({ void *vc_o_ = (void *)(objexpr); VCALL(vc_o_, voff, soff, ret, ptypes, __VA_ARGS__); })
#endif

/* Member-thunk forms for de-virtualised classes (README "Design B"): the class carries an
 * explicit `vc_u32 __vptr;` member, so the compiler supplies VOFF (and any base-class
 * `this` conversion) itself.  Only valid inside a member function. */
#define VC_VPTR_MEMBER  vc_u32 __vptr
#define VCM0(ret, soff) \
    (((ret (VC_CC *)(void *))(*(const vc_u32 *)(this->__vptr + (vc_u32)(soff))))((void *)this))
#define VCM(ret, ptypes, soff, ...) \
    (((ret (VC_CC *) ptypes)(*(const vc_u32 *)(this->__vptr + (vc_u32)(soff))))((void *)this, __VA_ARGS__))
/* Typed slot pointer only (caller supplies every argument): struct returns
 * (`VCM_FN(void, (R *, void *, ..), soff)(&r, (void *)this, ..)`) and variadic
 * slots (`VCM_FN(R, (void *, ...), soff)((void *)this, args...)`). */
#define VCM_FN(ret, ptypes, soff) \
    ((ret (VC_CC *) ptypes)(*(const vc_u32 *)(this->__vptr + (vc_u32)(soff))))
/* Qualified forms: the class has several polymorphic bases (several __vptr
 * members); B names the primary base whose vptr the slot lives in. */
#define VCMQ_FN(B, ret, ptypes, soff) \
    ((ret (VC_CC *) ptypes)(*(const vc_u32 *)(this->B::__vptr + (vc_u32)(soff))))
#define VCMQ0(B, ret, soff)  (VCMQ_FN(B, ret, (void *), soff)((void *)this))
#define VCMQ(B, ret, ptypes, soff, ...) \
    (VCMQ_FN(B, ret, ptypes, soff)((void *)this, __VA_ARGS__))

/* Explicit vptr store, the spelling the decomp already uses in its "constructors"
 * (`o->vt = D_00471498;`).  Kept here so hand overrides use one form. */
#define VC_SET_VPTR(obj, voff, vtbl) \
    (*(vc_u32 *)((vc_u8 *)(obj) + (voff)) = (vc_u32)(vtbl))

#endif /* PORT_VCALL_H */
