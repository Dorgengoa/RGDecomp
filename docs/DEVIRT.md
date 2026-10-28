# Transform 3: de-virtualisation (`tools/stages/devirt.py`)

PLAN.md transform 3, probes/vtable/README.md "Design B". The decomp reaches game code
through mwcc dummy classes (`class Unit { virtual void v0(); ... }`) whose slot numbers
were chosen so that mwcc emitted retail's `lw $25,VOFF(obj); lw $25,8+4k($25); jalr`.
Clang lays out dynamic classes differently (Itanium/MSVC vptr placement, no 8-byte
header), so the stage turns every such class into a plain class with an explicit vptr
member and inline thunks that dispatch through the game's own vtables (generated data C,
`u32 D_xxxxxxxx[]`). **Call sites are not touched.**

Stage order: `... protos, dialect, devirt, spin, hwaccess`. It runs on every `.cpp` unit
and on `include/*.h` files that declare virtuals (`camera_cpp.h`, `worldobj_cpp.h`).
Macros: `include/port/vcall.h` (promoted from the probe; force-included via
`port/prelude.h`).

## Rules

| What | Rule |
| --- | --- |
| vptr | The root polymorphic class's first virtual becomes `VC_VPTR_MEMBER;` (`vc_u32 __vptr`) at the same position (`public: VC_VPTR_MEMBER; <access>:` when the label there is not public). The class is then non-dynamic, so clang lays it out in declaration order, as mwcc did. |
| slots | Root virtuals in declaration order. A derived class starts from its primary (first polymorphic) base's table; a redeclaration with the same name and parameter types (C++ override rule, typedefs canonicalised) keeps the base slot and is dropped (re-emitted only for a covariant return); a new virtual gets `base_count + i`. Non-`virtual` redeclarations that match a base virtual are overrides too. |
| thunks | A virtual whose name occurs in the TU becomes `R f(P) { return VCM(R, (void *, P), 8+4k, args); }` (`VCM0` with no args); unreferenced placeholders are deleted (115,914). `bool`: `(vc_u8)VCM(vc_u32, ..) != 0` (mwcc tests the low byte). Struct return: `R r; VCM_FN(void, (R *, void *, P), soff)(&r, this, args)` (result pointer first). `f(...)`: `template <class... VcA> R f(VcA...)` through a `(void *, ...)` slot type, so default promotions apply as on mwcc; a class holding one inside an `extern "C" {}` block is wrapped in `extern "C++" { }` (17). Several polymorphic bases: `VCMQ*` with `this->Primary::__vptr`. |
| macros | Virtuals declared through macros (`#define V1(n) virtual void v##n();`, `V4`, `V16`; 9 files, 2,112 uses) are expanded in place first. |
| lines | Every rewritten member keeps its newlines, so line numbers (and `#line`) are unchanged. |
| linkage (a) | A game-symbol function definition (`*_xxxxxx`) with C++ linkage, and its earlier namespace-scope declarations, get `extern "C"` (1: `EffectEntryBuildChr_2dc0f0`). |
| linkage (b) | Namespace-scope `extern` data declarations outside `extern "C"` (the dialect stage's `rgp_anon_` structs included) get `extern "C"` (1,466). A block-scope `extern` gets a namespace-scope `extern "C"` twin in front of its function (0 in the corpus). |
| idempotent | The output has no `virtual`; every rewritten name already has C linkage. |

Outputs: `game/DEVIRT.tsv` (one row per class slot: file, line, class, vptr owner, slot,
`soff`, return kind, emitted) and `game/DEVIRT_FLAGS.tsv`.

Census at 2efa6b43: 1,683 files, 1,935 vptrs inserted, 3,169 thunks emitted (1,486 void,
1,618 scalar/pointer, 43 bool, 5 struct-return, 17 variadic), 3 overrides dropped. **No
class in the corpus adds new virtuals in a derived class, and none has two polymorphic
bases**, so the `base_count + i` rule (README open question 1) is implemented and
unit-tested but never exercised by real code.

## Verification against retail (`tools/devirt_verify.py`)

For every C++ unit, the virtual-call sites of the **compiled port object** are compared
with retail's:

- **retail**: `lw $25,V($r); lw $25,S($25); jalr|jr $25` over the unit's symbols, from
  SCUS_974.90 / BIN/*.BIN (read through `tools/census/platform/common.py`). Range = symbol
  to the next symbol or `glabel` of the pinned listings, so a multi-entry unit's interior
  entries are scanned. Also `lw $25,S(&D_vtbl)` (vptr known after a store).
- **port**: `movl V(%r),%x; calll|jmpl *S(%x)` (and the `movl S(%x),%y; calll *%y` form)
  in the i686 object, via `llvm-objdump -d -r`.
- Both sides run a forward must-dataflow over register definitions (branches, MIPS delay
  slots and branch-likely, call clobbers, stack spills), so vptr loads in delay slots,
  hoisted out of loops, or spilled are found. Clang-specific shapes are decoded: a
  store-forwarded vptr (`calll *D_vtbl+S`), tail-merged calls (`vptr+k` per path),
  and switch-to-lookup-table slots (`calll *(%vt,%idx)`, table read from `.rdata`).

Per unit: `match` (equal multisets), `set-match` (same (V,S) pairs, a site duplicated or
merged by one compiler), `dyn-slot` (a slot computed at run time by clang's lookup table
that could not be fully decoded), `voff-fold` (same slots; V differs only in how the
object address was formed), else `port-fewer` / `port-more` / `mismatch`.

Result: see "Results" below. Port side = the real game objects (-O1).

Controls (`--fault`): every port slot offset +4, or every V +4, must make every unit with
perturbable sites fail. Both are ARMED (`ctest -L devirt`: `devirt.verify_control_slot`,
`devirt.verify_control_voff`).

## Overrides and open items

- `CameraObjCtor_177430` (the one real constructor): **written**,
  `overrides/src/main/camera/CameraObjCtor_177430.cpp` — `extern "C" void
  CameraObjCtor_177430(O177430 *)` with `VC_SET_VPTR(o, 0xC0, D_00470090); o->Init();
  VC_SET_VPTR(o, 0xC0, D_00470340);` then the body. Its retail sites match.
- `SaveModeDispatch_375df0` (`__ptmf_scall`, the one pointer-to-member call): **listed,
  not written**. It compiles with clang's 8-byte PMF but is wrong at run time: mwcc's PMF
  is 12 bytes `{this_delta, vtbl_off, fn|vptr_off}` and the table `D_00463840` is filled
  by `StaticInitSaveSys_46d9f0` from f32-typed .sdata words (README hazard 6). Needs a
  `struct MwPmf` + C `__ptmf_scall` and the data2c re-typing.
- Struct-return thunks (5) assume the implementation takes `(R *out, T *self, ...)`. A C
  implementation written `R f(T *self)` with an 8-byte R would return in EAX:EDX on
  i686-msvc: screen the 5 slot implementations once data C exists (README question 2).
- Expected disagreement (`tests/devirt/expected_mismatch.tsv`), not a devirt error:
  `HandleRegistryInsert_314f80` (clang proves `Handle::operator=`'s release path dead on a
  just-tested null handle). `SaveHeaderBuild_3e5520` now matches: protos
  `def-tail-vcall-return` makes `CharaGetIconRecMaybe_3ae3e0` return its slot-0x340
  call's value (retail `$v0`), so the three virtual calls on the record are live.

## Tests (`tests/devirt`, `ctest -L devirt`)

| Test | Checks |
| --- | --- |
| `layout` | stage output for `fixtures/synthetic.cpp` (pad-before-vptr, data after the virtuals, override, derived new virtual, MI with a pad base, bool, struct return, variadic, macro virtuals, variadic inside `extern "C"`, data/function linkage): `static_assert` offsets + dispatch through fake data2c-style vtables |
| `layout_control` (WILL_FAIL) | the same with every vtable one slot off |
| `stage_<fixture>` ×5 | the stage is idempotent on 5 real snapshot files; their outputs compile with the game flags (`rg_devirt_fixtures`) |
| `verify`, `verify_control_slot`, `verify_control_voff` | the retail cross-check on the built game objects and its two armed controls (exit 77 = objects not built) |

## Link readiness (`tools/link_readiness.py`)

`llvm-nm` over the compile set (MANIFEST unit/data, `overrides/` replacing `game/`;
stale objects ignored), every undefined symbol no game object defines is classified
into `build/i686-windows/link_readiness.tsv` (symbol, class, refs, example object,
detail). Strong duplicate definitions are listed as `duplicate-def` (COMDAT literals
excluded).

## Results (2efa6b43, 2026-10-12)

**Ingest**: stages `int128, gccvarargs, vu0asm, asmexclude, ovlsyms, protos, dialect,
devirt, spin, hwaccess`; a second run writes 0 files; `--check` 0 manifest problems.
`ovlsyms` 3,417 renames in 564 files, 0 errors; `hwaccess` 84 rewrites in 31 files,
0 errors; protos `overlay-import-bound` 193, `overlay-import-disagree` 3 (ret only),
`overlay-import-per-site` 12, `addr-alias` 987, `hosted-unstatic` 4 (PROTOS.md);
`ingest.py` exits 0, 193 overrides current.

**Compile**: `tools/gameerrors.py`: 0 failed objects, 0 errors.

**Retail cross-check**: 1,957 C++ units, 1,689 with virtual calls (3,537 retail sites,
3,496 port sites): match 1,627, set-match 28, voff-fold 26, dyn-slot 7 → **1,688 / 1,689
= 99.94 % agree**; the other is the expected entry above (not a slot or layout error). Both fault controls ARMED (slot+4: 1,688/1,688 caught; V+4:
1,623/1,623). Details per unit: `build/i686-windows/devirt_verify.tsv`.

**Link readiness** (18,587 objects, 20,502 defined, 9,119 unresolved; was 10,103):

| Class | Symbols | What closes it |
| --- | ---: | --- |
| data-missing (`D_xxxxxxxx`) | 7,861 | data C (the snapshot predates data2c d784320c) |
| overlay-data-missing (`<ov>_D_…`) | 459 | overlay data C / arena (overlay manager) |
| excluded-asm:sdk / :game / :library | 261 / 90 / 56 | `src/sce` bindings and overrides (game/EXCLUDED.tsv) |
| overlay-import (`func_` at an overlay address) | 205 | overlay registry (`gen_overlay_registry.py`) |
| asm-only-unit | 142 | MAIN functions still linked from asm/main.s in this snapshot |
| other | 18 | MAIN symbols with no compiled definition (`InvAddItemCoreMaybe_3c6540`, `PathLocalize_1c28c0`, `NameTableRegisterImArchive_1594d0` (now reached by name), …), `gEventContext`/`gSystemVm` (named data) |
| port-runtime | 16 | `hw_*` (rg_ps2_hwbus), `rg_movie_g_*`, `rg_ovl_data_ptr`, `rg_spin_*`, `rg_vu0` |
| main-address-alias | 7 | was 993: protos `addr-alias` renames the rest to the MAIN symbol / C interior entry. Left: kernel-RAM addresses called by the SDK kernel patch (`func_0743C8`, `func_076038`, `func_076160`, `func_076460`), interior entries with no C entry (`func_207A90` in `TaskLoadSound_207a80`, `func_3930D0` in `InsectUiRosterRowSetTextMaybe_393020`), `func_00436980` (no symbol/label) |
| crt | 4 | libcmt (`_chkstk`, `_fltused`, `sqrt`, `sqrtf`) |
| hosted-static | 0 | was 4: protos `hosted-unstatic` |
| **cxx-mangled** | **0** | (was 1,082 data refs + 1 function before the linkage rules) |
| duplicate-def | 0 | |
