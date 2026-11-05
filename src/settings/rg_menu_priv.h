/* SPDX-License-Identifier: CC0-1.0 */
/* Internal: what rg_menu.c and rg_menu_saves.c (the save manager views) share. */
#ifndef RG_MENU_PRIV_H
#define RG_MENU_PRIV_H

#include "rg_menu.h"

#if defined(__GNUC__) || defined(__clang__)
__attribute__((format(printf, 2, 3)))
#endif
void rg_menu__status(rg_menu *m, const char *fmt, ...);
/* one line (no formatting) / one hint line with prompt tags expanded */
void rg_menu__line(rg_menu_line *l, int *k, int cap, bool sel, bool header, const char *text, int indent);
void rg_menu__hint(const rg_menu *m, rg_menu_line *l, int *k, int cap, const char *tmpl);
/* the text editor for target RG_MENU_TEXT_* other than a setting */
void rg_menu__open_text(rg_menu *m, int target, const char *initial);

/* rg_menu_saves.c */
void rg_menu__saves_open(rg_menu *m, int view);
void rg_menu__saves_command(rg_menu *m, rg_menu_cmd cmd);
int rg_menu__saves_render(const rg_menu *m, rg_menu_line *l, int cap);
void rg_menu__saves_text_done(rg_menu *m, int commit);
void rg_menu__saves_text_title(const rg_menu *m, char *out, size_t cap);

#endif
