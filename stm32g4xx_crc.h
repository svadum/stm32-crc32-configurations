#pragma once

#include <cstdint>

void crc_init();
void crc_deinit();

// CRC32-MPEG2 (STM32 default): Poly=0x04C11DB7 Init=0xFFFFFFFF RefIn=false RefOut=false XorOut=0x00000000
std::uint32_t crc32_mpeg2(const std::uint8_t* data, std::size_t size);
std::uint32_t crc32_mpeg2(const std::uint32_t* data, std::size_t size);

// CRC32: Poly=0x04C11DB7 Init=0xFFFFFFFF RefIn=true RefOut=true XorOut=0xFFFFFFFF
std::uint32_t crc32(const std::uint8_t* data, std::size_t size);
std::uint32_t crc32(const std::uint32_t* data, std::size_t size);

// CRC32-BZIP2: Poly=0x04C11DB7 Init=0xFFFFFFFF RefIn=false RefOut=false XorOut=0xFFFFFFFF
std::uint32_t crc32_bzip2(const std::uint8_t* data, std::size_t size);
std::uint32_t crc32_bzip2(const std::uint32_t* data, std::size_t size);