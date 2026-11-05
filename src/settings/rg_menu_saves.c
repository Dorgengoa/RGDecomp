/* SPDX-License-Identifier: CC0-1.0 */
/* The save manager views of the settings menu (docs/SAVES.md "Saves in the settings
 * overlay"): the saves of a card with their names and summaries (rename), and the import
 * from a PCSX2 memory card (typed path or file picker, target card, per-save import with a
 * replace confirmation).  Pure: every card / file operation goes through the host's
 * rg_menu_saves_ops (src/native/saves/mc_menu.c). */
#include <stdio.h>
#include <string.h>

#include "rg_menu.h"
#include "rg_menu_priv.h"

void rg_menu_set_saves(rg_menu *m, const rg_menu_saves_ops *ops) { m->saves = ops; }

static void sv_load(rg_menu *m)
{
    char msg[256] = "";
    m->sv_n = m->saves->list(m->saves->user, m->sv_card, m->sv, RG_MENU_MAX_SAVES, msg, sizeof msg);
    if (m->sv_n > RG_MENU_MAX_SAVES) m->sv_n = RG_MENU_MAX_SAVES;
    if (m->sv_n < 0) rg_menu__status(m, "Card %d: %s", m->sv_card + 1, msg[0] ? msg : "unavailable");
}

static void imp_load(rg_menu *m)
{
    m->imp_n = 0;
    m->imp_confirm[0] = 0;
    if (!m->imp_path[0]) return;
    char msg[256] = "";
    m->imp_n = m->saves->src_list(m->saves->user, m->imp_path, m->sv_card, m->imp, RG_MENU_MAX_SAVES, msg, sizeof msg);
    if (m->imp_n > RG_MENU_MAX_SAVES) m->imp_n = RG_MENU_MAX_SAVES;
    if (m->imp_n < 0) rg_menu__status(m, "%s: %s", m->imp_path, msg[0] ? msg : "not a memory card");
}

static void br_load(rg_menu *m, const char *dir)
{
    char msg[256] = "", resolved[RG_MENU_PATH_MAX] = "";
    int n = m->saves->browse(m->saves->user, dir, m->br, RG_MENU_MAX_FILES, resolved, sizeof resolved, msg, sizeof msg);
    if (n < 0) {
        rg_menu__status(m, "%s: %s", dir[0] ? dir : "(start folder)", msg[0] ? msg : "cannot be read");
        if (m->br_n > 0) return;   /* stay in the folder shown */
        n = 0;
    } else {
        m->status[0] = 0;
    }
    m->br_n = n > RG_MENU_MAX_FILES ? RG_MENU_MAX_FILES : n;
    snprintf(m->br_dir, sizeof m->br_dir, "%s", resolved);
    m->sub = 0;
}

void rg_menu__saves_open(rg_menu *m, int view)
{
    if (!m->saves) return;
    m->view = view;
    m->sub = 0;
    m->status[0] = 0;
    m->imp_confirm[0] = 0;
    if (view == RG_MENU_VIEW_SAVES) sv_load(m);
    else if (view == RG_MENU_VIEW_IMPORT) imp_load(m);
    else if (view == RG_MENU_VIEW_BROWSE) br_load(m, m->br_dir);
}

/* ---- row layouts ---- */
/* SAVES: 0 card, 1..n saves, n + 1 Back */
static int sv_rows(const rg_menu *m) { return (m->sv_n > 0 ? m->sv_n : 0) + 2; }
/* IMPORT: 0 path, 1 browse, 2 target card, 3.. saves, [import all], Back */
enum { IMP_PATH, IMP_BROWSE, IMP_CARD, IMP_FIRST };
static int imp_count(const rg_menu *m) { return m->imp_n > 0 ? m->imp_n : 0; }
static int imp_new_games(const rg_menu *m)
{
    int k = 0;
    for (int i = 0; i < imp_count(m); i++) k += m->imp[i].game && !m->imp[i].exists;
    return k;
}
static int imp_has_all(const rg_menu *m) { return imp_count(m) > 0; }
static int imp_all_row(const rg_menu *m) { return IMP_FIRST + imp_count(m); }
static int imp_rows(const rg_menu *m) { return IMP_FIRST + imp_count(m) + imp_has_all(m) + 1; }

static void do_import(rg_menu *m, int i, int force)
{
    char msg[256] = "";
    char dir[32];
    snprintf(dir, sizeof dir, "%s", m->imp[i].dir);
    int r = m->saves->src_import(m->saves->user, m->imp_path, m->sv_card, dir, force, msg, sizeof msg);
    if (r == 1) {
        snprintf(m->imp_confirm, sizeof m->imp_confirm, "%s", dir);
        rg_menu__status(m, "%s", msg[0] ? msg : "Card already has it");
        return;
    }
    int keep = m->sub;
    imp_load(m);   /* refresh the "card has it" marks */
    rg_menu__status(m, "%s", msg[0] ? msg : r == 0 ? "Imported" : "Import failed");
    m->sub = keep < imp_rows(m) ? keep : imp_rows(m) - 1;
}

static void import_all(rg_menu *m)
{
    int done = 0, kept = 0, failed = 0;
    char last[256] = "";
    for (int i = 0; i < imp_count(m); i++) {
        if (!m->imp[i].game) continue;
        if (m->imp[i].exists) { kept++; continue; }
        char msg[256] = "";
        int r = m->saves->src_import(m->saves->user, m->imp_path, m->sv_card, m->imp[i].dir, 0, msg, sizeof msg);
        if (r == 0) done++;
        else if (r == 1) kept++;
        else { failed++; snprintf(last, sizeof last, "%s", msg); }
    }
    int keep = m->sub;
    imp_load(m);
    if (!done && !failed && !kept) rg_menu__status(m, "No Rogue Galaxy save on this card file");
    else
        rg_menu__status(m, "Imported %d save%s into card %d; %d already there (kept)%s%s", done, done == 1 ? "" : "s",
                        m->sv_card + 1, kept, failed ? "; FAILED: " : "", failed ? last : "");
    m->sub = keep < imp_rows(m) ? keep : imp_rows(m) - 1;
}

static void wrap_cursor(rg_menu *m, rg_menu_cmd cmd, int rows)
{
    if (rows <= 0) { m->sub = 0; return; }
    if (cmd == RG_MENU_UP) m->sub = (m->sub + rows - 1) % rows;
    else if (cmd == RG_MENU_DOWN) m->sub = (m->sub + 1) % rows;
    if (m->sub >= rows) m->sub = rows - 1;
}

static void saves_cmd(rg_menu *m, rg_menu_cmd cmd)
{
    int rows = sv_rows(m);
    switch (cmd) {
    case RG_MENU_UP: case RG_MENU_DOWN: wrap_cursor(m, cmd, rows); break;
    case RG_MENU_LEFT: case RG_MENU_RIGHT:
    case RG_MENU_PAGE_PREV: case RG_MENU_PAGE_NEXT:
        /* the card (from any row: the list follows) */
        m->sv_card ^= 1;
        m->status[0] = 0;
        sv_load(m);
        if (m->sub >= sv_rows(m)) m->sub = sv_rows(m) - 1;
        break;
    case RG_MENU_ACCEPT:
        if (m->sub == 0) { m->sv_card ^= 1; m->status[0] = 0; sv_load(m); }
        else if (m->sub == rows - 1) { m->view = RG_MENU_VIEW_PAGE; m->status[0] = 0; }
        else {
            const rg_menu_save *sv = &m->sv[m->sub - 1];
            snprintf(m->sv_dir, sizeof m->sv_dir, "%s", sv->dir);
            rg_menu__open_text(m, RG_MENU_TEXT_SAVE_NAME, sv->name);
        }
        break;
    case RG_MENU_BACK: m->view = RG_MENU_VIEW_PAGE; m->status[0] = 0; break;
    default: break;
    }
}

static void import_cmd(rg_menu *m, rg_menu_cmd cmd)
{
    int rows = imp_rows(m);
    if (m->imp_confirm[0]) {   /* "replace?" waits for accept / back */
        int i = -1;
        for (int k = 0; k < imp_count(m); k++)
            if (!strcmp(m->imp[k].dir, m->imp_confirm)) i = k;
        if (cmd == RG_MENU_ACCEPT && i >= 0) { m->imp_confirm[0] = 0; do_import(m, i, 1); }
        else if (cmd == RG_MENU_BACK || cmd == RG_MENU_ACCEPT) {
            rg_menu__status(m, "%s kept on card %d (nothing imported)", m->imp_confirm, m->sv_card + 1);
            m->imp_confirm[0] = 0;
        }
        return;
    }
    switch (cmd) {
    case RG_MENU_UP: case RG_MENU_DOWN: wrap_cursor(m, cmd, rows); break;
    case RG_MENU_LEFT: case RG_MENU_RIGHT:
        if (m->sub == IMP_CARD) { m->sv_card ^= 1; m->status[0] = 0; imp_load(m); }
        break;
    case RG_MENU_ACCEPT:
        if (m->sub == IMP_PATH) rg_menu__open_text(m, RG_MENU_TEXT_IMPORT_PATH, m->imp_path);
        else if (m->sub == IMP_BROWSE) rg_menu__saves_open(m, RG_MENU_VIEW_BROWSE);
        else if (m->sub == IMP_CARD) { m->sv_card ^= 1; m->status[0] = 0; imp_load(m); }
        else if (m->sub == rows - 1) { m->view = RG_MENU_VIEW_PAGE; m->status[0] = 0; }
        else if (imp_has_all(m) && m->sub == imp_all_row(m)) import_all(m);
        else if (m->sub >= IMP_FIRST && m->sub < IMP_FIRST + imp_count(m)) do_import(m, m->sub - IMP_FIRST, 0);
        break;
    case RG_MENU_BACK: m->view = RG_MENU_VIEW_PAGE; m->status[0] = 0; break;
    default: break;
    }
}

static void browse_cmd(rg_menu *m, rg_menu_cmd cmd)
{
    int rows = m->br_n;
    switch (cmd) {
    case RG_MENU_UP: case RG_MENU_DOWN: wrap_cursor(m, cmd, rows); break;
    case RG_MENU_PAGE_PREV: m->sub = m->sub >= 10 ? m->sub - 10 : 0; break;
    case RG_MENU_PAGE_NEXT: if (rows) m->sub = m->sub + 10 < rows ? m->sub + 10 : rows - 1; break;
    case RG_MENU_ACCEPT: {
        if (m->sub < 0 || m->sub >= rows) break;
        const rg_menu_file *f = &m->br[m->sub];
        char path[RG_MENU_PATH_MAX];
        m->saves->join(m->saves->user, m->br_dir, f->name, f->kind, path, sizeof path);
        if (f->kind == RG_FILE_CARD || f->kind == RG_FILE_FOLDER_CARD) {
            snprintf(m->imp_path, sizeof m->imp_path, "%s", path);
            m->view = RG_MENU_VIEW_IMPORT;
            m->status[0] = 0;
            imp_load(m);
            m->sub = imp_count(m) > 0 ? IMP_FIRST : IMP_PATH;
            if (m->imp_n >= 0) rg_menu__status(m, "%d save%s on %s (read only)", m->imp_n, m->imp_n == 1 ? "" : "s", f->name);
        } else {
            br_load(m, path);
        }
        break;
    }
    case RG_MENU_BACK:
        m->view = RG_MENU_VIEW_IMPORT;
        m->sub = IMP_BROWSE;
        m->status[0] = 0;
        break;
    default: break;
    }
}

void rg_menu__saves_command(rg_menu *m, rg_menu_cmd cmd)
{
    if (!m->saves) { m->view = RG_MENU_VIEW_PAGE; return; }
    if (m->view == RG_MENU_VIEW_SAVES) saves_cmd(m, cmd);
    else if (m->view == RG_MENU_VIEW_IMPORT) import_cmd(m, cmd);
    else browse_cmd(m, cmd);
}

static void trim_path(char *s)
{
    size_t L = strlen(s);
    while (L && (s[L - 1] == ' ' || s[L - 1] == '\t')) s[--L] = 0;
    size_t a = 0;
    while (s[a] == ' ' || s[a] == '\t') a++;
    if (s[a] == '"' && L > a + 1 && s[L - 1] == '"') { s[--L] = 0; a++; }   /* a pasted "C:\...\Mcd001.ps2" */
    memmove(s, s + a, L - a + 1);
}

void rg_menu__saves_text_done(rg_menu *m, int commit)
{
    if (m->text_target == RG_MENU_TEXT_SAVE_NAME) {
        if (commit) {
            if (strlen(m->text) > 63) { rg_menu__status(m, "Name too long: 63 bytes at most"); return; }
            char msg[256] = "";
            if (m->saves->rename(m->saves->user, m->sv_card, m->sv_dir, m->text, msg, sizeof msg) != 0) {
                rg_menu__status(m, "%s: %s", m->sv_dir, msg[0] ? msg : "could not be named");
                return;   /* the editor stays open */
            }
            int keep = m->sub;
            sv_load(m);
            m->sub = keep < sv_rows(m) ? keep : sv_rows(m) - 1;
            if (m->text[0]) rg_menu__status(m, "%s named \"%s\"", m->sv_dir, m->text);
            else rg_menu__status(m, "%s: name removed", m->sv_dir);
        } else {
            rg_menu__status(m, "%s: name unchanged", m->sv_dir);
        }
        m->view = RG_MENU_VIEW_SAVES;
    } else {
        m->view = RG_MENU_VIEW_IMPORT;
        if (commit) {
            char p[RG_MENU_PATH_MAX];
            snprintf(p, sizeof p, "%s", m->text);
            trim_path(p);
            snprintf(m->imp_path, sizeof m->imp_path, "%s", p);
            m->status[0] = 0;
            imp_load(m);
            if (m->imp_n >= 0 && m->imp_path[0])
                rg_menu__status(m, "%d save%s on the card file (read only)", m->imp_n, m->imp_n == 1 ? "" : "s");
            m->sub = imp_count(m) > 0 ? IMP_FIRST : IMP_PATH;
        } else {
            m->status[0] = 0;
            m->sub = IMP_PATH;
        }
    }
    m->text_target = RG_MENU_TEXT_SETTING;
}

void rg_menu__saves_text_title(const rg_menu *m, char *out, size_t cap)
{
    if (m->text_target == RG_MENU_TEXT_SAVE_NAME)
        snprintf(out, cap, "Name for %s on card %d (empty = no name, 63 bytes at most)", m->sv_dir, m->sv_card + 1);
    else
        snprintf(out, cap, "PCSX2 memory card file or folder (e.g. ...\\PCSX2\\memcards\\Mcd001.ps2)");
}

/* ---- render ---- */
static void save_line(const rg_menu_save *s, int sel, int import, int card, char *out, size_t cap)
{
    size_t L = (size_t)snprintf(out, cap, "%s %s", sel ? ">" : " ", s->dir);
    if (s->name[0] && L < cap) L += (size_t)snprintf(out + L, cap - L, "  \"%s\"", s->name);
    if (s->when[0] && L < cap) L += (size_t)snprintf(out + L, cap - L, "  %s", s->when);
    if (L < cap) L += (size_t)snprintf(out + L, cap - L, "  %s", s->meta[0] ? s->meta : s->title[0] ? s->title : "(no summary)");
    if (import && s->exists && L < cap) snprintf(out + L, cap - L, "  [card %d has one: asks before replacing]", card + 1);
}

int rg_menu__saves_render(const rg_menu *m, rg_menu_line *l, int cap)
{
    int k = 0;
    char b[512];
    if (m->view == RG_MENU_VIEW_SAVES) {
        rg_menu__line(l, &k, cap, false, true, "SETTINGS  Saves > Manage saves", 4);
        rg_menu__hint(m, l, &k, cap, "[up] / [down] select   [left] / [right] card   [accept] renames the save   [back] returns");
        int rows = sv_rows(m);
        snprintf(b, sizeof b, "%s Card:  %s  %s", m->sub == 0 ? ">" : " ", m->sv_card == 0 ? "[1]" : " 1 ",
                 m->sv_card == 1 ? "[2]" : " 2 ");
        if (m->sv_n >= 0) {
            size_t L = strlen(b);
            snprintf(b + L, sizeof b - L, "   %d save director%s", m->sv_n, m->sv_n == 1 ? "y" : "ies");
        }
        rg_menu__line(l, &k, cap, m->sub == 0, false, b, 4);
        if (m->sv_n == 0) rg_menu__line(l, &k, cap, false, false, "  (no saves on this card)", 4);
        for (int i = 0; i < m->sv_n; i++) {
            save_line(&m->sv[i], m->sub == i + 1, 0, m->sv_card, b, sizeof b);
            rg_menu__line(l, &k, cap, m->sub == i + 1, false, b, 4);
        }
        rg_menu__line(l, &k, cap, m->sub == rows - 1, false, m->sub == rows - 1 ? "> Back" : "  Back", 4);
        rg_menu__line(l, &k, cap, false, true,
                      "  A name is the overlay's label for one of the game's save slots (kept in saves/card<N>.names, "
                      "shown in card<N>.txt); the game's own save screen is unchanged.", 4);
    } else if (m->view == RG_MENU_VIEW_IMPORT) {
        int rows = imp_rows(m);
        rg_menu__line(l, &k, cap, false, true, "SETTINGS  Saves > Import from a PCSX2 memory card", 4);
        rg_menu__hint(m, l, &k, cap, "[up] / [down] select   [accept] edits / picks / imports   [left] / [right] target card   [back] returns");
        snprintf(b, sizeof b, "%s Card file:  %s", m->sub == IMP_PATH ? ">" : " ",
                 m->imp_path[0] ? m->imp_path : "(none: type a path here, or browse)");
        rg_menu__line(l, &k, cap, m->sub == IMP_PATH, false, b, 4);
        rg_menu__line(l, &k, cap, m->sub == IMP_BROWSE, false,
                      m->sub == IMP_BROWSE ? "> Browse for the card file ..." : "  Browse for the card file ...", 4);
        snprintf(b, sizeof b, "%s Import into:  card %s  %s", m->sub == IMP_CARD ? ">" : " ", m->sv_card == 0 ? "[1]" : " 1 ",
                 m->sv_card == 1 ? "[2]" : " 2 ");
        rg_menu__line(l, &k, cap, m->sub == IMP_CARD, false, b, 4);
        if (m->imp_path[0] && m->imp_n == 0) rg_menu__line(l, &k, cap, false, false, "  (no saves on this card file)", 4);
        for (int i = 0; i < imp_count(m); i++) {
            save_line(&m->imp[i], m->sub == IMP_FIRST + i, 1, m->sv_card, b, sizeof b);
            rg_menu__line(l, &k, cap, m->sub == IMP_FIRST + i, false, b, 4);
        }
        if (imp_has_all(m)) {
            int all = imp_all_row(m);
            snprintf(b, sizeof b, "%s Import every Rogue Galaxy save card %d does not have (%d)", m->sub == all ? ">" : " ",
                     m->sv_card + 1, imp_new_games(m));
            rg_menu__line(l, &k, cap, m->sub == all, false, b, 4);
        }
        rg_menu__line(l, &k, cap, m->sub == rows - 1, false, m->sub == rows - 1 ? "> Back" : "  Back", 4);
        rg_menu__line(l, &k, cap, false, true,
                      "  The card file is only read.  Each save is written through the card's crash-safe writes; "
                      "a save that is replaced is backed up first (saves/backups).", 4);
        if (m->imp_confirm[0]) {
            char t[400];
            snprintf(t, sizeof t, "Card %d already has %s.  Replace it?  [accept] = replace (the current one is backed up "
                                  "first), [back] = keep it", m->sv_card + 1, m->imp_confirm);
            rg_menu__hint(m, l, &k, cap, t);
        }
    } else {
        rg_menu__line(l, &k, cap, false, true, "SETTINGS  Saves > Import > Browse for the card file", 4);
        rg_menu__hint(m, l, &k, cap, "[up] / [down] select   [prev] / [next] 10 rows   [accept] opens a folder or picks a card   [back] returns");
        snprintf(b, sizeof b, "  Folder: %s", m->br_dir[0] ? m->br_dir : "(drives)");
        rg_menu__line(l, &k, cap, false, true, b, 4);
        if (!m->br_n) rg_menu__line(l, &k, cap, false, false, "  (nothing here)", 4);
        for (int i = 0; i < m->br_n; i++) {
            const rg_menu_file *f = &m->br[i];
            static const char *const tag[] = { "", "[folder]", "[card]", "[PCSX2 folder card]", "[drive]" };
            if (f->kind == RG_FILE_UP) snprintf(b, sizeof b, "%s .. (up)", m->sub == i ? ">" : " ");
            else snprintf(b, sizeof b, "%s %-20s %s", m->sub == i ? ">" : " ", tag[f->kind < 5 ? f->kind : 1], f->name);
            rg_menu__line(l, &k, cap, m->sub == i, false, b, 4);
        }
    }
    if (m->status[0]) rg_menu__line(l, &k, cap, false, true, m->status, 4);
    return k;
}
