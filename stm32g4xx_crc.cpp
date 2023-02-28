#include "stm32g4xx_crc.h"

#include "stm32g4xx_ll_crc.h" // NOTE: replace header for your STM32 family
#include "stm32g4xx_ll_bus.h" // NOTE: replace header for your STM32 family


void crc_init()
{
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_CRC);

  if (!LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_CRC))
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CRC);
}

void crc_deinit()
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_CRC);
}


std::uint32_t crc32_mpeg2(const std::uint8_t* data, std::size_t size)
{
  if (!data || !size)
    return {};

  LL_CRC_ResetCRCCalculationUnit(CRC);
  LL_CRC_SetInputDataReverseMode(CRC, LL_CRC_INDATA_REVERSE_NONE);
  LL_CRC_SetOutputDataReverseMode(CRC, LL_CRC_OUTDATA_REVERSE_NONE);

  for (std::size_t i = 0; i < size; i++)
    LL_CRC_FeedData8(CRC, data[i]);

  return LL_CRC_ReadData32(CRC);
}

std::uint32_t crc32_mpeg2(const std::uint32_t* data, std::size_t size)
{
  if (!data || !size)
    return {};

  LL_CRC_ResetCRCCalculationUnit(CRC);
  LL_CRC_SetInputDataReverseMode(CRC, LL_CRC_INDATA_REVERSE_NONE);
  LL_CRC_SetOutputDataReverseMode(CRC, LL_CRC_OUTDATA_REVERSE_NONE);

  for (std::size_t i = 0; i < size; i++)
    LL_CRC_FeedData32(CRC, __REV(data[i]));

  return LL_CRC_ReadData32(CRC);
}


std::uint32_t crc32(const std::uint8_t* data, std::size_t size)
{
  if (!data || !size)
    return {};

  LL_CRC_ResetCRCCalculationUnit(CRC);
  LL_CRC_SetInputDataReverseMode(CRC, LL_CRC_INDATA_REVERSE_BYTE);
  LL_CRC_SetOutputDataReverseMode(CRC, LL_CRC_OUTDATA_REVERSE_BIT);

  for (std::size_t i = 0; i < size; i++)
    LL_CRC_FeedData8(CRC, data[i]);

  return LL_CRC_ReadData32(CRC) ^ 0xFFFFFFFFU;
}


std::uint32_t crc32(const std::uint32_t* data, std::size_t size)
{
  if (!data || !size)
    return {};

  LL_CRC_ResetCRCCalculationUnit(CRC);
  LL_CRC_SetInputDataReverseMode(CRC, LL_CRC_INDATA_REVERSE_WORD);
  LL_CRC_SetOutputDataReverseMode(CRC, LL_CRC_OUTDATA_REVERSE_BIT);

  for (std::size_t i = 0; i < size; i++)
    LL_CRC_FeedData32(CRC, data[i]);

  return LL_CRC_ReadData32(CRC) ^ 0xFFFFFFFFU;
}


std::uint32_t crc32_bzip2(const std::uint8_t* data, std::size_t size)
{
  return crc32_mpeg2(data, size) ^ 0xFFFFFFFFU;
}

std::uint32_t crc32_bzip2(const std::uint32_t* data, std::size_t size)
{
  return crc32_mpeg2(data, size) ^ 0xFFFFFFFFU;
}
