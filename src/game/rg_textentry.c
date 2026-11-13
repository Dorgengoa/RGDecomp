/* SPDX-License-Identifier: CC0-1.0 */
/* Copy and paste for the game's own text entry (lane insnet 2026-11-12, option B of
 * docs/INSECTRON-VERSUS.md "Passwords").
 *
 * Paste: Ctrl+V while the text entry's character palette is up hands the clipboard text to
 * the game the way its own developer shortcut did (TextEntryPaletteSelectState_435270 calls
 * TextEntryBuildTemplateText_4356d0(entry, 0, text); override of that state).  Only the
 * characters the entry accepts survive (passwords: the 58-character alphabet; names: letters
 * and digits; whitespace, dashes and anything else are dropped).  The player still presses
 * Confirm and the game's own checksum decides.
 * Copy: every password the game shows (View team, Triangle) is remembered
 * (TextEntryBuildTemplateText_4356d0 override); Ctrl+C puts the last one on the clipboard, and
 * each shown password is also appended once to <saves>/insectron-passwords.txt with its team
 * name, so a player on a gamepad finds it without a keyboard.
 * Test hooks: $RG_PASTE_TEXT=FILE + $RG_PASTE_AT=FIELD (a paste from FILE from that field on,
 * once); $RG_COPY_AT=FIELD (a Ctrl+C at that field). */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "host.h"
#include "rg_runtime.h"

int rg_insnet_ui_entry_pending(void);   /* rg_insnet_ui.c */

#define PW_CHARS 143
static const char k_b58[] = "0123456789abcdefghijkmnpqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ";

static char g_shown[PW_CHARS + 1];
static char g_logged[8][PW_CHARS + 1];
static int g_nlogged;
static int g_paste_hook_done;

static int is_b58(int c) { return c && strchr(k_b58, c) != NULL; }
static int is_alnum(int c) { return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

static uint64_t field_now(void) { return rg_runtime_get_stats()->fields; }

/* ---- the password's team name (a host copy of InsectTeamCodeDecode_431570's first fields;
 * tools/fixtures/insectpw.py has the whole codec) */
static uint32_t crc16(const uint8_t *b, size_t n)
{
    uint32_t c = 0xFFFF;
    for (size_t i = 0; i < n; i++) {
        c ^= (uint32_t)b[i] << 8;
        for (int k = 0; k < 8; k++) c = (c & 0x8000) ? ((c << 1) ^ 0x1021) : (c << 1);
    }
    return ~c & 0xFFFF;
}

static int team_name(const char *pw, char name[9])
{
    uint8_t raw[104];
    name[0] = 0;
    if (strlen(pw) != PW_CHARS) return -1;
    for (int blk = 0; blk < 13; blk++) {
        uint64_t v = 0, m = 1;
        for (int i = 0; i < 11; i++) {
            const char *p = strchr(k_b58, pw[blk * 11 + i]);
            if (!p || !*p) return -1;
            v += (uint64_t)(p - k_b58) * m;
            m *= 58;
        }
        for (int i = 0; i < 8; i++) raw[blk * 8 + i] = (uint8_t)(v >> (8 * i));
    }
    const size_t n = sizeof raw;
    uint32_t x = 0x014A76E0u;
    x = x * 0x21FC436u + 1u;
    size_t q = x % (n - 2);
    uint8_t t = raw[n - 2];
    raw[n - 2] = raw[q];
    raw[q] = t;
    uint32_t key = raw[n - 2] | (uint32_t)raw[n - 1] << 8;
    x = key + 0x05888F27u;
    for (size_t i = 0; i < n - 2; i++) {
        x = x * 0x21FC436u + 1u;
        raw[i] ^= (uint8_t)(x >> 24);
    }
    static const uint8_t k[] = "DC3InsectronEncryptKey";
    if (((key ^ crc16(k, sizeof k - 1) ^ 0x62D3) & 0xFFFF) != crc16(raw, n - 2)) return -1;
    int pos = 0, o = 0;
    for (int c = 0; c < 8; c++) {
        int v = 0;
        for (int i = 0; i < 6; i++, pos++)
            if (raw[pos >> 3] & (1 << (pos & 7))) v |= 1 << i;
        char ch = 0;
        if (v == 1) ch = ' ';
        else if (v >= 2 && v < 0x1C) ch = (char)(v + 0x3F);
        else if (v >= 0x1C && v < 0x36) ch = (char)(v + 0x45);
        else if (v >= 0x36 && v < 0x40) ch = (char)(v - 6);
        if (ch) name[o++] = ch;
    }
    name[o] = 0;
    return 0;
}

static void log_password(const char *pw)
{
    for (int i = 0; i < g_nlogged; i++)
        if (!strcmp(g_logged[i], pw)) return;
    snprintf(g_logged[g_nlogged % 8], sizeof g_logged[0], "%s", pw);
    g_nlogged++;
    const rg_runtime_config *c = rg_runtime_get_config();
    const char *saves = c && c->saves_dir ? c->saves_dir : getenv("RG_SAVES");
    char path[1100];
    snprintf(path, sizeof path, "%s/insectron-passwords.txt", saves && *saves ? saves : "saves");
    FILE *f = fopen(path, "a");
    if (!f) return;
    char name[9];
    if (team_name(pw, name)) snprintf(name, sizeof name, "?");
    time_t now = time(NULL);
    char when[32] = "";
    struct tm *tm = localtime(&now);
    if (tm) strftime(when, sizeof when, "%Y-%m-%d %H:%M", tm);
    /* shown in groups of five, as on screen; the game's entry ignores the dashes on a paste */
    fprintf(f, "%s  team %-8s  ", when, name);
    for (int i = 0; i < PW_CHARS; i++) fprintf(f, "%s%c", i && i % 5 == 0 ? "-" : "", pw[i]);
    fprintf(f, "\n");
    fclose(f);
    fprintf(stderr, "rg-game: Insectron password of team %s written to %s\n", name, path);
}

/* TextEntryBuildTemplateText_4356d0 override: the text the entry is about to show.  mode = the
 * entry's mode (0 = password), filled = arg1 == 0 (a text, not the blank template) */
void rg_textentry_shown(const char *text, int mode, int filled)
{
    if (!filled || (mode != 0 && mode != 4) || !text) return;   /* 0 = password entry, 4 = View team display */
    char pw[PW_CHARS + 1];
    int n = 0;
    for (const char *c = text; *c && n <= PW_CHARS; c++) {
        if (!is_b58((unsigned char)*c)) return;
        pw[n++] = *c;
    }
    if (n != PW_CHARS) return;
    pw[n] = 0;
    memcpy(g_shown, pw, sizeof g_shown);
    log_password(pw);
}

/* the text the paste puts in: out is zero-filled to cap (BuildTemplateText reads one source
 * character per input cell, past the end too).  Returns the count, 0 = no paste now. */
static int is_sep(int c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '-' || c == '*'; }

/* a password inside a longer text (a chat line, the passwords file): runs of password-alphabet
 * words separated by spaces / dashes / line breaks whose letters add up to exactly 143, and whose
 * checksum is right (team_name decodes); words around it ("here's my team:") are skipped */
static int find_password(const char *in, char *out)
{
    const char *starts[1024];
    int lens[1024], nt = 0;
    for (const char *c = in; *c && nt < 1024;) {
        while (*c && is_sep((unsigned char)*c)) c++;
        if (!*c) break;
        starts[nt] = c;
        while (*c && !is_sep((unsigned char)*c)) c++;
        lens[nt] = (int)(c - starts[nt]);
        nt++;
    }
    for (int i = 0; i < nt; i++) {
        int L = 0, ok = 1;
        char pw[PW_CHARS + 1];
        for (int j = i; j < nt && L < PW_CHARS && ok; j++) {
            for (int k = 0; k < lens[j] && ok; k++) ok = is_b58((unsigned char)starts[j][k]);
            if (!ok || L + lens[j] > PW_CHARS) break;
            memcpy(pw + L, starts[j], (size_t)lens[j]);
            L += lens[j];
        }
        if (L != PW_CHARS) continue;
        pw[L] = 0;
        char name[9];
        if (team_name(pw, name) == 0) {
            memcpy(out, pw, PW_CHARS + 1);
            return PW_CHARS;
        }
    }
    return 0;
}

static int filter_paste(const char *in, char *out, int cap, int mode)
{
    int n = 0, maxn = mode == 0 ? PW_CHARS : 64;
    memset(out, 0, (size_t)cap);
    if (mode == 0 && cap > PW_CHARS && find_password(in, out)) return PW_CHARS;
    for (const char *c = in; *c && n < cap - 1 && n < maxn; c++) {
        int ch = (unsigned char)*c;
        if (mode == 0 ? is_b58(ch) : is_alnum(ch)) out[n++] = (char)ch;
    }
    return n;
}

int rg_textentry_paste(char *out, int cap, int mode)
{
    if (!out || cap < 2) return 0;
    rg_host *h = rg_runtime_host();
    char clip[2048];
    int got = h ? rg_host_take_paste(h, clip, sizeof clip) : 0;
    if (!got && !g_paste_hook_done) {
        const char *at = getenv("RG_PASTE_AT"), *file = getenv("RG_PASTE_TEXT");
        if (at && file && field_now() >= strtoull(at, NULL, 0)) {
            g_paste_hook_done = 1;
            FILE *f = fopen(file, "rb");
            if (f) {
                size_t r = fread(clip, 1, sizeof clip - 1, f);
                clip[r] = 0;
                fclose(f);
                got = 1;
            }
        }
    }
    if (!got) return 0;
    int n;
    if (rg_insnet_ui_entry_pending()) {
        /* the online battle's address entry: host:port / IPv4 / [IPv6]:port characters */
        memset(out, 0, (size_t)cap);
        n = 0;
        for (const char *c = clip; *c && n < cap - 1 && n < 60; c++)
            if (is_alnum((unsigned char)*c) || *c == '.' || *c == ':' || *c == '-' || *c == '[' || *c == ']')
                out[n++] = *c;
    } else
        n = filter_paste(clip, out, cap, mode);
    fprintf(stderr, "rg-game: paste of %d character(s) into the text entry (mode %d)\n", n, mode);
    return n;
}

/* per field (rg-game main loop): Ctrl+C -> the clipboard */
void rg_textentry_field(uint64_t k)
{
    rg_host *h = rg_runtime_host();
    int req = h ? rg_host_take_copy_request(h) : 0;
    const char *at = getenv("RG_COPY_AT");
    if (at && strtoull(at, NULL, 0) == k) req = 1;
    if (!req) return;
    if (!g_shown[0]) {
        fprintf(stderr, "rg-game: Ctrl+C: no Insectron password shown yet\n");
        return;
    }
    int ok = h && rg_host_set_clipboard(h, g_shown) == 0;
    fprintf(stderr, "rg-game: Ctrl+C: password %.10s... %s\n", g_shown, ok ? "copied to the clipboard" : "(no clipboard)");
}
