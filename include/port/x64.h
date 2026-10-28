/* SPDX-License-Identifier: CC0-1.0
 *
 * x64 spellings of the strategy-A stages (docs/X64-PLAN.md).  Force-included
 * ahead of port/prelude.h in the x64 game build only (CMakeLists.txt,
 * RG_ARCH=x64); the i686 build never sees it.
 *
 *   RG_P32     a pointer stored in game memory keeps its i686 size: a 4-byte
 *              `__ptr32 __uptr` pointer (zero-extended on load).  Every host
 *              address of the x64 exe is below 2 GB (tools/x64/pecheck.py).
 *   RG_FPC(e)  call through an RG_P32 function pointer: cast to the ordinary
 *              function pointer type first (LLVM cannot lower a call through
 *              a __ptr32 function pointer; tools/stages/ptr32.py)
 */
#ifndef RG_PORT_X64_H
#define RG_PORT_X64_H
#if defined(_WIN64) || defined(__x86_64__)
#define RG_P32 __ptr32 __uptr
#define RG_FPC(e) ((__typeof_unqual__(*(e)) *)(e))
/* EE kernel calls that share a name with a kernel32 export: on i686 the Win32 ones are
 * stdcall-decorated (_CreateThread@24) and never collide; x64 names are undecorated.
 * The same renames are in src/sce/kernel/eekernel.h (the definitions). */
#define CreateThread    rg_ee_CreateThread
#define ExitThread      rg_ee_ExitThread
#define TerminateThread rg_ee_TerminateThread
#define SuspendThread   rg_ee_SuspendThread
#define ResumeThread    rg_ee_ResumeThread
/* Float sqrt rounds to NEAREST as on i686 (the CRT's x87 sqrtf there), not toward
 * zero under the guest MXCSR as an inlined sqrtss would (port/sqrtf_rn.h). */
#include "port/sqrtf_rn.h"
#define sqrtf(x)           rg_sqrtf_rn(x)
#define __builtin_sqrtf(x) rg_sqrtf_rn(x)
#else
#define RG_P32
#define RG_FPC(e) (e)
#endif
#endif
