/* Address-literal accessors (PLAN.md transform 5, docs/HWBUS.md).
 *
 * The `hwaccess` ingest stage (tools/stages/hwaccess.py) rewrites the game's
 * literal-address idioms into these spellings and includes this header in
 * each file it changes.  Freestanding: no system headers (game files declare
 * their own libc prototypes); the hw_* functions live in src/ps2/hwbus.
 *
 *   *(volatile T *)0x1000xxxx         ->  ((T)HW_R32(0x1000xxxxu))      rvalue
 *   *(volatile T *)A = v;             ->  HW_W32(A, v);                 store
 *   *(volatile T *)A op= v;           ->  HW_W32(A, (T)HW_R32(A) op (v));
 *   (T *)0x7000xxxx                   ->  (T *)PS2_SPR(0xxxxx)           scratchpad
 *   p & 0x0FFFFFFF  (DMA address)     ->  (p)                            identity
 *   p | 0x20000000  (uncached)        ->  (p)                            identity
 *   p | 0x30000000  (uncached accel.) ->  (p)                            identity
 *   *(T *)0x5273C2  (overlay memory)  ->  (*(T *)((unsigned char *)D_00527020 + 0x3A2))
 *   HW_* on T0 / GS privileged / VIF1_FBRST  ->  rg_logic_t0_*, rg_gs_reg_r64/w64(RG_GS_<REG>),
 *                                                rg_vif1_fbrst_w32 (the native services)
 *
 * The mirror/mask sites are the identity on purpose: in the i686 build a DMA
 * address IS the host pointer (docs/DMAC.md "Address mapping", host mode), so
 * stripping or adding segment bits would corrupt it.  Since 2026-10-25 (D9 gate
 * `native_only.addr_census`) the stage strips them to the operand; the
 * PS2_PHYS / PS2_UNCACHED / PS2_UCAB markers below stay defined (identity) for
 * hand-written code, and the stage's HWACCESS.tsv lists every stripped site.
 */
#ifndef RG_PORT_HWACCESS_H
#define RG_PORT_HWACCESS_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned char      hw_r8(unsigned int addr);
unsigned short     hw_r16(unsigned int addr);
unsigned int       hw_r32(unsigned int addr);
unsigned long long hw_r64(unsigned int addr);
void               hw_r128(unsigned int addr, void *out16);
void hw_w8(unsigned int addr, unsigned char v);
void hw_w16(unsigned int addr, unsigned short v);
void hw_w32(unsigned int addr, unsigned int v);
void hw_w64(unsigned int addr, unsigned long long v);
void hw_w128(unsigned int addr, const void *in16);
unsigned char *hw_spr_base(void);
void *rg_ovl_data_ptr(const char *ovl, const char *sym, unsigned int sym_addr,
                      unsigned int off);
/* the game's timer-0 frame clock over native logic time (below, HW_R32 / HW_W32) */
unsigned int rg_logic_t0_count(void);
void rg_logic_t0_set_count(unsigned int v);
void rg_logic_t0_set_mode(unsigned int mode);
/* the renderer's display / GS control registers and the VIF1 stall cancel (below, HW_R64 /
 * HW_W64 / HW_W32): native display state, src/native/render/nr_hw.c */
unsigned long long rg_gs_priv_r64(unsigned int addr);
void rg_gs_priv_w64(unsigned int addr, unsigned long long v);
void rg_vif1_fbrst_w32(unsigned int v);
/* The same GS privileged registers by REGISTER ID (D9: what the hwaccess stage emits at the
 * game's sites, so the game names no PS2 address; tools/stages/hwaccess.py NATIVE_REGS).  The id
 * is the register's slot in the renderer's register block (nr_gs.h preg[]): 0-14 the display
 * block, 16+ the CSR block.  Native-only: src/native/render/nr_hw.c; oracle: src/ps2/hwbus. */
unsigned long long rg_gs_reg_r64(unsigned int reg);
void rg_gs_reg_w64(unsigned int reg, unsigned long long v);

#ifdef __cplusplus
}
#endif

#define RG_GS_PMODE     0u
#define RG_GS_SMODE1    1u
#define RG_GS_SMODE2    2u
#define RG_GS_SRFSH     3u
#define RG_GS_SYNCH1    4u
#define RG_GS_SYNCH2    5u
#define RG_GS_SYNCV     6u
#define RG_GS_DISPFB1   7u
#define RG_GS_DISPLAY1  8u
#define RG_GS_DISPFB2   9u
#define RG_GS_DISPLAY2  10u
#define RG_GS_EXTBUF    11u
#define RG_GS_EXTDATA   12u
#define RG_GS_EXTWRITE  13u
#define RG_GS_BGCOLOR   14u
#define RG_GS_CSR       16u
#define RG_GS_IMR       17u
#define RG_GS_BUSDIR    20u
#define RG_GS_SIGLBLID  24u

/* Timer 0 is the game's frame clock (T0_MODE = 0x83: horizontal lines; read / reset by
 * GfxEndFrame, GfxFlipBuffersMaybe, Vif1IntcHandler, set up by GfxSysInit).  Those
 * accesses go to the native logic-time clock (src/native/threads/rg_logic_time.c,
 * docs/NATIVE-CPU.md section 8), not the bus.  Every site passes a literal address, so the
 * compare folds and a non-timer site references only the hw_* call.  (Declared in the
 * extern "C" block above.) */
#define RG_HW_T0_COUNT 0x10000000u
#define RG_HW_T0_MODE  0x10000010u

#define HW_R8(a)     hw_r8((unsigned int)(a))
#define HW_R16(a)    hw_r16((unsigned int)(a))
#define HW_R32(a)    ((unsigned int)(a) == RG_HW_T0_COUNT ? rg_logic_t0_count() : hw_r32((unsigned int)(a)))
/* GS privileged registers (PMODE, DISPFB1, DISPLAY1: GsDbufPutEnv_144150, SysInitHardware_15e670;
 * CSR: GfxVblankStartHandler_15df20) and VIF1_FBRST (Vif1IntcHandler_15e170's stall cancel) go to
 * the renderer (src/native/render/nr_hw.c, docs/NATIVE-RENDER.md "Hardware register sites"),
 * not the bus.  Literal addresses: the range compare folds. */
#define RG_HW_GS_PRIV(a) ((unsigned int)(a) - 0x12000000u < 0x2000u)
#define RG_HW_VIF1_FBRST 0x10003C10u
#define HW_R64(a)    (RG_HW_GS_PRIV(a) ? rg_gs_priv_r64((unsigned int)(a)) : hw_r64((unsigned int)(a)))
#define HW_W8(a, v)  hw_w8((unsigned int)(a), (unsigned char)(v))
#define HW_W16(a, v) hw_w16((unsigned int)(a), (unsigned short)(v))
#define HW_W32(a, v)                                                                     \
    ((unsigned int)(a) == RG_HW_T0_COUNT     ? rg_logic_t0_set_count((unsigned int)(v)) \
     : (unsigned int)(a) == RG_HW_T0_MODE    ? rg_logic_t0_set_mode((unsigned int)(v))  \
     : (unsigned int)(a) == RG_HW_VIF1_FBRST ? rg_vif1_fbrst_w32((unsigned int)(v))     \
                                             : hw_w32((unsigned int)(a), (unsigned int)(v)))
#define HW_W64(a, v)                                                         \
    (RG_HW_GS_PRIV(a) ? rg_gs_priv_w64((unsigned int)(a), (unsigned long long)(v)) \
                      : hw_w64((unsigned int)(a), (unsigned long long)(v)))
#ifdef RG_PORT_U128_H
static inline rg_u128 hw_r128v_(unsigned int a) { rg_u128 r; hw_r128(a, &r); return r; }
#define HW_R128(a)    hw_r128v_((unsigned int)(a))
#define HW_W128(a, v) do { rg_u128 hw_t_ = (rg_u128)(v); hw_w128((unsigned int)(a), &hw_t_); } while (0)
#endif

/* scratchpad: offset into the DMAC model's 16 KB SPR (a host pointer) */
#define PS2_SPR(off) ((void *)(hw_spr_base() + ((unsigned int)(off) & 0x3FFFu)))
/* segment mirrors / masks on DMA addresses: identity in host mode */
#define PS2_PHYS(p)     (p)
#define PS2_UNCACHED(p) (p)
#define PS2_UCAB(p)     (p)

/* MAIN reading/writing overlay memory by literal address.  `ovl` is the
 * overlay name, `sym` the overlay symbol that holds the address (from
 * config/<ovl>.symbols.txt / names.txt), `symaddr` its retail address and
 * `off` the byte offset into it.  An lvalue.  The OVERLAY MANAGER must
 * resolve it (hwbus_set_ovl_resolver): host address of `sym` while `ovl` is
 * resident; otherwise the access goes to a scratch slot and is reported. */
#define RG_OVL_DATA(T, ovl, sym, symaddr, off) \
    (*(T *)rg_ovl_data_ptr(#ovl, #sym, (unsigned int)(symaddr), (unsigned int)(off)))

#endif
