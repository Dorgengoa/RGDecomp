/* SPDX-License-Identifier: CC0-1.0
 *
 * Float sqrt rounds to NEAREST as in the Windows i686 exe (a call to the CRT's x87 sqrtf), not
 * toward zero under the guest MXCSR as an inlined sqrtss would (port/sqrtf_rn.h).  Force-included
 * into the game objects and the VU0 libraries of the Linux and (since 2026-11-10) Windows i686 builds (cmake/game.cmake,
 * CMakeLists.txt; docs/LINUX.md "Float sqrt"); the x64 build gets the same mapping from port/x64.h.
 */
#ifndef RG_PORT_SQRTF_MAP_H
#define RG_PORT_SQRTF_MAP_H
#include "port/sqrtf_rn.h"
#if defined(_WIN32) && defined(__i386__)
/* Windows i686 (2026-11-10, VS 2022 toolset; docs/TOOLCHAIN.md "MSVC toolset"): the UCRT's x86
 * math.h DEFINES sqrtf inline ((float)sqrt(x)); seen after the mapping below it would become a
 * second definition of rg_sqrtf_rn.  Include it first (a TU that includes it later gets the
 * include guard). */
#include <math.h>
#endif
#define sqrtf(x)           rg_sqrtf_rn(x)
#define __builtin_sqrtf(x) rg_sqrtf_rn(x)
#endif
