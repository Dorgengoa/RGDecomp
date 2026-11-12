/* SPDX-License-Identifier: CC0-1.0 */
/* Discord Rich Presence over Discord's local IPC (docs/DISCORD.md).
 *
 * Our own minimal client (no Discord SDK, no third-party code): one background thread
 * connects lazily to the Discord desktop app's pipe (\\.\pipe\discord-ipc-0..9; on Linux the
 * discord-ipc-N socket under $XDG_RUNTIME_DIR / $TMPDIR / /tmp), sends the handshake
 * (op 0 {"v":1,"client_id":...}), then SET_ACTIVITY (op 1, with our pid) and answers PINGs.
 * Frames = u32 LE opcode, u32 LE length, JSON.
 *
 *   - Never blocks the caller: rg_discord_set_activity copies two strings under a lock and
 *     wakes the thread; the thread coalesces updates (at most one SET_ACTIVITY every 15 s,
 *     Discord's rate limit) and does every pipe operation itself.
 *   - Silent when Discord is absent: a failed connect is retried every 20 s (one CreateFile
 *     on a missing pipe, microseconds); a dropped connection the same way.
 *   - rg_discord_stop closes the pipe (Discord clears the activity) and joins the thread
 *     (at most ~1 s; a write stuck in a dead pipe is cancelled).
 *   - Reads no game state and writes none: the game logic and its run hash cannot see it.
 *   - Self-contained: no SDL, no renderer, no crash-handler interaction.
 */
#ifndef RG_DISCORD_H
#define RG_DISCORD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* client_id: the Discord application ID (decimal digits, 17-20 of them).  NULL / empty /
 * not digits = idle: no thread, every other call is a no-op.  0 started, 1 idle. */
int rg_discord_start(const char *client_id);
/* The activity text (UTF-8; NULL / "" = line omitted).  Cheap, any thread. */
void rg_discord_set_activity(const char *details, const char *state);
void rg_discord_stop(void);

/* "1234..." -> 1 when it looks like an application ID */
int rg_discord_valid_id(const char *client_id);

/* JSON string escaping (tests): writes "..." with quotes; returns the length or -1 if cap
 * is too small. */
int rg_discord_json_str(char *out, int cap, const char *s);

typedef struct rg_discord_stats {
    int running;          /* the thread exists */
    int connected;        /* handshake answered (READY) */
    uint32_t connects;    /* successful pipe connects */
    uint32_t activities;  /* SET_ACTIVITY frames written */
    uint32_t pongs;       /* PINGs answered */
    uint32_t errors;      /* error replies / dropped connections */
} rg_discord_stats;
void rg_discord_get_stats(rg_discord_stats *out);

/* Tests: the pipe / socket name prefix ("discord-ipc-" by default; also $RG_DISCORD_IPC),
 * the retry and the activity intervals in ms.  Call before rg_discord_start. */
void rg_discord_test_config(const char *ipc_prefix, int retry_ms, int activity_ms);

#ifdef __cplusplus
}
#endif

#endif
