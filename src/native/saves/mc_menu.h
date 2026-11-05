/* SPDX-License-Identifier: CC0-1.0 */
/* The settings overlay's save manager on the card model (docs/SAVES.md "Saves in the
 * settings overlay"): rg_menu_set_saves(menu, mc_menu_ops()).  mccard_init first. */
#ifndef RG_MC_MENU_H
#define RG_MC_MENU_H

#include <stddef.h>

#include "rg_menu.h"

#ifdef __cplusplus
extern "C" {
#endif

const rg_menu_saves_ops *mc_menu_ops(void);
/* where the picker starts: $RG_IMPORT_DIR, else PCSX2's memcards folder (Documents\PCSX2\
 * memcards; ~/.config/PCSX2/memcards), else the current folder */
void mc_menu_start_dir(char *out, size_t cap);

#ifdef __cplusplus
}
#endif
#endif
