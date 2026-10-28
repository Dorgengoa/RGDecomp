/* SPDX-License-Identifier: CC0-1.0
 * RG_THREADS_ORACLE (docs/NATIVE-THREADS.md "Native-only"; docs/NATIVE-ONLY.md): 1 in a
 * default build, where the EE kernel HLE (src/ps2/kernel) is linked and RG_THREADS=hle |
 * service | frame select it (the oracle); 0 in an RG_NATIVE_ONLY build, where rg-game links
 * the native kernel table only (rg_native_kernel_ps2k): the HLE modes, the service-thread
 * registry and the kernel census recorder are compiled out (preprocessor, not dead-code
 * elimination). */
#ifndef RG_THREADS_ORACLE_H
#define RG_THREADS_ORACLE_H

#ifndef RG_THREADS_ORACLE
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
#define RG_THREADS_ORACLE 0
#else
#define RG_THREADS_ORACLE 1
#endif
#endif

#endif
