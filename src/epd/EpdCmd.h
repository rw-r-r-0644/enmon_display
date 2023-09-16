/**
 * EpdCmd.h
 *
 * Waveshare 4.2inch e-Paper (B) command definitions
 * Based on 4.2inch-e-paper-b-specification.pdf specs
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once

#define CMD_PSR     0x00    /* panel setting */
    #define PSR_RES(r)  (((r) & 0b11) << 6)
        #define RES_400_300     0b00
        #define RES_320_300     0b01
        #define RES_320_240     0b10
        #define RES_200_300     0b11
    #define PSR_LUT_REG (1 << 5)
    #define PSR_KW_R    (1 << 4)
    #define PSR_UD      (1 << 3)
    #define PSR_SHL     (1 << 2)
    #define PSR_SHD_N   (1 << 1)
    #define PSR_RST_N   (1 << 0)
#define CMD_POF     0x02    /* power OFF */
#define CMD_PON     0x04    /* power ON */
#define CMD_DSLP    0x07    /* deep sleep */
    #define DSLP_CHECK_MAGIC    0xA5
#define CMD_DTM1    0x10    /* data start transmission 1 */
#define CMD_DRF     0x12    /* display refresh */
#define CMD_DTM2    0x13    /* data start transmission 2 */
#define CMD_CDI     0x50    /* VCOM and data interval setting */
    #define CDI_VBD(r)  (((r) & 0b11) << 6)
    #define CDI_DDX(r)  (((r) & 0b11) << 4)
    #define CDI_CDI(r)  (((r) & 0b1111) << 0)
