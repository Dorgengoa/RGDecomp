/* SPDX-License-Identifier: CC0-1.0
 *
 * Float sqrt rounds to NEAREST as in the Windows i686 exe (a call to the CRT's x87 sqrtf), not
 * toward zero under the guest MXCSR as an inlined sqrtss would (port/sqrtf_rn.h).  Force-included
 * into the game objects and the VU0 libraries of the Linux i686 build (cmake/game.cmake,
 * CMakeLists.txt; docs/LINUX.md "Float sqrt"); the x64 build gets the same mapping from port/x64.h.
 */
#ifndef RG_PORT_SQRTF_MAP_H
#define RG_PORT_SQRTF_MAP_H
#include "port/sqrtf_rn.h"
#define sqrtf(x)           rg_sqrtf_rn(x)
#define __builtin_sqrtf(x) rg_sqrtf_rn(x)
#endif
