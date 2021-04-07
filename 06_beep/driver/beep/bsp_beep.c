#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

void beep_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10B0);

    GPIO5->GDIR |= (0x1 << 1);
    GPIO5->DR |= (0x1 << 1);
}

void beep_set_status(bool status)
{
    if (status == TRUE) {
        GPIO5->DR &= ~(0x1 << 1);
    } else {
        GPIO5->DR |= (0x1 << 1);
    }
}