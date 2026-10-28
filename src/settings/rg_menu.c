/* SPDX-License-Identifier: CC0-1.0 */
/* Settings menu model.  docs/SETTINGS.md "Menu API"; rebinding: docs/INPUT.md
 * "Rebinding from the menu". */
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "rg_menu.h"

static const char *const k_page_titles[][2] = {
    { "display", "Display" }, { "graphics", "Graphics" }, { "audio", "Audio" },
    { "controls", "Controls" }, { "controls_ui", "Menu controls" }, { "gameplay", "Gameplay" },
    { "system", "System" }, { "presets", "Presets & save" },
};

/* Bindings of these categories can't drop to zero (the menu must stay
 * reachable). */
static const char k_ui_category[] = "controls_ui";

static const char *page_title(const char *p)
{
    for (size_t i = 0; i < sizeof k_page_titles / sizeof k_page_titles[0]; i++)
        if (!strcmp(k_page_titles[i][0], p)) return k_page_titles[i][1];
    return p;
}

static const char *label_of(const rg_menu *m, int idx)
{
    const rg_setting_def *d = rg_settings_def(m->s, idx);
    return d->label ? d->label : d->id;
}

void rg_menu_refresh(rg_menu *m)
{
    const char *cats[RG_MENU_MAX_PAGES];
    int n = rg_settings_categories(m->s, cats, RG_MENU_MAX_PAGES - 1);
    if (n > RG_MENU_MAX_PAGES - 1) n = RG_MENU_MAX_PAGES - 1;
    m->npages = 0;
    for (int i = 0; i < n; i++) {
        /* skip a category with nothing visible */
        int vis = 0;
        for (int k = 0; k < rg_settings_count(m->s) && !vis; k++) {
            const rg_setting_def *d = rg_settings_def(m->s, k);
            if (!strcmp(d->category, cats[i]) && !(d->flags & RG_SETF_HIDDEN)) vis = 1;
        }
        if (vis) m->pages[m->npages++] = cats[i];
    }
    m->pages[m->npages++] = "presets";
    if (m->page >= m->npages) m->page = 0;
}

void rg_menu_set_choices(rg_menu *m, rg_menu_choices_fn fn, void *user)
{
    m->choices = fn;
    m->choices_user = user;
}

void rg_menu_init(rg_menu *m, rg_settings *s)
{
    memset(m, 0, sizeof *m);
    m->s = s;
    m->trial_ms = 15000;
    m->capture_ms = 5000;
    snprintf(m->capture_hint, sizeof m->capture_hint, "Esc / Guide");
    rg_menu_refresh(m);
}

static int is_presets(const rg_menu *m) { return !strcmp(m->pages[m->page], "presets"); }

int rg_menu_rows(const rg_menu *m, int *rows, int cap)
{
    int k = 0;
    if (is_presets(m)) {
        int np = rg_settings_preset_count(m->s);
        for (int i = 0; i < np && k < cap; i++) rows[k++] = -1 - (RG_ROW_PRESET + RG_ROW_STRIDE * i);
        if (m->save_path && k < cap) rows[k++] = -1 - RG_ROW_SAVE;
        return k;
    }
    const char *cat = m->pages[m->page];
    int bindings = 0;
    for (int i = 0; i < rg_settings_count(m->s) && k < cap; i++) {
        const rg_setting_def *d = rg_settings_def(m->s, i);
        if (!strcmp(d->category, cat) && !(d->flags & RG_SETF_HIDDEN)) {
            rows[k++] = i;
            if (d->type == RG_SET_BINDING) bindings = 1;
        }
    }
    if (bindings && k < cap) rows[k++] = -1 - RG_ROW_RESET_BINDINGS;
    if (k < cap) rows[k++] = -1 - RG_ROW_RESET_PAGE;
    return k;
}

static int cur_row(const rg_menu *m, int *nrows)
{
    int rows[RG_MENU_MAX_ROWS];
    int n = rg_menu_rows(m, rows, RG_MENU_MAX_ROWS);
    if (nrows) *nrows = n;
    if (!n) return -1 - RG_ROW_RESET_PAGE;
    int c = m->cursor < n ? m->cursor : n - 1;
    return rows[c];
}

#if defined(__GNUC__) || defined(__clang__)
__attribute__((format(printf, 2, 3)))
#endif
static void status(rg_menu *m, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(m->status, sizeof m->status, fmt, ap);
    va_end(ap);
}

/* ------------------------------------------------------------ binding tokens */
#define TOK_MAX 16
#define TOK_LEN 96

static int split_tokens(const char *v, char t[TOK_MAX][TOK_LEN])
{
    int n = 0;
    const char *p = v ? v : "";
    while (*p && n < TOK_MAX) {
        const char *e = strchr(p, ',');
        size_t L = e ? (size_t)(e - p) : strlen(p);
        while (L && isspace((unsigned char)*p)) { p++; L--; }
        while (L && isspace((unsigned char)p[L - 1])) L--;
        if (L) {
            if (L >= TOK_LEN) L = TOK_LEN - 1;
            memcpy(t[n], p, L);
            t[n][L] = 0;
            n++;
        }
        if (!e) break;
        p = e + 1;
    }
    return n;
}

static int tok_eq(const char *a, const char *b)
{
    for (; *a && *b; a++, b++)
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
    return *a == *b;
}

static int edit_tokens(const rg_menu *m, char t[TOK_MAX][TOK_LEN])
{
    return split_tokens(rg_settings_get_string(m->s, rg_settings_def(m->s, m->edit)->id), t);
}

int rg_menu_binding_conflicts(const rg_menu *m, int index, const char *token, int *out, int cap)
{
    int k = 0;
    const char *cat = rg_settings_category(m->s, index);
    for (int i = 0; i < rg_settings_count(m->s); i++) {
        if (i == index) continue;
        const rg_setting_def *d = rg_settings_def(m->s, i);
        if (d->type != RG_SET_BINDING || strcmp(rg_settings_category(m->s, i), cat)) continue;
        char t[TOK_MAX][TOK_LEN];
        int n = split_tokens(rg_settings_get_string(m->s, d->id), t);
        for (int j = 0; j < n; j++)
            if (tok_eq(t[j], token)) {
                if (k < cap && out) out[k] = i;
                k++;
                break;
            }
    }
    return k;
}

/* Stores the list; RG_SET_* (status set on failure). */
static int store_tokens(rg_menu *m, char t[TOK_MAX][TOK_LEN], int n)
{
    char buf[TOK_MAX * (TOK_LEN + 2)];
    buf[0] = 0;
    for (int i = 0; i < n; i++) {
        if (i) strcat(buf, ", ");
        strcat(buf, t[i]);
    }
    char err[128] = "";
    int rc = rg_settings_set_text(m->s, m->edit, buf, RG_SRC_MENU, err, sizeof err);
    if (rc == RG_SET_OK) m->dirty = true;
    else if (rc < 0) status(m, "%s: %s", label_of(m, m->edit), err[0] ? err : "refused");
    return rc;
}

static void conflict_note(const rg_menu *m, int idx, const char *tok, char *out, size_t cap)
{
    int c[8];
    int k = rg_menu_binding_conflicts(m, idx, tok, c, 8);
    out[0] = 0;
    if (!k) return;
    if (k == 1) snprintf(out, cap, "%s", label_of(m, c[0]));
    else snprintf(out, cap, "%s (+%d more)", label_of(m, c[0]), k - 1);
}

/* ---- device guard (menu controls) ---- */
enum { DEV_OTHER, DEV_KEYBOARD, DEV_GAMEPAD };

static int has_prefix(const char *s, const char *p)
{
    for (; *p; s++, p++)
        if (tolower((unsigned char)*s) != *p) return 0;
    return 1;
}

static int tok_dev(const char *t)
{
    if (has_prefix(t, "key:")) return DEV_KEYBOARD;
    if (has_prefix(t, "pad:") || has_prefix(t, "axis:")) return DEV_GAMEPAD;
    return DEV_OTHER;
}

static int count_dev(char t[TOK_MAX][TOK_LEN], int n, int dev)
{
    int k = 0;
    for (int i = 0; i < n; i++) k += tok_dev(t[i]) == dev;
    return k;
}

/* the menu actions (input.bind.ui_*); not the overlay chord, which takes gamepad buttons only */
static int guarded(const rg_menu *m)
{
    return !strcmp(rg_settings_category(m->s, m->edit), k_ui_category) &&
           !strncmp(rg_settings_def(m->s, m->edit)->id, "input.bind.", 11);
}

static const char *dev_name(int dev) { return dev == DEV_KEYBOARD ? "keyboard" : "gamepad"; }

/* The device whose last binding the change o -> t would take away from a menu
 * control, or DEV_OTHER when the change is allowed. */
static int guard_loses(const rg_menu *m, char o[TOK_MAX][TOK_LEN], int no, char t[TOK_MAX][TOK_LEN], int nt)
{
    if (!guarded(m)) return DEV_OTHER;
    for (int dev = DEV_KEYBOARD; dev <= DEV_GAMEPAD; dev++)
        if (count_dev(o, no, dev) > 0 && count_dev(t, nt, dev) == 0) return dev;
    return DEV_OTHER;
}

/* Editor rows: n bindings, then Add, Capture mouse motion, Reset, Back. */
enum { ED_ADD, ED_MOTION, ED_RESET, ED_BACK, ED_EXTRA };

static void begin_capture(rg_menu *m, int slot, bool motion, uint64_t now)
{
    m->capturing = true;
    m->capture_motion = motion;
    m->capture_slot = slot;
    m->capture_deadline = now + m->capture_ms;
    m->status[0] = 0;
    m->offer[0] = 0;
    m->confirm[0] = 0;
}

bool rg_menu_capturing(const rg_menu *m) { return m->open && m->capturing; }
bool rg_menu_capturing_motion(const rg_menu *m) { return rg_menu_capturing(m) && m->capture_motion; }

/* Puts binding `b` into `slot` (replace) or appends it (slot < 0). */
static void apply_binding(rg_menu *m, int slot, const char *b)
{
    const char *lab = label_of(m, m->edit);
    char t[TOK_MAX][TOK_LEN], o[TOK_MAX][TOK_LEN];
    int n = edit_tokens(m, t);
    int no = edit_tokens(m, o);
    for (int i = 0; i < n; i++)
        if (tok_eq(t[i], b)) {
            if (i == slot) status(m, "%s: %s unchanged", lab, b);
            else status(m, "%s already has %s", lab, b);
            m->sub = i;
            return;
        }
    int pos;
    if (slot >= 0 && slot < n) pos = slot;
    else if (n < TOK_MAX) pos = n++;
    else { status(m, "%s: too many bindings", lab); return; }
    char old[TOK_LEN];
    snprintf(old, sizeof old, "%s", pos < n && slot >= 0 ? t[pos] : "");
    snprintf(t[pos], TOK_LEN, "%s", b);
    int lost = guard_loses(m, o, no, t, n);
    if (lost != DEV_OTHER) {
        status(m, "%s: not replaced: %s is its last %s binding, and the menu must work from the "
                  "keyboard alone and from a gamepad alone. Accept on \"Add %s instead\" keeps both.",
               lab, old, dev_name(lost), b);
        snprintf(m->offer, sizeof m->offer, "%s", b);
        m->sub = no + ED_ADD;
        m->sub_col = 0;
        return;
    }
    if (store_tokens(m, t, n) < 0) return;
    /* the stored (canonical) list: find the new token's row */
    n = edit_tokens(m, t);
    for (int i = 0; i < n; i++) if (tok_eq(t[i], b)) m->sub = i;
    m->sub_col = 0;
    char note[96];
    conflict_note(m, m->edit, b, note, sizeof note);
    if (old[0]) status(m, "%s: %s replaced by %s", lab, old, b);
    else status(m, "%s: added %s", lab, b);
    if (note[0]) {
        size_t L = strlen(m->status);
        snprintf(m->status + L, sizeof m->status - L, "  WARNING: %s has it too (both fire)", note);
    }
}

void rg_menu_capture_input(rg_menu *m, const char *b, uint64_t now)
{
    (void)now;
    if (!m->capturing) return;
    m->capturing = false;
    bool motion = m->capture_motion;
    m->capture_motion = false;
    const char *lab = label_of(m, m->edit);
    if (!b || !*b) { status(m, "%s: cancelled, bindings unchanged", lab); return; }
    if (motion) {
        /* the confirm step: nothing is stored until ACCEPT */
        char t[TOK_MAX][TOK_LEN];
        int n = edit_tokens(m, t);
        for (int i = 0; i < n; i++)
            if (tok_eq(t[i], b)) { status(m, "%s already has %s", lab, b); m->sub = i; return; }
        snprintf(m->confirm, sizeof m->confirm, "%s", b);
        m->status[0] = 0;
        return;
    }
    apply_binding(m, m->capture_slot, b);
}

static void remove_binding(rg_menu *m, int slot)
{
    char t[TOK_MAX][TOK_LEN];
    int n = edit_tokens(m, t);
    if (slot < 0 || slot >= n) return;
    const char *lab = label_of(m, m->edit);
    char o[TOK_MAX][TOK_LEN];
    int no = edit_tokens(m, o);
    char gone[TOK_LEN];
    snprintf(gone, sizeof gone, "%s", t[slot]);
    memmove(&t[slot], &t[slot + 1], (size_t)(n - slot - 1) * sizeof t[0]);
    n--;
    int lost = guard_loses(m, o, no, t, n);
    if (lost != DEV_OTHER) {
        status(m, "%s: not removed: %s is its last %s binding, and the menu must work from the "
                  "keyboard alone and from a gamepad alone. Add another %s binding first (selected).",
               lab, gone, dev_name(lost), dev_name(lost));
        m->sub = no + ED_ADD;
        m->sub_col = 0;
        return;
    }
    if (n == 0 && guarded(m)) {   /* e.g. a mouse button only: still never unbound */
        status(m, "%s: not removed: menu controls keep at least one binding. Add another first (selected).", lab);
        m->sub = no + ED_ADD;
        m->sub_col = 0;
        return;
    }
    if (store_tokens(m, t, n) < 0) return;
    status(m, n ? "%s: removed %s" : "%s: removed %s (now unbound)", lab, gone);
    if (m->sub > n) m->sub = n;   /* stays on the row that moved up, or "Add" */
}

static void bindings_command(rg_menu *m, rg_menu_cmd cmd, uint64_t now)
{
    char t[TOK_MAX][TOK_LEN];
    int n = edit_tokens(m, t);
    int rows = n + ED_EXTRA;
    if (m->sub >= rows) m->sub = rows - 1;
    if (m->confirm[0]) {   /* a captured motion waits for accept / back */
        char b[96];
        snprintf(b, sizeof b, "%s", m->confirm);
        if (cmd == RG_MENU_ACCEPT) { m->confirm[0] = 0; apply_binding(m, -1, b); }
        else if (cmd == RG_MENU_BACK) {
            m->confirm[0] = 0;
            status(m, "%s: %s discarded, bindings unchanged", label_of(m, m->edit), b);
        }
        return;
    }
    if (cmd == RG_MENU_ACCEPT || cmd == RG_MENU_BACK) {
        /* an offer is taken by accepting it; any other accept or back drops it */
        if (cmd == RG_MENU_ACCEPT && m->offer[0] && m->sub == n + ED_ADD) {
            char b[96];
            snprintf(b, sizeof b, "%s", m->offer);
            m->offer[0] = 0;
            apply_binding(m, -1, b);
            return;
        }
        m->offer[0] = 0;
    }
    switch (cmd) {
    case RG_MENU_UP: m->sub = (m->sub + rows - 1) % rows; m->sub_col = 0; break;
    case RG_MENU_DOWN: m->sub = (m->sub + 1) % rows; m->sub_col = 0; break;
    case RG_MENU_LEFT:
    case RG_MENU_RIGHT:
        if (m->sub < n) m->sub_col ^= 1;
        break;
    case RG_MENU_ACCEPT:
        if (m->sub < n) {
            if (m->sub_col == 0) begin_capture(m, m->sub, false, now);
            else remove_binding(m, m->sub);
        } else if (m->sub == n + ED_ADD) {
            begin_capture(m, -1, false, now);
        } else if (m->sub == n + ED_MOTION) {
            begin_capture(m, -1, true, now);
        } else if (m->sub == n + ED_RESET) {
            rg_settings_reset(m->s, m->edit);
            m->dirty = true;
            status(m, "%s: default bindings restored", label_of(m, m->edit));
        } else {
            m->view = RG_MENU_VIEW_PAGE;
        }
        break;
    case RG_MENU_BACK: m->view = RG_MENU_VIEW_PAGE; break;
    default: break;
    }
}

/* ------------------------------------------------------------ text entry */
static const char *const k_osk[] = {
    "abcdefghijklm", "nopqrstuvwxyz", "ABCDEFGHIJKLM", "NOPQRSTUVWXYZ",
    "0123456789.-_", "/\\:~()!,'+=@&",
};
static const char *const k_osk_special[] = { "Space", "Delete", "Clear", "OK", "Cancel" };
enum { OSK_CHAR_ROWS = 6, OSK_ROWS = 7, OSK_SPECIAL = 5 };
enum { OSK_SPACE, OSK_DELETE, OSK_CLEAR, OSK_OK, OSK_CANCEL };

static int osk_len(int row) { return row < OSK_CHAR_ROWS ? (int)strlen(k_osk[row]) : OSK_SPECIAL; }

bool rg_menu_text_editing(const rg_menu *m) { return m->open && m->view == RG_MENU_VIEW_TEXT; }

static void text_insert(rg_menu *m, const char *str, size_t L)
{
    size_t have = strlen(m->text);
    if (have + L >= sizeof m->text) { status(m, "Text too long"); return; }
    memmove(m->text + m->text_cur + L, m->text + m->text_cur, have - (size_t)m->text_cur + 1);
    memcpy(m->text + m->text_cur, str, L);
    m->text_cur += (int)L;
}

static int utf8_prev(const char *s, int i)
{
    if (i <= 0) return 0;
    i--;
    while (i > 0 && ((unsigned char)s[i] & 0xC0) == 0x80) i--;
    return i;
}

static int utf8_next(const char *s, int i)
{
    if (!s[i]) return i;
    i++;
    while (s[i] && ((unsigned char)s[i] & 0xC0) == 0x80) i++;
    return i;
}

void rg_menu_text_input(rg_menu *m, const char *utf8)
{
    if (!rg_menu_text_editing(m) || !utf8) return;
    for (const char *p = utf8; *p; ) {
        int n = utf8_next(p, 0);
        if ((unsigned char)*p >= 0x20 && *p != 0x7F) text_insert(m, p, (size_t)n);
        p += n;
    }
}

static void text_close(rg_menu *m) { m->view = RG_MENU_VIEW_PAGE; }

void rg_menu_text_key(rg_menu *m, rg_text_key k)
{
    if (!rg_menu_text_editing(m)) return;
    int L = (int)strlen(m->text);
    switch (k) {
    case RG_TEXT_BACKSPACE:
        if (m->text_cur > 0) {
            int p = utf8_prev(m->text, m->text_cur);
            memmove(m->text + p, m->text + m->text_cur, (size_t)(L - m->text_cur + 1));
            m->text_cur = p;
        }
        break;
    case RG_TEXT_DELETE:
        if (m->text_cur < L) {
            int nx = utf8_next(m->text, m->text_cur);
            memmove(m->text + m->text_cur, m->text + nx, (size_t)(L - nx + 1));
        }
        break;
    case RG_TEXT_LEFT: m->text_cur = utf8_prev(m->text, m->text_cur); break;
    case RG_TEXT_RIGHT: m->text_cur = utf8_next(m->text, m->text_cur); break;
    case RG_TEXT_HOME: m->text_cur = 0; break;
    case RG_TEXT_END: m->text_cur = L; break;
    case RG_TEXT_CANCEL:
        status(m, "%s: unchanged", label_of(m, m->edit));
        text_close(m);
        break;
    case RG_TEXT_COMMIT: {
        char err[128] = "";
        const rg_setting_def *d = rg_settings_def(m->s, m->edit);
        int rc = rg_settings_set_text(m->s, m->edit, m->text, RG_SRC_MENU, err, sizeof err);
        if (rc < 0) { status(m, "%s: %s", label_of(m, m->edit), err[0] ? err : "invalid"); break; }
        if (rc == RG_SET_OK) {
            m->dirty = true;
            int pend[4];
            if ((d->flags & RG_SETF_RESTART) && rg_settings_restart_pending(m->s, pend, 4) > 0)
                status(m, "%s set; takes effect after a restart", label_of(m, m->edit));
            else status(m, "%s set", label_of(m, m->edit));
        } else {
            status(m, "%s: unchanged", label_of(m, m->edit));
        }
        text_close(m);
        break;
    }
    }
}

static void text_command(rg_menu *m, rg_menu_cmd cmd)
{
    switch (cmd) {
    case RG_MENU_UP: m->osk_row = (m->osk_row + OSK_ROWS - 1) % OSK_ROWS; break;
    case RG_MENU_DOWN: m->osk_row = (m->osk_row + 1) % OSK_ROWS; break;
    case RG_MENU_LEFT: m->osk_col = (m->osk_col + osk_len(m->osk_row) - 1) % osk_len(m->osk_row); break;
    case RG_MENU_RIGHT: m->osk_col = (m->osk_col + 1) % osk_len(m->osk_row); break;
    case RG_MENU_BACK: rg_menu_text_key(m, RG_TEXT_BACKSPACE); break;
    case RG_MENU_PAGE_PREV: rg_menu_text_key(m, RG_TEXT_LEFT); break;
    case RG_MENU_PAGE_NEXT: rg_menu_text_key(m, RG_TEXT_RIGHT); break;
    case RG_MENU_ACCEPT:
        if (m->osk_row < OSK_CHAR_ROWS) {
            text_insert(m, &k_osk[m->osk_row][m->osk_col], 1);
        } else {
            switch (m->osk_col) {
            case OSK_SPACE: text_insert(m, " ", 1); break;
            case OSK_DELETE: rg_menu_text_key(m, RG_TEXT_BACKSPACE); break;
            case OSK_CLEAR: m->text[0] = 0; m->text_cur = 0; break;
            case OSK_OK: rg_menu_text_key(m, RG_TEXT_COMMIT); break;
            default: rg_menu_text_key(m, RG_TEXT_CANCEL); break;
            }
        }
        break;
    default: break;
    }
    if (m->osk_col >= osk_len(m->osk_row)) m->osk_col = osk_len(m->osk_row) - 1;
}

static void open_text(rg_menu *m, int idx)
{
    m->view = RG_MENU_VIEW_TEXT;
    m->edit = idx;
    const char *raw = rg_settings_get_string(m->s, rg_settings_def(m->s, idx)->id);
    snprintf(m->text, sizeof m->text, "%s", raw ? raw : "");
    m->text_cur = (int)strlen(m->text);
    m->osk_row = m->osk_col = 0;
    m->status[0] = 0;
}

/* ------------------------------------------------------------ page view */
/* A STRING setting with a choice list (rg_menu_set_choices, e.g. audio.device): LEFT /
 * RIGHT steps through the list (a value not in it steps to the first / last choice). */
static bool change_choice(rg_menu *m, int idx, int dir)
{
    const rg_setting_def *d = rg_settings_def(m->s, idx);
    const char *list[RG_MENU_MAX_CHOICES];
    int n = m->choices ? m->choices(d->id, list, RG_MENU_MAX_CHOICES, m->choices_user) : 0;
    if (n <= 0) return false;
    if (n > RG_MENU_MAX_CHOICES) n = RG_MENU_MAX_CHOICES;
    const char *cur = rg_settings_get_string(m->s, d->id);
    int at = -1;
    for (int i = 0; i < n && at < 0; i++)
        if (!strcmp(list[i], cur ? cur : "")) at = i;
    int next = at < 0 ? (dir > 0 ? 0 : n - 1) : (at + (dir > 0 ? 1 : n - 1)) % n;
    if (rg_settings_set_string(m->s, d->id, list[next], RG_SRC_MENU) == RG_SET_OK) {
        m->dirty = true;
        m->status[0] = 0;
    }
    return true;
}

static void change(rg_menu *m, int idx, int dir, uint64_t now)
{
    const rg_setting_def *d = rg_settings_def(m->s, idx);
    if (d->type == RG_SET_STRING && change_choice(m, idx, dir)) return;
    if (d->type == RG_SET_STRING || d->type == RG_SET_BINDING) {
        status(m, "%s: press accept to edit", label_of(m, idx));
        return;
    }
    if (d->flags & RG_SETF_DISPLAY) rg_settings_trial_begin(m->s, idx, now, m->trial_ms);
    if (rg_settings_step(m->s, idx, dir) == RG_SET_OK) {
        m->dirty = true;
        m->status[0] = 0;
        int pend[4];
        if ((d->flags & RG_SETF_RESTART) && rg_settings_restart_pending(m->s, pend, 4) > 0)
            status(m, "%s: takes effect after a restart", label_of(m, idx));
    }
    /* nothing changed (at a range end): an open trial stays as it was */
}

static void activate_action_row(rg_menu *m, int row)
{
    int code = -1 - row;
    if (code == RG_ROW_SAVE) {
        if (rg_settings_save(m->s, m->save_path, 0) == 0) { m->dirty = false; status(m, "Saved to %s", m->save_path); }
        else status(m, "Could not write %s", m->save_path);
    } else if (code == RG_ROW_RESET_PAGE) {
        const char *cat = m->pages[m->page];
        for (int i = 0; i < rg_settings_count(m->s); i++) {
            const rg_setting_def *d = rg_settings_def(m->s, i);
            if (!strcmp(d->category, cat) && !(d->flags & RG_SETF_HIDDEN)) rg_settings_reset(m->s, i);
        }
        m->dirty = true;
        status(m, "%s reset to defaults", page_title(cat));
    } else if (code == RG_ROW_RESET_BINDINGS) {
        for (int i = 0; i < rg_settings_count(m->s); i++)
            if (rg_settings_def(m->s, i)->type == RG_SET_BINDING) rg_settings_reset(m->s, i);
        m->dirty = true;
        status(m, "All bindings (game and menu) reset to defaults");
    } else if (code % RG_ROW_STRIDE == RG_ROW_PRESET) {
        int pi = code / RG_ROW_STRIDE;
        const char *name = rg_settings_preset_name(m->s, pi);
        if (name && rg_settings_apply_preset(m->s, name) == 0) {
            m->dirty = true;
            status(m, "Preset applied: %s", rg_settings_preset_label(m->s, pi));
        }
    }
}

/* closing the overlay persists any change once (no per-key writes); the Save
   row stays as an explicit mid-session save */
static void close_menu(rg_menu *m)
{
    m->open = false;
    if (m->dirty && m->save_path && rg_settings_save(m->s, m->save_path, 0) == 0) m->dirty = false;
}

bool rg_menu_command(rg_menu *m, rg_menu_cmd cmd, uint64_t now)
{
    if (cmd == RG_MENU_TOGGLE) {
        if (m->open && rg_settings_trial_active(m->s)) rg_settings_trial_revert(m->s);
        if (m->open) close_menu(m); else m->open = true;
        m->status[0] = 0;
        m->capturing = false;
        m->capture_motion = false;
        m->confirm[0] = m->offer[0] = 0;
        m->view = RG_MENU_VIEW_PAGE;
        if (m->open) rg_menu_refresh(m);
        return true;
    }
    if (!m->open) return false;
    if (m->capturing) return true;   /* the host routes raw input to the capture */
    if (m->view == RG_MENU_VIEW_BINDINGS) { bindings_command(m, cmd, now); return true; }
    if (m->view == RG_MENU_VIEW_TEXT) { text_command(m, cmd); return true; }
    int n = 0;
    int row = cur_row(m, &n);
    if (rg_settings_trial_active(m->s)) {
        switch (cmd) {
        case RG_MENU_ACCEPT: rg_settings_trial_confirm(m->s); status(m, "Display settings kept"); break;
        case RG_MENU_BACK: rg_settings_trial_revert(m->s); status(m, "Display settings reverted"); break;
        case RG_MENU_LEFT:
        case RG_MENU_RIGHT:
            if (row >= 0 && (rg_settings_def(m->s, row)->flags & RG_SETF_DISPLAY))
                change(m, row, cmd == RG_MENU_LEFT ? -1 : 1, now);
            break;
        default: break;
        }
        return true;
    }
    switch (cmd) {
    case RG_MENU_UP: if (n) m->cursor = (m->cursor + n - 1) % n; break;
    case RG_MENU_DOWN: if (n) m->cursor = (m->cursor + 1) % n; break;
    case RG_MENU_PAGE_PREV: m->page = (m->page + m->npages - 1) % m->npages; m->cursor = 0; break;
    case RG_MENU_PAGE_NEXT: m->page = (m->page + 1) % m->npages; m->cursor = 0; break;
    case RG_MENU_LEFT:
    case RG_MENU_RIGHT:
        if (row >= 0) change(m, row, cmd == RG_MENU_LEFT ? -1 : 1, now);
        break;
    case RG_MENU_ACCEPT:
        if (row >= 0) {
            rg_setting_type t = rg_settings_def(m->s, row)->type;
            if (t == RG_SET_BOOL || t == RG_SET_ENUM) change(m, row, 1, now);
            else if (t == RG_SET_BINDING) {
                m->view = RG_MENU_VIEW_BINDINGS;
                m->edit = row;
                m->sub = m->sub_col = 0;
                m->status[0] = 0;
                m->confirm[0] = m->offer[0] = 0;
            } else if (t == RG_SET_STRING) open_text(m, row);
        } else {
            activate_action_row(m, row);
        }
        break;
    case RG_MENU_BACK: close_menu(m); break;
    default: break;
    }
    return true;
}

int rg_menu_tick(rg_menu *m, uint64_t now)
{
    if (m->capturing && now >= m->capture_deadline) {
        m->capturing = false;
        m->capture_motion = false;
        status(m, "%s: no input for %u s, bindings unchanged", label_of(m, m->edit),
               (unsigned)((m->capture_ms + 999) / 1000));
    }
    if (rg_settings_tick(m->s, now)) { status(m, "Display settings reverted (not confirmed)"); return 1; }
    return 0;
}

/* ------------------------------------------------------------ render */
#if defined(__GNUC__) || defined(__clang__)
__attribute__((format(printf, 6, 7)))
#endif
static void line(rg_menu_line *l, int *k, int cap, bool sel, bool header, const char *fmt, ...)
{
    if (*k >= cap) return;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(l[*k].text, sizeof l[*k].text, fmt, ap);
    va_end(ap);
    l[*k].selected = sel;
    l[*k].header = header;
    l[*k].indent = 4;
    (*k)++;
}

/* ------------------------------------------------------------ prompts */
static const char *const k_prompt_tag[RG_MP_COUNT] = {
    "up", "down", "left", "right", "accept", "back", "prev", "next", "toggle",
    "start", "select", "dpad", "ls", "rs",
};
static const char *const k_prompt_generic[RG_MP_COUNT] = {
    "up", "down", "left", "right", "accept", "back", "<prev", "next>", "F1 / Guide",
    "Start", "Select", "d-pad", "left stick", "right stick",
};

void rg_menu_set_prompt(rg_menu *m, rg_menu_prompt p, const char *label)
{
    if ((unsigned)p >= RG_MP_COUNT) return;
    snprintf(m->prompt[p], sizeof m->prompt[p], "%s", label ? label : "");
}

const char *rg_menu_prompt_text(const rg_menu *m, rg_menu_prompt p)
{
    if ((unsigned)p >= RG_MP_COUNT) return "";
    return m->prompt[p][0] ? m->prompt[p] : k_prompt_generic[p];
}

static size_t expand(const rg_menu *m, const char *in, char *out, size_t cap, bool esc_pct)
{
    size_t len = 0;
#define PUT(ch) do { if (len + 1 < cap) out[len] = (ch); len++; } while (0)
    for (const char *p = in; *p; ) {
        const char *rep = NULL;
        size_t used = 0;
        if (*p == '[') {
            const char *e = strchr(p, ']');
            if (e) {
                size_t L = (size_t)(e - p - 1);
                for (int i = 0; i < RG_MP_COUNT && !rep; i++)
                    if (strlen(k_prompt_tag[i]) == L && !strncmp(p + 1, k_prompt_tag[i], L))
                        rep = rg_menu_prompt_text(m, (rg_menu_prompt)i);
                if (!rep && L == 6 && !strncmp(p + 1, "cancel", 6)) rep = m->capture_hint;
                used = L + 2;
            }
        }
        if (rep) {
            for (const char *r = rep; *r; r++) {
                if (esc_pct && *r == '%') PUT('%');
                PUT(*r);
            }
            p += used;
        } else {
            PUT(*p);
            p++;
        }
    }
    if (cap) out[len < cap ? len : cap - 1] = 0;
#undef PUT
    return len;
}

size_t rg_menu_expand(const rg_menu *m, const char *in, char *out, size_t cap)
{
    return expand(m, in, out, cap, false);
}

/* line() whose template may hold prompt tags (expanded before the format). */
#if defined(__GNUC__) || defined(__clang__)
__attribute__((format(printf, 6, 7)))
#endif
static void hint(const rg_menu *m, rg_menu_line *l, int *k, int cap, bool sel, const char *tmpl, ...)
{
    if (*k >= cap) return;
    char fmt[640];
    expand(m, tmpl, fmt, sizeof fmt, true);
    va_list ap;
    va_start(ap, tmpl);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#endif
    vsnprintf(l[*k].text, sizeof l[*k].text, fmt, ap);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
    va_end(ap);
    l[*k].selected = sel;
    l[*k].header = true;
    l[*k].indent = 4;
    (*k)++;
}

/* The continuation indent of the line just written. */
static void indent_last(rg_menu_line *l, int k, int cap, int indent)
{
    if (k > 0 && k <= cap) l[k - 1].indent = indent;
}

int rg_menu_wrap(const rg_menu_line *in, int n, int cols, rg_menu_line *out, int cap)
{
    if (cols < 8) cols = 8;
    if (cols > (int)sizeof out[0].text - 1) cols = (int)sizeof out[0].text - 1;
    int k = 0;
    for (int i = 0; i < n && k < cap; i++) {
        const char *p = in[i].text;
        int ind = in[i].indent < 0 ? 0 : in[i].indent > cols / 2 ? cols / 2 : in[i].indent;
        int first = 1;
        do {
            int pre = first ? 0 : ind;
            int room = cols - pre;
            int len = (int)strlen(p);
            int take = len;
            if (len > room) {
                take = room;
                int lead = 0;
                while (p[lead] == ' ') lead++;
                /* the last space that fits (the break must leave something on this line) */
                for (int j = room; j > lead; j--)
                    if (p[j] == ' ') { take = j; break; }
                /* keep a UTF-8 sequence whole on a hard break */
                while (take > 1 && ((unsigned char)p[take] & 0xC0) == 0x80) take--;
            }
            rg_menu_line *o = &out[k++];
            *o = in[i];
            memset(o->text, ' ', (size_t)pre);
            memcpy(o->text + pre, p, (size_t)take);
            o->text[pre + take] = 0;
            /* no trailing blanks on a broken line */
            for (int e = pre + take - 1; e >= pre && o->text[e] == ' ' && p[take]; e--) o->text[e] = 0;
            p += take;
            while (*p == ' ') p++;
            first = 0;
        } while (*p && k < cap);
    }
    return k;
}

/* What a setting's flags mean, for the help area. */
static void flag_help(const rg_setting_def *d, char *out, size_t cap)
{
    out[0] = 0;
    size_t L = 0;
#define ADD(txt) do { L += (size_t)snprintf(out + L, L < cap ? cap - L : 0, "%s%s", L ? "; " : "  ", txt); } while (0)
    if (d->flags & RG_SETF_RESTART) ADD("[restart] takes effect after a restart");
    if (d->flags & RG_SETF_GAMEPLAY) ADD("[gameplay] changes game logic, off in Original");
    if (d->flags & RG_SETF_DISPLAY) ADD("display change: reverts in 15 s unless kept");
    if (d->flags & RG_SETF_PLACEHOLDER) ADD("(planned) stored, no effect yet");
#undef ADD
}

static int render_bindings(const rg_menu *m, uint64_t now, rg_menu_line *l, int cap)
{
    int k = 0;
    line(l, &k, cap, false, true, "SETTINGS  %s > %s", page_title(m->pages[m->page]), label_of(m, m->edit));
    hint(m, l, &k, cap, false, "[up] / [down] select   [left] / [right]: replace or remove   [accept] does it   [back] returns");
    char t[TOK_MAX][TOK_LEN];
    int n = edit_tokens(m, t);
    if (!n) line(l, &k, cap, false, false, "  %s", "(unbound)");
    for (int i = 0; i < n; i++) {
        bool sel = m->sub == i;
        char note[96];
        conflict_note(m, m->edit, t[i], note, sizeof note);
        line(l, &k, cap, sel, false, "%s %-24.24s %s  %s   %s%s", sel ? ">" : " ", t[i],
             sel && m->sub_col == 0 ? "[Replace]" : " Replace ", sel && m->sub_col == 1 ? "[Remove]" : " Remove ",
             note[0] ? "also: " : "", note);
        indent_last(l, k, cap, 49);
    }
    char def[256];
    rg_settings_default_text(m->s, m->edit, def, sizeof def);
    if (m->offer[0])
        line(l, &k, cap, m->sub == n + ED_ADD, false, "%s Add %s instead", m->sub == n + ED_ADD ? ">" : " ", m->offer);
    else
        line(l, &k, cap, m->sub == n + ED_ADD, false, "%s Add a binding", m->sub == n + ED_ADD ? ">" : " ");
    line(l, &k, cap, m->sub == n + ED_MOTION, false, "%s Capture mouse motion (move the mouse; confirm after)",
         m->sub == n + ED_MOTION ? ">" : " ");
    line(l, &k, cap, m->sub == n + ED_RESET, false, "%s Reset to default (%s)",
         m->sub == n + ED_RESET ? ">" : " ", def[0] ? def : "unbound");
    line(l, &k, cap, m->sub == n + ED_BACK, false, "%s Back", m->sub == n + ED_BACK ? ">" : " ");
    if (guarded(m)) {
        int kb = count_dev(t, n, DEV_KEYBOARD), gp = count_dev(t, n, DEV_GAMEPAD);
        line(l, &k, cap, false, true, "%s", "  Menu control: keeps at least one keyboard and one gamepad binding");
        if (!kb || !gp)
            line(l, &k, cap, false, true, "  WARNING: no %s binding; add one so the menu works from %s",
                 !kb ? "keyboard" : "gamepad", !kb ? "the keyboard" : "a gamepad");
    }
    if (m->capturing && m->capture_motion) {
        uint64_t left = m->capture_deadline > now ? m->capture_deadline - now : 0;
        line(l, &k, cap, false, true, "Move the mouse far in one direction (%d px) for %s", RG_MENU_MOTION_DIST,
             label_of(m, m->edit));
        hint(m, l, &k, cap, false, "  (keys and buttons are ignored; [cancel] cancels, %u s)",
             (unsigned)((left + 999) / 1000));
    } else if (m->capturing) {
        uint64_t left = m->capture_deadline > now ? m->capture_deadline - now : 0;
        line(l, &k, cap, false, true, "Press a key, mouse button, gamepad button or stick for %s",
             label_of(m, m->edit));
        hint(m, l, &k, cap, false, "  ([cancel] cancels, %u s)", (unsigned)((left + 999) / 1000));
    }
    if (m->confirm[0])
        hint(m, l, &k, cap, false, "Bind %s to %s?  [accept] = bind, [back] = discard", m->confirm,
             label_of(m, m->edit));
    if (m->status[0]) line(l, &k, cap, false, true, "%s", m->status);
    return k;
}

static int render_text(const rg_menu *m, rg_menu_line *l, int cap)
{
    int k = 0;
    const rg_setting_def *d = rg_settings_def(m->s, m->edit);
    line(l, &k, cap, false, true, "SETTINGS  %s > %s", page_title(m->pages[m->page]), label_of(m, m->edit));
    line(l, &k, cap, false, true, "%s", "keyboard: type, Enter = OK, Esc = cancel");
    hint(m, l, &k, cap, false, "gamepad: [up] / [down] / [left] / [right] + [accept] pick a key, [back] deletes, [prev] / [next] move the cursor");
    char shown[RG_MENU_TEXT_MAX + 2];
    snprintf(shown, sizeof shown, "%.*s|%s", m->text_cur, m->text, m->text + m->text_cur);
    line(l, &k, cap, false, false, "  [%s]", shown);
    indent_last(l, k, cap, 3);
    for (int r = 0; r < OSK_ROWS; r++) {
        char row[160];
        size_t L = 0;
        row[0] = 0;
        for (int c = 0; c < osk_len(r) && L < sizeof row - 12; c++) {
            bool on = r == m->osk_row && c == m->osk_col;
            if (r < OSK_CHAR_ROWS) L += (size_t)snprintf(row + L, sizeof row - L, on ? "[%c]" : " %c ", k_osk[r][c]);
            else L += (size_t)snprintf(row + L, sizeof row - L, on ? " [%s]" : "  %s ", k_osk_special[c]);
        }
        line(l, &k, cap, r == m->osk_row, false, "   %s", row);
    }
    if (d->help) line(l, &k, cap, false, true, "  %s", d->help);
    char fh[256];
    flag_help(d, fh, sizeof fh);
    if (fh[0]) line(l, &k, cap, false, true, "%s", fh);
    if (m->status[0]) line(l, &k, cap, false, true, "%s", m->status);
    return k;
}

int rg_menu_render(const rg_menu *m, uint64_t now, rg_menu_line *l, int cap)
{
    int k = 0;
    if (!m->open) return 0;
    if (m->view == RG_MENU_VIEW_BINDINGS) return render_bindings(m, now, l, cap);
    if (m->view == RG_MENU_VIEW_TEXT) return render_text(m, l, cap);
    line(l, &k, cap, false, true, "SETTINGS  (%d/%d) %s%s", m->page + 1, m->npages,
         page_title(m->pages[m->page]), m->dirty ? "  [unsaved]" : "");
    hint(m, l, &k, cap, false, "[prev] / [next] pages   [up] / [down] select   [left] / [right] change   [accept] edits   [back] closes   (open / close: [toggle])");
    int rows[RG_MENU_MAX_ROWS];
    int n = rg_menu_rows(m, rows, RG_MENU_MAX_ROWS);
    int cur = m->cursor < n ? m->cursor : n - 1;
    int pend[64];
    int npend = rg_settings_restart_pending(m->s, pend, 64);
    for (int r = 0; r < n; r++) {
        bool sel = r == cur;
        if (rows[r] >= 0) {
            int i = rows[r];
            const rg_setting_def *d = rg_settings_def(m->s, i);
            char v[256];
            rg_settings_display_text(m->s, i, v, sizeof v);
            if (d->type == RG_SET_BINDING && !v[0]) snprintf(v, sizeof v, "(unbound)");
            if (d->type == RG_SET_STRING && !v[0]) snprintf(v, sizeof v, "(empty)");
            const char *mk_pending = "";
            for (int p = 0; p < npend && p < 64; p++)
                if (pend[p] == i) mk_pending = " (restart pending)";
            line(l, &k, cap, sel, false, "%s %-30.30s %s%s%s%s%s%s", sel ? ">" : " ",
                 label_of(m, i), v,
                 (d->flags & RG_SETF_RESTART) ? " [restart]" : "",
                 (d->flags & RG_SETF_GAMEPLAY) ? " [gameplay]" : "",
                 (d->flags & RG_SETF_PLACEHOLDER) ? " (planned)" : "",
                 mk_pending,
                 rg_settings_overridden(m->s, i) ? " (--set)" : "");
            indent_last(l, k, cap, 33);
        } else {
            int code = -1 - rows[r];
            if (code == RG_ROW_SAVE) line(l, &k, cap, sel, false, "%s Save settings", sel ? ">" : " ");
            else if (code == RG_ROW_RESET_PAGE) line(l, &k, cap, sel, false, "%s Reset this page to defaults", sel ? ">" : " ");
            else if (code == RG_ROW_RESET_BINDINGS)
                line(l, &k, cap, sel, false, "%s Reset all bindings (game and menu) to defaults", sel ? ">" : " ");
            else {
                int pi = code / RG_ROW_STRIDE;
                line(l, &k, cap, sel, false, "%s Apply preset: %s%s", sel ? ">" : " ",
                     rg_settings_preset_label(m->s, pi),
                     rg_settings_matches_preset(m->s, rg_settings_preset_name(m->s, pi)) ? "  (active)" : "");
            }
        }
    }
    if (cur >= 0 && cur < n && rows[cur] >= 0) {
        const rg_setting_def *d = rg_settings_def(m->s, rows[cur]);
        if (d->help) line(l, &k, cap, false, true, "  %s", d->help);
        char fh[256];
        flag_help(d, fh, sizeof fh);
        if (fh[0]) line(l, &k, cap, false, true, "%s", fh);
    }
    if (rg_settings_trial_active(m->s)) {
        uint32_t left = rg_settings_trial_remaining(m->s, now);
        hint(m, l, &k, cap, false, "Keep these display settings?  [accept] = keep, [back] = revert (%u s)",
             (unsigned)((left + 999) / 1000));
    }
    if (m->status[0]) line(l, &k, cap, false, true, "%s", m->status);
    return k;
}
