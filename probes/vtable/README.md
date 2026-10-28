# mwcc vtable / virtual-call ABI — PLAN step 3 probe

Settled from retail evidence only: `../RGDecomp\asm\main.s` plus the overlay listings, and
the generated data C in `src/main_data/`. Nothing was compiled with mwcc; the matching
corpus is already byte-identical, so its dummy-class declarations are proven mwcc input.

## The rule

```
vtable  (generated data C, u32 D_xxxxxxxx[]):
   +0x0   RTTI word    0 in every game vtable; MSL library classes hold a typeinfo ptr
   +0x4   offset word  0 in every vtable observed, including secondary (MI) vtables
   +0x8   slot 0
   +8+4k  slot k
object:   vptr == &D_xxxxxxxx (the symbol itself, NOT an Itanium address point)
          vptr sits at VOFF = the bytes of data declared BEFORE the first virtual
          declaration (the first one in the root polymorphic class)
call:     lw $25, VOFF(this) ; lw $25, 8+4k($25) ; jalr $25 ; $4 = this
          this is the pointer the vptr was loaded through. A sub-object offset is
          folded into VOFF, and the call site never adjusts `this`.
sret:     hidden result pointer in $4, this in $5 (=> impl `void f(R *out, T *self, ...)`)
MI:       a secondary base has its own vptr at its sub-object offset. Its vtable slots
          are ordinary GAME functions that do `this -= delta; j impl` (decompiled C).
          There's no offset-word adjustment and no compiler thunk.
```

So `byte offset in vtable = 8 + 4*slot_index`, and the vptr points at the vtable symbol.
Itanium differs on all three counts: vptr at offset 0 or primary-base-first, address
point after offset-to-top/RTTI, and slot k at vptr+4k. So no dummy class can be compiled
as-is by clang.

## Evidence

Census over every `jalr` in every listing. A site is a vcall if `lw $25,K($25)` is
preceded by `lw $25,V($r)`:

| image | jalr | vcall-shaped | slot offset < 8 | slot offset not 4-aligned |
| --- | ---: | ---: | ---: | ---: |
| MAIN | 3,488 | 3,156 | 0 | 0 |
| factory / insect / normal | 40 / 109 / 149 | 40 / 108 / 141 | 0 | 0 |

The smallest slot offset seen is 0x8 (132 sites in MAIN). VOFF values in MAIN: 0 (2,312
sites), 0xC0 (256), 0x1B0 (137), 0x190 (87), 0xB0 (46), 0x68 (44), and others. The
non-vcall `jalr`s are plain C function pointers (`jalr $2/$3`) and are unaffected.

Six sites in different files, checked against source declarations and the data C:

| # | function (source) | retail sequence | declaration → slot | vtable data | this |
| --- | --- | --- | --- | --- | --- |
| 1 | ActionMgrFindLiftableInFrontMaybe_232de0 | `lw $25,0($21); lw $25,0xC0($25)` and `0x354` | `isBusy` = virtual #46 → 8+184=0xC0; `getInfo` #211 → 0x354 | — | unadjusted |
| 2 | MotionEventBlockAppendEvent_1b2370 (`class VT14 { u8 pad_[0x14]; virtual void f8(); }`) | `sw D_00471048,0x14($16); lw $25,0x8($2); jalr; daddu $4,$16` | #0 → 0x8; VOFF 0x14 = pre-virtual pad | `D_00471048 = {0, 0, &ListNodeClear_1b2270, 0,0,0}`: slot 0 is word 2, and the vptr is the symbol | obj, not obj+0x14 |
| 3 | CharaDeserialize_3a9c50 (`Item items[10]` embedded at +0x308) | `lw $25,0x308($2); lw $25,0x1C($25); jalr; addiu $4,$2,0x308`; `Self::v508` → `0x508` | Item #5 → 0x1C, #4 → 0x18; Self #320 → 0x508 | — | &items[k] (offset folded into VOFF) |
| 4 | HandleRegistryStepAll_314e10 (`B314e10 { pad0[0x84]; s16 m84; pad86[..0xB0]; virtual ... }`) | `lw $25,0xB0($4); lw $25,0x6C($25)`; `0x8` with `mov.s $f12` | `f6c` #25 → 0x6C, `f8(H*,f32)` #0 → 0x8 | — | unadjusted |
| 5 | CameraObjCtor_177430 (`B177430 { pad0[0xC0]; virtuals }`, derived `O177430`) | `sw D_00470090,0xC0($4); lw $25,0x44($2)`, then `sw D_00470340,0xC0`; later `0x48`, `0x4C` | Init #15 → 0x44, Params #16 → 0x48, Setup #17 → 0x4C | `D_00470090[2+15] = CameraBaseInit_15fc80`, `D_00470340[2+16] = CameraGetParamBlock_1601a0`; both headers {0,0} | unadjusted |
| 6 | MI ctor at 0x3EE2FC (12-byte object) | `sw D_00472260,0($17); sw D_0047227C,4($17)` | secondary vptr at +4 | `D_0047227C` = `D_00472260`+0x1C = `{0, 0, &CharaMgrPoolViewCountThunk_3b09c0, …}`; the thunk is `j CharaMgrPoolCount; addiu $4,$4,-4`. The offset word is still 0 | thunk does it |

The constructor scan covered every `lui/addiu D_x` followed by `sw` whose data has a
function pointer at word 2. It found 602 game vtables with header `{0,0}`. The only
non-zero word 0 belongs to 18 MSL classes (exception, bad_alloc, ios_base, streambuf,
filebuf, istream/ostream, string errors), where it holds an RTTI typeinfo pointer into
.rodata. Word 1 was 0 in all of them, including the iostream vptrs at +4/+8/+16/+24.
Other MI adjusters exist with the same shape: `DataTable*Thunk` (-0x88) and
`UnitChildViewGetNthThunk` (-0x230).

Evidence quality: **high** for the slot rule, the header and where the vptr points. They
rest on 3,445 sites, the data tables, and prior matching sessions
(memory `levers.d/jalr-is-cpp-virtual.md`: "slot = 8+4N" was verified on more than 100
units, one of them with 278 dummies). VOFF placement is **high** for the shapes in the
corpus: pad before the virtuals, virtuals before data, and derived data after the base
vptr. Slot numbering for a derived class that ADDS new virtuals is **unverified** (no
example was examined; see the open questions).

## Related mechanisms

- **Constructors and destructors** in the corpus are almost all plain C with explicit vptr stores
  (`o->vt = D_00471498;`, and the "two consecutive vptr stores" destructor family). These
  work unchanged on i686. **Exactly one real C++ constructor exists**:
  `CameraObjCtor_177430.cpp` (`O177430::O177430()`). Its compiler-emitted vtables are
  aliased to retail data (`config/aliases.txt`: `__vt__7B177430 = 0x470090`,
  `__vt__7O177430 = 0x470340`), so it needs an **override** that spells the two
  `VC_SET_VPTR` stores. Inline constructors in dummy classes (`A() { Init(); }`) have no
  callers. Placement `new (heap) T` is used in about 4 files (`MapAreaStartLoad_1d8370`,
  `ObjListInstantiateByName_1890b0`, `EventVoiceListInit_24f580`, …), and their constructors
  store vptrs explicitly.
- **Pointer-to-member**: `__ptmf_scall` = `PtmfScall_100e70` has one call site, in
  `SaveModeDispatch_375df0` (`(arg0->*D_00463840[idx])()`). The MW PMF is 12 bytes:
  `{s32 this_delta; s32 vtbl_off (<0 = non-virtual); u32 fn | vptr_off}`. The dispatch
  is: `this += delta; fn = vtbl_off < 0 ? w2 : *(*(this + w2) + vtbl_off)`. Clang's
  Itanium PMF is 8 bytes, so this file needs an **override** that spells a
  `struct MwPmf` + `__ptmf_scall` in C. The table is filled at runtime by
  `StaticInitSaveSys_46d9f0`, which copies it from .sdata `D_0047F9F8…`.
- ⚠ **Function pointers hidden in f32 data.** Those .sdata words are copied with
  `lwc1/swc1`, so data2c typed them `f32`. For example,
  `D_0047FA00[0] = 5.08189296e-39f` is the bit pattern `0x00375640` = `McGetInfoStep_375640`.
  A scan of `src/main_data` for denormal floats whose bits fall in 0x100000–0x2000000
  finds **17**: 11 PMF targets (`D_0047FA00…D_0047FAA0`), 2 `MapCmd*` functions
  (`D_0047E424`, `D_0047E434`), and 4 data pointers (`D_0047E010/14`, `D_0047F240/44`).
  On the port these stay literal PS2 addresses. data2c (or a transform) must turn them
  into `(u32)&sym`, and the copy code must not go through x87. `-mfpmath=sse` moves
  are bit-exact; an x87 `fld` would quiet an sNaN.
- **Static constructors**: `MainStaticInit_100580` calls `RunStaticCtors_100df0` over
  `[D_0046F9C0, D_0046FD64)`, which is generated data C: `u32 D_0046F9C0[233] =
  {(u32)&StaticInit…, …}`. The first two entries are `D_00469140+0x40/+0x50`, code with
  no symbol of its own. The constructors are ordinary C functions (`StaticInit*_46xxxx.c`).
  They register global destructors through `RegisterGlobalObject_100dc0`, a linked
  list that `DestroyGlobalChain_100d60` walks. The port's startup only has to walk the u32
  table and call each entry. Overlays use the same `RunStaticCtors_100df0` from
  `OverlayLoadFile_100410`, with the ctor/dtor ranges in the MWo3 header (transform 7).
  No `.ctors`/`__sinit` section machinery is involved.
- **Explicit C vtable calls** (`vtbl = *(void **)p; ((fn)vtbl[k])()`, about 280 files)
  already include the 8-byte header in their index arithmetic, so they're correct
  against the data C on i686 as they are.

## Port design

### Design B (recommended): de-virtualise the class declarations, leave call sites alone

Dummy virtual classes appear only in `.cpp` files: 1,740 of them, with about 112k
`virtual` declarations, most of them `void vN()` padding. The transform rewrites each
polymorphic class declaration and doesn't touch any call site:

1. In the root polymorphic class, replace the first virtual declaration's position with
   `VC_VPTR_MEMBER;` (`vc_u32 __vptr`). Every `virtual` keyword then goes away. The class
   is now non-dynamic, so clang lays it out in declaration order, as mwcc did. This also
   fixes `struct Top : Pad88, List`, which Itanium would reorder to put the dynamic base
   first.
2. Slot index k: root virtuals are numbered in declaration order. In a derived class, a
   redeclaration with the same name and parameters keeps the base's slot, and the
   redeclaration is **dropped** so the inherited thunk serves it. A new virtual gets
   `base_count + i` (unverified, see below).
3. Each virtual that is referenced in the TU becomes an inline thunk, and unreferenced
   `vN` dummies are deleted:

   | declared | emitted |
   | --- | --- |
   | `virtual void f(A a, B b);` | `void f(A a, B b) { VCM(void, (void *, A, B), SOFF, a, b); }` |
   | `virtual void f();` | `void f() { VCM0(void, SOFF); }` |
   | `virtual R f(...)` with R scalar or pointer | `R f(..) { return VCM(R, (void *, ..), SOFF, ..); }` |
   | `virtual bool f(..)` | `bool f(..) { return (vc_u8)VCM(vc_u32, ..) != 0; }` (mwcc tests the low byte: `andi $2,0xFF`) |
   | `virtual S f(..)` with S a struct (`Bits48`, `Mask64`, …) | `S f(..) { S r; VC_FN(void, (S *, void *, ..), this, VOFF, SOFF)(&r, this, ..); return r; }` |
   | `virtual R f(...)` (8 files) | `template <class... A> R f(A... a) { return VCM(R, (void *, A...), SOFF, a...); }` |

   Unnamed parameters get names `a0..an`, and default arguments are kept. `SOFF = 8+4k`
   is written as a literal. `VCM*` uses `this->__vptr`, so VOFF, embedded objects
   (`items[k].f()`) and MI `this` conversion all come from the compiler.
4. Emit `static_assert(offsetof(Root, __vptr) == VOFF)` for each class whose VOFF the
   retail census knows. That pins our reimplementation of mwcc's placement rule.
5. Classes that have a user constructor or destructor that is ODR-used, and anything
   using `->*`/`.*`, are reported and routed to `overrides/`. Today that's the two files
   named above.

Why this design over rewriting each call site with `VCALL(obj, voff, soff, …)`:

- It touches about 1,740 class bodies, which follow a fixed pattern, instead of 3,445
  call expressions. Those expressions would need a real C++ expression parser, because
  the object can be `GetX()->`, `self->items[k].`, or an MI-converted pointer.
- `this` is evaluated once, with no GNU statement-expressions.
- The layout of every non-virtual member stays as mwcc had it.
- The calling convention is pinned per thunk (`VC_CC` cdecl), so MSVC-style `__thiscall`
  can't leak into a slot call.

### Design A (VCALL at call sites): kept for hand code

`vcall.h` provides the plan's form for overrides and C:
`VCALL0(obj, voff, soff, ret)`, `VCALL(obj, voff, soff, ret, (ptypes incl. this), args…)`,
`VCALL_THIS(obj, voff, soff, ret, ptypes)(full args)` for sret and irregular cases,
`VCALL_BOOL*`, `VC_SET_VPTR`, `VC_SLOT_OFF(k)`. `obj` is evaluated twice. The `*_SE`
statement-expression forms evaluate it once, but only under clang/gcc.

### Verification for the transform

For each rewritten function, compare the multiset of `SOFF` values of the thunks it
calls against retail's `lw $25,K($25)` multiset for that symbol (from the listing, as
`vcensus.py` reads it), and the VOFF values against `lw $25,V($obj)`. A mismatch means
the tool's slot or placement model is wrong for that class. mwcc itself already matched,
so the source is not the suspect.

## Files

- `vcall.h`: the macro set.
- `test_vcall.c`: fake vtables in data2c spelling, covering cases 1–6 plus sret, bool
  low byte, an f32 argument and return, and single evaluation.
- `test_devirt.cpp`: Design B output for VT14, Item/Self (embedded array), B/O177430
  (derived class plus the constructor override) and an MI pad-base, with layout
  `static_assert`s.
- `build_msvc.cmd` and `build_clang.cmd`. **MSVC x86 (VS2019): both tests PASS.** clang
  wasn't installed yet (`../tools\llvm\bin\clang.exe` absent). Run `build_clang.cmd`
  once it is.

## Open questions and hazards

1. **Derived classes that add new virtuals.** Is the slot `base_count + i`, and does a
   derived class with a non-polymorphic base put its vptr after the base data? The
   census cross-check settles it per function. No counter-example is known.
2. **Return-type agreement between the call site and the implementation.** If a dummy
   declares `f32` but the implementation returns `s32`, or the reverse, i686 leaves the
   x87 stack unbalanced: `f32` comes back in `st(0)` even with `-mfpmath=sse`. Screen
   for this by joining every (vtable, slot) in the data C to the implementation's
   definition, then comparing against the dummy's return type. Do the same for
   struct-returning implementations, which should be `(R *out, T *self, …)`.
3. **Under-argued virtual calls.** The dummy can declare fewer parameters than the
   implementation. cdecl tolerates this, but the callee reads garbage. Same class of
   problem as transform 2.
4. **Variadic dummies** (`virtual s32 f(...)`, 8 files). mwcc promoted f32 to double. The
   template thunk does not promote, so check what those implementations actually take.
5. **Class-level `operator new` that can return 0** (`MemStackNew` in the placement-new
   files). Clang assumes a non-`noexcept` allocator never returns null and skips the
   null check before the constructor. Build with `-fcheck-new`, or mark those operators
   `noexcept`.
6. **The f32-encoded pointers** (17 words, above) need a data2c or ingest fix before the
   PMF table or `MapCmd*` can work.
7. **x64 (P7).** The vtables are u32 arrays, so slots can't hold 64-bit pointers. That
   becomes part of the handle/translation work.
