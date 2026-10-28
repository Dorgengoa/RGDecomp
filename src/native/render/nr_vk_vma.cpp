/* SPDX-License-Identifier: CC0-1.0 */
/* The Vulkan Memory Allocator's implementation (third_party/vma, MIT) for the Vulkan backend
 * (nr_vulkan.cpp, docs/NATIVE-VULKAN.md), in its own translation unit.  Functions come from volk
 * (dynamic loading: no link-time Vulkan dependency). */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY && defined(RG_HAVE_VULKAN)
#include "volk.h"
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
#endif
