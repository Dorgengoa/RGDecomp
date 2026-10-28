// SPDX-License-Identifier: CC0-1.0
// MVI movie conversion (docs/MVI.md): descramble a Rogue Galaxy .MVI movie and split it
// into a standard MPEG-2 program stream (video, bit-exact, not re-encoded) plus a PCM WAV.
#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>

namespace rgx::mvi {

// First word of the per-sector keystream. Derived from the key string the game keeps
// obfuscated at 0x0044B330 in SCUS_974.90 (see docs/MVI.md, "Encryption").
constexpr uint32_t kSeed = 0x98293255u;
// Keystream multiplier: k[i+1] = k[i] * kMul (mod 2^32), one 32-bit word per step.
constexpr uint32_t kMul = 0x02E90EDDu;
constexpr size_t kSector = 2048;

// The 2048-byte keystream that every sector is XORed with.
const uint8_t* keystream();

// XOR `len` bytes that start at byte offset `file_offset` of an MVI file with the
// keystream. The transform is its own inverse (it both scrambles and descrambles).
void descramble(uint8_t* buf, size_t len, uint64_t file_offset);

// Seed computed the way the game does it: de-obfuscate the stored key bytes
// (c ^ k, k = k * 13 + 1 starting at 0x3E) and sum the result into 4 byte lanes.
uint32_t seed_from_stored_key(const uint8_t* key, size_t len);

struct MovieInfo {
    // Video (MPEG-2, first sequence header and sequence extension).
    int width = 0, height = 0;
    int aspect_code = 0;          // aspect_ratio_information
    int frame_rate_code = 0;      // 4 = 30000/1001, 5 = 30
    int profile_level = 0;        // 0x48 = Main Profile @ Main Level
    uint64_t pictures = 0;        // picture start codes in the stream
    uint64_t video_bytes = 0;     // elementary stream bytes
    int64_t video_first_pts = -1; // 90 kHz
    // Audio (SShd header).
    uint32_t audio_rate = 0, audio_channels = 0, audio_interleave = 0;
    uint64_t audio_frames_in = 0;  // sample frames in SSbd
    uint64_t audio_frames_out = 0; // sample frames written to the WAV
    int64_t audio_first_pts = -1;  // 90 kHz
    int64_t audio_shift_frames = 0; // >0: silence prepended, <0: frames dropped
    // Container.
    uint64_t packs = 0, video_packets = 0, audio_packets = 0;
};

// Convert one movie. `in_size` bytes are read from `in`. On success writes
// `out_mpg` (MPEG-PS with only the video stream) and `out_wav` (16-bit PCM, sample 0
// aligned to the first video PTS), fills `info` and returns true. On failure returns
// false with a message in `err`; partial outputs are removed.
bool convert_movie(const std::filesystem::path& in, const std::filesystem::path& out_mpg,
                   const std::filesystem::path& out_wav, MovieInfo* info, std::string* err);

// Same, on an in-memory MVI image (used by the unit tests).
bool convert_movie_memory(const uint8_t* data, size_t size, std::string* mpg, std::string* wav,
                          MovieInfo* info, std::string* err);

}  // namespace rgx::mvi
