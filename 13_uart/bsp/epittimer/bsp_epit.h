#ifndef __EPIT_H__
#define __EPIT_H__

#include "imx6ul.h"
/** @
 *  初始化epit 
 *  分频值
 *  比较值
 */
void epit_init(unsigned int frac, unsigned int value);
void epit1_irqhandler(unsigned int giccIar, void *param);

#endif // !__EPIT_H__