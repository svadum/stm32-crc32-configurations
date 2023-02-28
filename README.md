# stm32-crc32-configurations
STM32 CRC32 (CCIT, BZIP, MPEG-2) configuration examples

### Description
This repository contains STM32 hardware CRC32 calcaulation examples (CRC32, CRC32-MPEG2, CRC32-BZIP2) for STM32G4 familiy.
However, driver's code should be also compatible with most chips that have CRC module, because driver uses STM32 LL library (just replace stm32g4xx_ headers for your family).

### Usage:
```c++
#include <cassert>
#include <cstdint>

#include "stm32g4xx_crc.h"

int main()
{
    crc_init();

    // 8 bytes
    constexpr std::uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    constexpr std::uint32_t crc32_expected       = 0x3FCA88C5;
    constexpr std::uint32_t crc32_mpeg2_expected = 0x140B8DD8;
    constexpr std::uint32_t crc32_bzip2_expected = 0xEBF47227;

    constexpr std::size_t data_size_bytes = sizeof(data);
    constexpr std::size_t data_size_words = data_size_bytes / sizeof(std::uint32_t);

    const std::uint32_t crc32_by_byte = crc32(data, data_size_bytes);
    const std::uint32_t crc32_by_word = crc32(reinterpret_cast<const std::uint32_t *>(data), data_size_words);

    assert(crc32_by_byte == crc32_expected);
    assert(crc32_by_word == crc32_expected);
    assert(crc32_by_byte == crc32_by_word);

    const std::uint32_t crc32_mpeg2_by_byte = crc32_mpeg2(data, data_size_bytes);
    const std::uint32_t crc32_mpeg2_by_word = crc32_mpeg2(reinterpret_cast<const std::uint32_t *>(data), data_size_words);

    assert(crc32_mpeg2_by_byte == crc32_mpeg2_expected);
    assert(crc32_mpeg2_by_word == crc32_mpeg2_expected);
    assert(crc32_mpeg2_by_byte == crc32_mpeg2_by_word);

    const std::uint32_t crc32_bzip2_by_byte = crc32_bzip2(data, data_size_bytes);
    const std::uint32_t crc32_bzip2_by_word = crc32_bzip2(reinterpret_cast<const std::uint32_t *>(data), data_size_words);

    assert(crc32_bzip2_by_byte == crc32_bzip2_expected);
    assert(crc32_bzip2_by_word == crc32_bzip2_expected);
    assert(crc32_bzip2_by_byte == crc32_bzip2_by_word);

    crc_deinit();
}
```
see also: [stm32g4xx_crc.cpp](stm32g4xx_crc.cpp)
### Results:
![readme_image](https://user-images.githubusercontent.com/22641386/221810902-625f22d2-5341-41e3-87f4-874f9331e98d.png)
