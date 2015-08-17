/*-
 * Copyright (c) 2011
 *	Ben Gray <ben.r.gray@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: soc2013/dpl/head/sys/arm/ti/omap4/omap4_reg.h 240379 2012-08-15 06:31:32Z gonzo $
 */

/*
 * Texas Instruments - OMAP44xx series processors
 *
 * Reference:
 *  OMAP44xx Applications Processor
 *   Technical Reference Manual
 *  (omap44xx_techref.pdf)
 *
 *
 * Note:
 *  The devices are mapped into address above 0xD000_0000 as the kernel space
 *  memory is at 0xC000_0000 and above.  The first 256MB after this is reserved
 *  for the size of the kernel, everything above that is reserved for SoC
 *  devices.
 *
 */
#ifndef _OMAP44XX_REG_H_
#define _OMAP44XX_REG_H_

#ifndef _LOCORE
#include <sys/types.h>		/* for uint32_t */
#endif





/* Physical/Virtual address for SDRAM controller */

#define OMAP44XX_SMS_VBASE			0x6C000000UL
#define OMAP44XX_SMS_HWBASE			0x6C000000UL
#define OMAP44XX_SMS_SIZE			0x01000000UL

#define OMAP44XX_SDRC_VBASE			0x6D000000UL
#define OMAP44XX_SDRC_HWBASE		0x6D000000UL
#define OMAP44XX_SDRC_SIZE			0x01000000UL



/* Physical/Virtual address for I/O space */

#define OMAP44XX_L3_EMU_VBASE		0xD4000000UL
#define OMAP44XX_L3_EMU_HWBASE		0x54000000UL
#define OMAP44XX_L3_EMU_SIZE		0x00200000UL

#define OMAP44XX_L3_EMIF1_VBASE     0xEC000000UL
#define OMAP44XX_L3_EMIF1_HWBASE    0x4C000000UL
#define OMAP44XX_L3_EMIF1_SIZE      0x01000000UL

#define OMAP44XX_L3_EMIF2_VBASE     0xED000000UL
#define OMAP44XX_L3_EMIF2_HWBASE    0x4D000000UL
#define OMAP44XX_L3_EMIF2_SIZE      0x01000000UL


#define OMAP44XX_L4_CORE_VBASE		0xEA000000UL
#define OMAP44XX_L4_CORE_HWBASE		0x4A000000UL
#define OMAP44XX_L4_CORE_SIZE		0x01000000UL

#define OMAP44XX_L4_WAKEUP_VBASE	0xEA300000UL
#define OMAP44XX_L4_WAKEUP_HWBASE	0x4A300000UL
#define OMAP44XX_L4_WAKEUP_SIZE		0x00040000UL

#define OMAP44XX_L4_PERIPH_VBASE	0xE8000000UL
#define OMAP44XX_L4_PERIPH_HWBASE	0x48000000UL
#define OMAP44XX_L4_PERIPH_SIZE		0x01000000UL

#define OMAP44XX_L4_ABE_VBASE		0xE9000000UL
#define OMAP44XX_L4_ABE_HWBASE		0x49000000UL
#define OMAP44XX_L4_ABE_SIZE		0x00100000UL


/* Physical/Virtual address for MPU Subsystem space */

#define OMAP44XX_MPU_SUBSYS_VBASE   (OMAP44XX_L4_PERIPH_VBASE + 0x00240000UL)
#define OMAP44XX_MPU_SUBSYS_HWBASE  (OMAP44XX_L4_PERIPH_HWBASE + 0x00240000UL)
#define OMAP44XX_MPU_SUBSYS_SIZE    0x00004000UL

/*
 * MPU Subsystem addresss offsets
 */
#define OMAP44XX_SCU_OFFSET                     0x00000000UL
#define OMAP44XX_GIC_CPU_OFFSET                 0x00000100UL
#define OMAP44XX_GBL_TIMER_OFFSET               0x00000200UL
#define OMAP44XX_PRV_TIMER_OFFSET               0x00000600UL
#define OMAP44XX_GIC_DIST_OFFSET                0x00001000UL
#define OMAP44XX_PL310_OFFSET                   0x00002000UL
#define OMAP44XX_CORTEXA9_SOCKET_PRCM_OFFSET    0x00003000UL
#define OMAP44XX_CORTEXA9_PRM_OFFSET            0x00003200UL
#define OMAP44XX_CORTEXA9_CPU0_OFFSET           0x00003400UL
#define OMAP44XX_CORTEXA9_CPU1_OFFSET           0x00003800UL

#define OMAP44XX_SCU_HWBASE         (OMAP44XX_MPU_SUBSYS_HWBASE + OMAP44XX_SCU_OFFSET)
#define OMAP44XX_SCU_VBASE          (OMAP44XX_MPU_SUBSYS_VBASE  + OMAP44XX_SCU_OFFSET)
#define OMAP44XX_SCU_SIZE           0x00000080UL
#define OMAP44XX_GIC_CPU_HWBASE     (OMAP44XX_MPU_SUBSYS_HWBASE + OMAP44XX_GIC_CPU_OFFSET)
#define OMAP44XX_GIC_CPU_VBASE      (OMAP44XX_MPU_SUBSYS_VBASE  + OMAP44XX_GIC_CPU_OFFSET)
#define OMAP44XX_GIC_CPU_SIZE       0x00000100UL
#define OMAP44XX_GBL_TIMER_HWBASE   (OMAP44XX_MPU_SUBSYS_HWBASE + OMAP44XX_GBL_TIMER_OFFSET)
#define OMAP44XX_GBL_TIMER_VBASE    (OMAP44XX_MPU_SUBSYS_VBASE  + OMAP44XX_GBL_TIMER_OFFSET)
#define OMAP44XX_GBL_TIMER_SIZE     0x00000100UL
#define OMAP44XX_PRV_TIMER_HWBASE   (OMAP44XX_MPU_SUBSYS_HWBASE + OMAP44XX_PRV_TIMER_OFFSET)
#define OMAP44XX_PRV_TIMER_VBASE    (OMAP44XX_MPU_SUBSYS_VBASE  + OMAP44XX_PRV_TIMER_OFFSET)
#define OMAP44XX_PRV_TIMER_SIZE     0x00000100UL
#define OMAP44XX_GIC_DIST_HWBASE    (OMAP44XX_MPU_SUBSYS_HWBASE + OMAP44XX_GIC_DIST_OFFSET)
#define OMAP44XX_GIC_DIST_VBASE     (OMAP44XX_MPU_SUBSYS_VBASE  + OMAP44XX_GIC_DIST_OFFSET)
#define OMAP44XX_GIC_DIST_SIZE      0x00000100UL
#define OMAP44XX_PL310_HWBASE       (OMAP44XX_MPU_SUBSYS_HWBASE + OMAP44XX_PL310_OFFSET)
#define OMAP44XX_PL310_VBASE        (OMAP44XX_MPU_SUBSYS_VBASE  + OMAP44XX_PL310_OFFSET)
#define OMAP44XX_PL310_SIZE         0x00001000UL




/*
 * L4-CORE Physical/Virtual addresss offsets
 */
#define OMAP44XX_SCM_OFFSET         0x00002000UL
#define OMAP44XX_CM_OFFSET          0x00004000UL
#define OMAP44XX_SDMA_OFFSET        0x00056000UL
#define OMAP44XX_USB_TLL_OFFSET     0x00062000UL
#define OMAP44XX_USB_UHH_OFFSET     0x00064000UL
#define OMAP44XX_USB_OHCI_OFFSET    0x00064800UL
#define OMAP44XX_USB_EHCI_OFFSET    0x00064C00UL
#define OMAP44XX_MCBSP1_OFFSET      0x00074000UL
#define OMAP44XX_MCBSP5_OFFSET      0x00096000UL
#define OMAP44XX_SCM_PADCONF_OFFSET 0x00100000UL

/*
 * L4-WAKEUP Physical/Virtual addresss offsets
 */
#define OMAP44XX_PRM_OFFSET         0x00006000UL
#define OMAP44XX_SCRM_OFFSET        0x0000A000UL
#define OMAP44XX_GPIO1_OFFSET       0x00010000UL
#define OMAP44XX_GPTIMER1_OFFSET    0x00018000UL



/*
 * L4-PERIPH Physical/Virtual addresss offsets
 */
#define OMAP44XX_UART3_OFFSET		0x00020000UL
#define OMAP44XX_GPTIMER2_OFFSET	0x00032000UL
#define OMAP44XX_GPTIMER3_OFFSET	0x00034000UL
#define OMAP44XX_GPTIMER4_OFFSET	0x00036000UL
#define OMAP44XX_GPTIMER9_OFFSET	0x0003E000UL
#define OMAP44XX_GPIO2_OFFSET		0x00055000UL
#define OMAP44XX_GPIO3_OFFSET		0x00057000UL
#define OMAP44XX_GPIO4_OFFSET		0x00059000UL
#define OMAP44XX_GPIO5_OFFSET		0x0005B000UL
#define OMAP44XX_GPIO6_OFFSET		0x0005D000UL
#define OMAP44XX_I2C3_OFFSET		0x00060000UL
#define OMAP44XX_UART1_OFFSET		0x0006A000UL
#define OMAP44XX_UART2_OFFSET		0x0006C000UL
#define OMAP44XX_UART4_OFFSET		0x0006E000UL
#define OMAP44XX_I2C1_OFFSET		0x00070000UL
#define OMAP44XX_I2C2_OFFSET		0x00072000UL
#define OMAP44XX_SLIMBUS2_OFFSET	0x00076000UL
#define OMAP44XX_ELM_OFFSET			0x00078000UL
#define OMAP44XX_GPTIMER10_OFFSET	0x00086000UL
#define OMAP44XX_GPTIMER11_OFFSET	0x00088000UL
#define OMAP44XX_MCBSP4_OFFSET		0x00096000UL
#define OMAP44XX_MCSPI1_OFFSET		0x00098000UL
#define OMAP44XX_MCSPI2_OFFSET		0x0009A000UL
#define OMAP44XX_MMCHS1_OFFSET		0x0009C000UL
#define OMAP44XX_MMCSD3_OFFSET		0x000AD000UL
#define OMAP44XX_MMCHS2_OFFSET		0x000B4000UL
#define OMAP44XX_MMCSD4_OFFSET		0x000D1000UL
#define OMAP44XX_MMCSD5_OFFSET		0x000D5000UL
#define OMAP44XX_I2C4_OFFSET		0x00350000UL

/* The following are registers defined as part of the ARM MPCORE system,
 * they are not SoC components rather registers that control the MPCORE core.
 */
// #define OMAP44XX_SCU_OFFSET			0x48240000	/* Snoop control unit */
// #define OMAP44XX_GIC_PROC_OFFSET	0x48240100	/* Interrupt controller unit */
// #define OMAP44XX_MPU_TIMER_OFFSET	0x48240600
// #define OMAP44XX_GIC_INTR_OFFSET	0x48241000
// #define OMAP44XX_PL310_OFFSET		0x48242000	/* L2 Cache controller */


/*
 * L4-ABE Physical/Virtual addresss offsets
 */
#define OMAP44XX_GPTIMER5_OFFSET	0x00038000UL
#define OMAP44XX_GPTIMER6_OFFSET	0x0003A000UL
#define OMAP44XX_GPTIMER7_OFFSET	0x0003C000UL
#define OMAP44XX_GPTIMER8_OFFSET	0x0003E000UL





/*
 * System Control Module
 */
#define OMAP44XX_SCM_HWBASE				(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_SCM_OFFSET)
#define OMAP44XX_SCM_VBASE				(OMAP44XX_L4_CORE_VBASE + OMAP44XX_SCM_OFFSET)
#define OMAP44XX_SCM_SIZE				0x00001000UL



/*
 *
 */
#define OMAP44XX_CM_HWBASE				(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_CM_OFFSET)
#define OMAP44XX_CM_VBASE				(OMAP44XX_L4_CORE_VBASE + OMAP44XX_CM_OFFSET)
#define OMAP44XX_CM_SIZE				0x00001500UL


/*
 *
 */
#define OMAP44XX_PRM_HWBASE				(OMAP44XX_L4_WAKEUP_HWBASE + OMAP44XX_PRM_OFFSET)
#define OMAP44XX_PRM_VBASE				(OMAP44XX_L4_WAKEUP_VBASE + OMAP44XX_PRM_OFFSET)
#define OMAP44XX_PRM_SIZE				0x00001600UL

/*
 *
 */
#define OMAP44XX_SCRM_HWBASE            (OMAP44XX_L4_WAKEUP_HWBASE + OMAP44XX_SCRM_OFFSET)
#define OMAP44XX_SCRM_VBASE             (OMAP44XX_L4_WAKEUP_VBASE + OMAP44XX_SCRM_OFFSET)
#define OMAP44XX_SCRM_SIZE              0x00000800UL



/*
 * Uarts
 */
#define OMAP44XX_UART1_HWBASE			(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_UART1_OFFSET)
#define OMAP44XX_UART1_VBASE			(OMAP44XX_L4_CORE_VBASE  + OMAP44XX_UART1_OFFSET)
#define OMAP44XX_UART1_SIZE				0x00001000UL
#define OMAP44XX_UART2_HWBASE			(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_UART2_OFFSET)
#define OMAP44XX_UART2_VBASE			(OMAP44XX_L4_CORE_VBASE  + OMAP44XX_UART2_OFFSET)
#define OMAP44XX_UART2_SIZE				0x00001000UL
#define OMAP44XX_UART3_HWBASE			(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_UART3_OFFSET)
#define OMAP44XX_UART3_VBASE			(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_UART3_OFFSET)
#define OMAP44XX_UART3_SIZE				0x00001000UL
#define OMAP44XX_UART4_HWBASE			(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_UART4_OFFSET)
#define OMAP44XX_UART4_VBASE			(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_UART4_OFFSET)
#define OMAP44XX_UART4_SIZE				0x00001000UL




/*
 * I2C Modules
 */
#define OMAP44XX_I2C1_HWBASE			(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_I2C1_OFFSET)
#define OMAP44XX_I2C1_VBASE				(OMAP44XX_L4_CORE_VBASE  + OMAP44XX_I2C1_OFFSET)
#define OMAP44XX_I2C1_SIZE				0x00000080UL
#define OMAP44XX_I2C2_HWBASE			(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_I2C2_OFFSET)
#define OMAP44XX_I2C2_VBASE				(OMAP44XX_L4_CORE_VBASE  + OMAP44XX_I2C2_OFFSET)
#define OMAP44XX_I2C2_SIZE				0x00000080UL
#define OMAP44XX_I2C3_HWBASE			(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_I2C3_OFFSET)
#define OMAP44XX_I2C3_VBASE				(OMAP44XX_L4_CORE_VBASE  + OMAP44XX_I2C3_OFFSET)
#define OMAP44XX_I2C3_SIZE				0x00000080UL



/*
 * McBSP Modules
 */
#define OMAP44XX_MCBSP1_HWBASE			(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_MCBSP1_OFFSET)
#define OMAP44XX_MCBSP1_VBASE			(OMAP44XX_L4_CORE_VBASE  + OMAP44XX_MCBSP1_OFFSET)
#define OMAP44XX_MCBSP1_SIZE			0x00001000UL
#define OMAP44XX_MCBSP2_HWBASE			(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_MCBSP2_OFFSET)
#define OMAP44XX_MCBSP2_VBASE			(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_MCBSP2_OFFSET)
#define OMAP44XX_MCBSP2_SIZE			0x00001000UL
#define OMAP44XX_MCBSP3_HWBASE			(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_MCBSP3_OFFSET)
#define OMAP44XX_MCBSP3_VBASE			(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_MCBSP3_OFFSET)
#define OMAP44XX_MCBSP3_SIZE			0x00001000UL
#define OMAP44XX_MCBSP4_HWBASE			(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_MCBSP4_OFFSET)
#define OMAP44XX_MCBSP4_VBASE			(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_MCBSP4_OFFSET)
#define OMAP44XX_MCBSP4_SIZE			0x00001000UL
#define OMAP44XX_MCBSP5_HWBASE			(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_MCBSP5_OFFSET)
#define OMAP44XX_MCBSP5_VBASE			(OMAP44XX_L4_CORE_VBASE  + OMAP44XX_MCBSP5_OFFSET)
#define OMAP44XX_MCBSP5_SIZE			0x00001000UL



/*
 * USB TTL Module
 */
#define OMAP44XX_USB_TLL_HWBASE         (OMAP44XX_L4_CORE_HWBASE + OMAP44XX_USB_TLL_OFFSET)
#define OMAP44XX_USB_TLL_VBASE          (OMAP44XX_L4_CORE_VBASE  + OMAP44XX_USB_TLL_OFFSET)
#define OMAP44XX_USB_TLL_SIZE           0x00001000UL

/*
 * USB Host Module
 */
#define OMAP44XX_USB_UHH_HWBASE         (OMAP44XX_L4_CORE_HWBASE + OMAP44XX_USB_UHH_OFFSET)
#define OMAP44XX_USB_UHH_VBASE          (OMAP44XX_L4_CORE_VBASE  + OMAP44XX_USB_UHH_OFFSET)
#define OMAP44XX_USB_UHH_SIZE           0x00000700UL

/*
 * USB OHCI Module
 */
#define OMAP44XX_USB_OHCI_HWBASE        (OMAP44XX_L4_CORE_HWBASE + OMAP44XX_USB_OHCI_OFFSET)
#define OMAP44XX_USB_OHCI_VBASE         (OMAP44XX_L4_CORE_VBASE  + OMAP44XX_USB_OHCI_OFFSET)
#define OMAP44XX_USB_OHCI_SIZE          0x00000400UL

/*
 * USB EHCI Module
 */
#define OMAP44XX_USB_EHCI_HWBASE        (OMAP44XX_L4_CORE_HWBASE + OMAP44XX_USB_EHCI_OFFSET)
#define OMAP44XX_USB_EHCI_VBASE         (OMAP44XX_L4_CORE_VBASE  + OMAP44XX_USB_EHCI_OFFSET)
#define OMAP44XX_USB_EHCI_SIZE          0x0000400UL





/*
 * SDMA Offset
 *  PA 0x4805 6000
 */

#define OMAP44XX_SDMA_HWBASE			(OMAP44XX_L4_CORE_HWBASE + OMAP44XX_SDMA_OFFSET)
#define OMAP44XX_SDMA_VBASE				(OMAP44XX_L4_CORE_VBASE  + OMAP44XX_SDMA_OFFSET)
#define OMAP44XX_SDMA_SIZE				0x00001000UL



/*
 * Interrupt Controller Unit.
 *
 *    Refer to the omap4_intr.c file for interrupt controller (GIC)
 *    implementation.
 *
 *    Note:
 *    - 16 Interprocessor interrupts (IPI): ID[15:0]
 *    - 2 private Timer/Watchdog interrupts: ID[30:29]
 *    - 2 legacy nFIQ & nIRQ: one per CPU, bypasses the interrupt distributor
 *      logic and directly drives interrupt requests into CPU if used in
 *      legacy mode (else treated like other interrupts lines with ID28
 *      and ID31 respectively)
 *    - 128 hardware interrupts: ID[159:32] (rising-edge or high-level sensitive).
 */
#define OMAP44XX_HARDIRQ(x)         (32 + (x))

#define OMAP44XX_IRQ_L2CACHE        OMAP44XX_HARDIRQ(0)     /* L2 cache controller interrupt */
#define OMAP44XX_IRQ_CTI_0          OMAP44XX_HARDIRQ(1)     /* Cross-trigger module 0 (CTI0) interrupt */
#define OMAP44XX_IRQ_CTI_1          OMAP44XX_HARDIRQ(2)     /* Cross-trigger module 1 (CTI1) interrupt */
#define OMAP44XX_IRQ_RESERVED3      OMAP44XX_HARDIRQ(3)     /* RESERVED */
#define OMAP44XX_IRQ_ELM            OMAP44XX_HARDIRQ(4)     /* Error location process completion */
#define OMAP44XX_IRQ_RESERVED5      OMAP44XX_HARDIRQ(5)     /* RESERVED */
#define OMAP44XX_IRQ_RESERVED6      OMAP44XX_HARDIRQ(6)     /* RESERVED */
#define OMAP44XX_IRQ_SYS_NIRQ       OMAP44XX_HARDIRQ(7)     /* External source (active low) */
#define OMAP44XX_IRQ_RESERVED8      OMAP44XX_HARDIRQ(8)     /* RESERVED */
#define OMAP44XX_IRQ_L3_DBG         OMAP44XX_HARDIRQ(9)     /* L3 interconnect debug error */
#define OMAP44XX_IRQ_L3_APP         OMAP44XX_HARDIRQ(10)    /* L3 interconnect application error */
#define OMAP44XX_IRQ_PRCM_MPU       OMAP44XX_HARDIRQ(11)    /* PRCM module IRQ */
#define OMAP44XX_IRQ_SDMA0          OMAP44XX_HARDIRQ(12)    /* System DMA request 0(3) */
#define OMAP44XX_IRQ_SDMA1          OMAP44XX_HARDIRQ(13)    /* System DMA request 1(3) */
#define OMAP44XX_IRQ_SDMA2          OMAP44XX_HARDIRQ(14)    /* System DMA request 2 */
#define OMAP44XX_IRQ_SDMA3          OMAP44XX_HARDIRQ(15)    /* System DMA request 3 */
#define OMAP44XX_IRQ_MCBSP4         OMAP44XX_HARDIRQ(16)    /* McBSP module 4 IRQ */
#define OMAP44XX_IRQ_MCBSP1         OMAP44XX_HARDIRQ(17)    /* McBSP module 1 IRQ */
#define OMAP44XX_IRQ_SR1            OMAP44XX_HARDIRQ(18)    /* SmartReflex™ 1 */
#define OMAP44XX_IRQ_SR2            OMAP44XX_HARDIRQ(19)    /* SmartReflex™ 2 */
#define OMAP44XX_IRQ_GPMC           OMAP44XX_HARDIRQ(20)    /* General-purpose memory controller module */
#define OMAP44XX_IRQ_SGX            OMAP44XX_HARDIRQ(21)    /* 2D/3D graphics module */
#define OMAP44XX_IRQ_MCBSP2         OMAP44XX_HARDIRQ(22)    /* McBSP module 2 */
#define OMAP44XX_IRQ_MCBSP3         OMAP44XX_HARDIRQ(23)    /* McBSP module 3 */
#define OMAP44XX_IRQ_ISS5           OMAP44XX_HARDIRQ(24)    /* Imaging subsystem interrupt 5 */
#define OMAP44XX_IRQ_DSS            OMAP44XX_HARDIRQ(25)    /* Display subsystem module(3) */
#define OMAP44XX_IRQ_MAIL_U0        OMAP44XX_HARDIRQ(26)    /* Mailbox user 0 request */
#define OMAP44XX_IRQ_C2C_SSCM       OMAP44XX_HARDIRQ(27)    /* C2C status interrupt */
#define OMAP44XX_IRQ_DSP_MMU        OMAP44XX_HARDIRQ(28)    /* DSP MMU */
#define OMAP44XX_IRQ_GPIO1_MPU      OMAP44XX_HARDIRQ(29)    /* GPIO module 1(3) */
#define OMAP44XX_IRQ_GPIO2_MPU      OMAP44XX_HARDIRQ(30)    /* GPIO module 2(3) */
#define OMAP44XX_IRQ_GPIO3_MPU      OMAP44XX_HARDIRQ(31)    /* GPIO module 3(3) */
#define OMAP44XX_IRQ_GPIO4_MPU      OMAP44XX_HARDIRQ(32)    /* GPIO module 4(3) */
#define OMAP44XX_IRQ_GPIO5_MPU      OMAP44XX_HARDIRQ(33)    /* GPIO module 5(3) */
#define OMAP44XX_IRQ_GPIO6_MPU      OMAP44XX_HARDIRQ(34)    /* GPIO module 6(3) */
#define OMAP44XX_IRQ_RESERVED35     OMAP44XX_HARDIRQ(35)    /* RESERVED */
#define OMAP44XX_IRQ_WDT3           OMAP44XX_HARDIRQ(36)    /* Watchdog timer module 3 overflow */
#define OMAP44XX_IRQ_GPT1           OMAP44XX_HARDIRQ(37)    /* General-purpose timer module 1 */
#define OMAP44XX_IRQ_GPT2           OMAP44XX_HARDIRQ(38)    /* General-purpose timer module 2 */
#define OMAP44XX_IRQ_GPT3           OMAP44XX_HARDIRQ(39)    /* General-purpose timer module 3 */
#define OMAP44XX_IRQ_GPT4           OMAP44XX_HARDIRQ(40)    /* General-purpose timer module 4 */
#define OMAP44XX_IRQ_GPT5           OMAP44XX_HARDIRQ(41)    /* General-purpose timer module 5 */
#define OMAP44XX_IRQ_GPT6           OMAP44XX_HARDIRQ(42)    /* General-purpose timer module 6 */
#define OMAP44XX_IRQ_GPT7           OMAP44XX_HARDIRQ(43)    /* General-purpose timer module 7 */
#define OMAP44XX_IRQ_GPT8           OMAP44XX_HARDIRQ(44)    /* General-purpose timer module 8 */
#define OMAP44XX_IRQ_GPT9           OMAP44XX_HARDIRQ(45)    /* General-purpose timer module 9 */
#define OMAP44XX_IRQ_GPT10          OMAP44XX_HARDIRQ(46)    /* General-purpose timer module 10 */
#define OMAP44XX_IRQ_GPT11          OMAP44XX_HARDIRQ(47)    /* General-purpose timer module 11 */
#define OMAP44XX_IRQ_MCSPI4         OMAP44XX_HARDIRQ(48)    /* McSPI module 4 */
#define OMAP44XX_IRQ_RESERVED49     OMAP44XX_HARDIRQ(49)    /* RESERVED */
#define OMAP44XX_IRQ_RESERVED50     OMAP44XX_HARDIRQ(50)    /* RESERVED */
#define OMAP44XX_IRQ_RESERVED51     OMAP44XX_HARDIRQ(51)    /* RESERVED */
#define OMAP44XX_IRQ_RESERVED52     OMAP44XX_HARDIRQ(52)    /* RESERVED */
#define OMAP44XX_IRQ_DSS_DSI1       OMAP44XX_HARDIRQ(53)    /* Display Subsystem DSI1 interrupt */
#define OMAP44XX_IRQ_RESERVED54     OMAP44XX_HARDIRQ(54)    /* RESERVED */
#define OMAP44XX_IRQ_RESERVED55     OMAP44XX_HARDIRQ(55)    /* RESERVED */
#define OMAP44XX_IRQ_I2C1           OMAP44XX_HARDIRQ(56)    /* I2C module 1 */
#define OMAP44XX_IRQ_I2C2           OMAP44XX_HARDIRQ(57)    /* I2C module 2 */
#define OMAP44XX_IRQ_HDQ            OMAP44XX_HARDIRQ(58)    /* HDQ / One-wire */
#define OMAP44XX_IRQ_MMC5           OMAP44XX_HARDIRQ(59)    /* MMC5 interrupt */
#define OMAP44XX_IRQ_RESERVED60     OMAP44XX_HARDIRQ(60)    /* RESERVED */
#define OMAP44XX_IRQ_I2C3           OMAP44XX_HARDIRQ(61)    /* I2C module 3 */
#define OMAP44XX_IRQ_I2C4           OMAP44XX_HARDIRQ(62)    /* I2C module 4 */
#define OMAP44XX_IRQ_RESERVED63     OMAP44XX_HARDIRQ(63)    /* RESERVED */
#define OMAP44XX_IRQ_RESERVED64     OMAP44XX_HARDIRQ(64)    /* RESERVED */
#define OMAP44XX_IRQ_MCSPI1         OMAP44XX_HARDIRQ(65)    /* McSPI module 1 */
#define OMAP44XX_IRQ_MCSPI2         OMAP44XX_HARDIRQ(66)    /* McSPI module 2 */
#define OMAP44XX_IRQ_HSI_P1         OMAP44XX_HARDIRQ(67)    /* HSI Port 1 interrupt */
#define OMAP44XX_IRQ_HSI_P2         OMAP44XX_HARDIRQ(68)    /* HSI Port 2 interrupt */
#define OMAP44XX_IRQ_FDIF_3         OMAP44XX_HARDIRQ(69)    /* Face detect interrupt 3 */
#define OMAP44XX_IRQ_UART4          OMAP44XX_HARDIRQ(70)    /* UART module 4 interrupt */
#define OMAP44XX_IRQ_HSI_DMA        OMAP44XX_HARDIRQ(71)    /* HSI DMA engine MPU request */
#define OMAP44XX_IRQ_UART1          OMAP44XX_HARDIRQ(72)    /* UART module 1 */
#define OMAP44XX_IRQ_UART2          OMAP44XX_HARDIRQ(73)    /* UART module 2 */
#define OMAP44XX_IRQ_UART3          OMAP44XX_HARDIRQ(74)    /* UART module 3 (also infrared)(3) */
#define OMAP44XX_IRQ_PBIAS          OMAP44XX_HARDIRQ(75)    /* Merged interrupt for PBIASlite1 and 2 */
#define OMAP44XX_IRQ_OHCI           OMAP44XX_HARDIRQ(76)    /* OHCI controller HSUSB MP Host Interrupt */
#define OMAP44XX_IRQ_EHCI           OMAP44XX_HARDIRQ(77)    /* EHCI controller HSUSB MP Host Interrupt */
#define OMAP44XX_IRQ_TLL            OMAP44XX_HARDIRQ(78)    /* HSUSB MP TLL Interrupt */
#define OMAP44XX_IRQ_RESERVED79     OMAP44XX_HARDIRQ(79)    /* RESERVED */
#define OMAP44XX_IRQ_WDT2           OMAP44XX_HARDIRQ(80)    /* WDTIMER2 interrupt */
#define OMAP44XX_IRQ_RESERVED81     OMAP44XX_HARDIRQ(81)    /* RESERVED */
#define OMAP44XX_IRQ_RESERVED82     OMAP44XX_HARDIRQ(82)    /* RESERVED */
#define OMAP44XX_IRQ_MMC1           OMAP44XX_HARDIRQ(83)    /* MMC/SD module 1 */
#define OMAP44XX_IRQ_DSS_DSI2       OMAP44XX_HARDIRQ(84)    /* Display subsystem DSI2 interrupt */
#define OMAP44XX_IRQ_RESERVED85     OMAP44XX_HARDIRQ(85)    /* Reserved */
#define OMAP44XX_IRQ_MMC2           OMAP44XX_HARDIRQ(86)    /* MMC/SD module 2 */
#define OMAP44XX_IRQ_MPU_ICR        OMAP44XX_HARDIRQ(87)    /* MPU ICR */
#define OMAP44XX_IRQ_C2C_GPI        OMAP44XX_HARDIRQ(88)    /* C2C GPI interrupt */
#define OMAP44XX_IRQ_FSUSB          OMAP44XX_HARDIRQ(89)    /* FS-USB - host controller Interrupt */
#define OMAP44XX_IRQ_FSUSB_SMI      OMAP44XX_HARDIRQ(90)    /* FS-USB - host controller SMI Interrupt */
#define OMAP44XX_IRQ_MCSPI3         OMAP44XX_HARDIRQ(91)    /* McSPI module 3 */
#define OMAP44XX_IRQ_HSUSB_OTG      OMAP44XX_HARDIRQ(92)    /* High-Speed USB OTG controller */
#define OMAP44XX_IRQ_HSUSB_OTG_DMA  OMAP44XX_HARDIRQ(93)    /* High-Speed USB OTG DMA controller */
#define OMAP44XX_IRQ_MMC3           OMAP44XX_HARDIRQ(94)    /* MMC/SD module 3 */
#define OMAP44XX_IRQ_RESERVED95     OMAP44XX_HARDIRQ(95)    /* RESERVED */
#define OMAP44XX_IRQ_MMC4           OMAP44XX_HARDIRQ(96)    /* MMC4 interrupt */
#define OMAP44XX_IRQ_SLIMBUS1       OMAP44XX_HARDIRQ(97)    /* SLIMBUS1 interrupt */
#define OMAP44XX_IRQ_SLIMBUS2       OMAP44XX_HARDIRQ(98)    /* SLIMBUS2 interrupt */
#define OMAP44XX_IRQ_ABE            OMAP44XX_HARDIRQ(99)    /* Audio back-end interrupt */
#define OMAP44XX_IRQ_CORTEXM3_MMU   OMAP44XX_HARDIRQ(100)   /* Cortex-M3 MMU interrupt */
#define OMAP44XX_IRQ_DSS_HDMI       OMAP44XX_HARDIRQ(101)   /* Display subsystem HDMI interrupt */
#define OMAP44XX_IRQ_SR_IVA         OMAP44XX_HARDIRQ(102)   /* SmartReflex IVA interrupt */
#define OMAP44XX_IRQ_IVAHD1         OMAP44XX_HARDIRQ(103)   /* Sync interrupt from iCONT2 (vDMA) */
#define OMAP44XX_IRQ_IVAHD2         OMAP44XX_HARDIRQ(104)   /* Sync interrupt from iCONT1 */
#define OMAP44XX_IRQ_RESERVED105    OMAP44XX_HARDIRQ(105)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED106    OMAP44XX_HARDIRQ(106)   /* RESERVED */
#define OMAP44XX_IRQ_IVAHD_MAILBOX0 OMAP44XX_HARDIRQ(107)   /* IVAHD mailbox interrupt */
#define OMAP44XX_IRQ_RESERVED108    OMAP44XX_HARDIRQ(108)   /* RESERVED */
#define OMAP44XX_IRQ_MCASP1         OMAP44XX_HARDIRQ(109)   /* McASP1 transmit interrupt */
#define OMAP44XX_IRQ_EMIF1          OMAP44XX_HARDIRQ(110)   /* EMIF1 interrupt */
#define OMAP44XX_IRQ_EMIF2          OMAP44XX_HARDIRQ(111)   /* EMIF2 interrupt */
#define OMAP44XX_IRQ_MCPDM          OMAP44XX_HARDIRQ(112)   /* MCPDM interrupt */
#define OMAP44XX_IRQ_DMM            OMAP44XX_HARDIRQ(113)   /* DMM interrupt */
#define OMAP44XX_IRQ_DMIC           OMAP44XX_HARDIRQ(114)   /* DMIC interrupt */
#define OMAP44XX_IRQ_RESERVED115    OMAP44XX_HARDIRQ(115)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED116    OMAP44XX_HARDIRQ(116)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED117    OMAP44XX_HARDIRQ(117)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED118    OMAP44XX_HARDIRQ(118)   /* RESERVED */
#define OMAP44XX_IRQ_SYS_NIRQ2      OMAP44XX_HARDIRQ(119)   /* External source 2 (active low) */
#define OMAP44XX_IRQ_KBD            OMAP44XX_HARDIRQ(120)   /* Keyboard controller interrupt */
#define OMAP44XX_IRQ_RESERVED121    OMAP44XX_HARDIRQ(121)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED122    OMAP44XX_HARDIRQ(122)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED123    OMAP44XX_HARDIRQ(123)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED124    OMAP44XX_HARDIRQ(124)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED125    OMAP44XX_HARDIRQ(125)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED126    OMAP44XX_HARDIRQ(126)   /* RESERVED */
#define OMAP44XX_IRQ_RESERVED127    OMAP44XX_HARDIRQ(127)   /* RESERVED */



/*
 * General Purpose Timers
 */
#define OMAP44XX_GPTIMER1_VBASE		(OMAP44XX_L4_WAKEUP_VBASE + OMAP44XX_GPTIMER1_OFFSET)
#define OMAP44XX_GPTIMER1_HWBASE	(OMAP44XX_L4_WAKEUP_HWBASE + OMAP44XX_GPTIMER1_OFFSET)
#define OMAP44XX_GPTIMER2_VBASE		(OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_GPTIMER2_OFFSET)
#define OMAP44XX_GPTIMER2_HWBASE	(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPTIMER2_OFFSET)
#define OMAP44XX_GPTIMER3_VBASE		(OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_GPTIMER3_OFFSET)
#define OMAP44XX_GPTIMER3_HWBASE	(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPTIMER3_OFFSET)
#define OMAP44XX_GPTIMER4_VBASE		(OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_GPTIMER4_OFFSET)
#define OMAP44XX_GPTIMER4_HWBASE	(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPTIMER4_OFFSET)
#define OMAP44XX_GPTIMER5_VBASE		(OMAP44XX_L4_ABE_VBASE + OMAP44XX_GPTIMER5_OFFSET)
#define OMAP44XX_GPTIMER5_HWBASE	(OMAP44XX_L4_ABE_HWBASE + OMAP44XX_GPTIMER5_OFFSET)
#define OMAP44XX_GPTIMER6_VBASE		(OMAP44XX_L4_ABE_VBASE + OMAP44XX_GPTIMER6_OFFSET)
#define OMAP44XX_GPTIMER6_HWBASE	(OMAP44XX_L4_ABE_HWBASE + OMAP44XX_GPTIMER6_OFFSET)
#define OMAP44XX_GPTIMER7_VBASE		(OMAP44XX_L4_ABE_VBASE + OMAP44XX_GPTIMER7_OFFSET)
#define OMAP44XX_GPTIMER7_HWBASE	(OMAP44XX_L4_ABE_HWBASE + OMAP44XX_GPTIMER7_OFFSET)
#define OMAP44XX_GPTIMER8_VBASE		(OMAP44XX_L4_ABE_VBASE + OMAP44XX_GPTIMER8_OFFSET)
#define OMAP44XX_GPTIMER8_HWBASE	(OMAP44XX_L4_ABE_HWBASE + OMAP44XX_GPTIMER8_OFFSET)
#define OMAP44XX_GPTIMER9_VBASE		(OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_GPTIMER9_OFFSET)
#define OMAP44XX_GPTIMER9_HWBASE    (OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPTIMER9_OFFSET)
#define OMAP44XX_GPTIMER10_VBASE	(OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_GPTIMER10_OFFSET)
#define OMAP44XX_GPTIMER10_HWBASE	(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPTIMER10_OFFSET)
#define OMAP44XX_GPTIMER11_VBASE	(OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_GPTIMER11_OFFSET)
#define OMAP44XX_GPTIMER11_HWBASE	(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPTIMER11_OFFSET)
#define OMAP44XX_GPTIMER_SIZE		0x00001000UL



/*
 * GPIO - General Purpose IO
 */

/* Base addresses for the GPIO modules */
#define OMAP44XX_GPIO1_HWBASE		(OMAP44XX_L4_WAKEUP_HWBASE + OMAP44XX_GPIO1_OFFSET)
#define OMAP44XX_GPIO1_VBASE		(OMAP44XX_L4_WAKEUP_VBASE  + OMAP44XX_GPIO1_OFFSET)
#define OMAP44XX_GPIO1_SIZE			0x00001000UL
#define OMAP44XX_GPIO2_HWBASE		(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPIO2_OFFSET)
#define OMAP44XX_GPIO2_VBASE		(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_GPIO2_OFFSET)
#define OMAP44XX_GPIO2_SIZE			0x00001000UL
#define OMAP44XX_GPIO3_HWBASE		(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPIO3_OFFSET)
#define OMAP44XX_GPIO3_VBASE		(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_GPIO3_OFFSET)
#define OMAP44XX_GPIO3_SIZE			0x00001000UL
#define OMAP44XX_GPIO4_HWBASE		(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPIO4_OFFSET)
#define OMAP44XX_GPIO4_VBASE		(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_GPIO4_OFFSET)
#define OMAP44XX_GPIO4_SIZE			0x00001000UL
#define OMAP44XX_GPIO5_HWBASE		(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPIO5_OFFSET)
#define OMAP44XX_GPIO5_VBASE		(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_GPIO5_OFFSET)
#define OMAP44XX_GPIO5_SIZE			0x00001000UL
#define OMAP44XX_GPIO6_HWBASE		(OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_GPIO6_OFFSET)
#define OMAP44XX_GPIO6_VBASE		(OMAP44XX_L4_PERIPH_VBASE  + OMAP44XX_GPIO6_OFFSET)
#define OMAP44XX_GPIO6_SIZE			0x00001000UL


/*
 * MMC/SD/SDIO
 */

/* Base addresses for the MMC/SD/SDIO modules */
#define OMAP44XX_MMCHS1_HWBASE   (OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_MMCHS1_OFFSET)
#define OMAP44XX_MMCHS1_VBASE    (OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_MMCHS1_OFFSET)
#define OMAP44XX_MMCHS2_HWBASE   (OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_MMCHS2_OFFSET)
#define OMAP44XX_MMCHS2_VBASE    (OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_MMCHS2_OFFSET)
#define OMAP44XX_MMCHS3_HWBASE   (OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_MMCSD3_OFFSET)
#define OMAP44XX_MMCHS3_VBASE    (OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_MMCSD3_OFFSET)
#define OMAP44XX_MMCHS4_HWBASE   (OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_MMCSD4_OFFSET)
#define OMAP44XX_MMCHS4_VBASE    (OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_MMCSD4_OFFSET)
#define OMAP44XX_MMCHS5_HWBASE   (OMAP44XX_L4_PERIPH_HWBASE + OMAP44XX_MMCSD5_OFFSET)
#define OMAP44XX_MMCHS5_VBASE    (OMAP44XX_L4_PERIPH_VBASE + OMAP44XX_MMCSD5_OFFSET)
#define OMAP44XX_MMCHS_SIZE      0x00001000UL



/*
 * SCM - System Control Module
 */

/* Base addresses for the SC modules */
#define OMAP44XX_SCM_PADCONF_HWBASE (OMAP44XX_L4_CORE_HWBASE + OMAP44XX_SCM_PADCONF_OFFSET)
#define OMAP44XX_SCM_PADCONF_VBASE  (OMAP44XX_L4_CORE_VBASE + OMAP44XX_SCM_PADCONF_OFFSET)
#define OMAP44XX_SCM_PADCONF_SIZE   0x00001000UL




#endif /* _OMAP44XX_REG_H_ */
