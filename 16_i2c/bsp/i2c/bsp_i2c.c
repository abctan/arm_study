#include "bsp_i2c.h"

void i2c_init(I2C_Type *base)
{
    base->I2CR &= ~(1 << 7); /* close i2c */
    base->IFDR = 0X15 << 0;
    base->I2CR |= (1<<7);
}

unsigned char i2c_master_start(I2C_Type *base, unsigned char address, enum i2c_direction direction)
{
    if ((base->I2SR >> 5) & 0x1) {
        return I2C_STATUS_BUSY;
    }
    base->I2CR |= (1 << 5) | (1 << 4);

    base->I2DR = ((unsigned int)address << 1) | ((direction == kI2C_Read)? 1 : 0);
    return I2C_STATUS_OK;
}

unsigned char i2c_master_stop(I2C_Type *base)
{
    unsigned short timeout = 0XFFFF;

    /* 清除 I2CR 的 bit[5:3]这三位 */
    base->I2CR &= ~((1 << 5) | (1 << 4) | (1 << 3));
    while((base->I2SR & (1 << 5))) /* 等待忙结束 */
    {
        timeout--;
        if (timeout == 0) {
            return I2C_STATUS_TIMEOUT;
        }
    }
    return I2C_STATUS_OK;
}

unsigned char i2c_master_repeated_start(I2C_Type *base, unsigned char address,  enum i2c_direction direction)
{
    if (((base->I2SR >> 5) & 0x1) && ((base->I2CR >> 5) & 0x1) == 0)
        return I2C_STATUS_BUSY;
    
    base->I2CR |= (1 << 4) | (1 << 2);
    base->I2DR = (address << 1) | ((direction == kI2C_Read) ? 1 : 0);
    return I2C_STATUS_OK;
}

unsigned char i2c_check_and_clear_error(I2C_Type *base, unsigned int status)
{
    if(status & (1<<4)) {
        base->I2SR &= ~(1<<4);
        base->I2CR &= ~(1 << 7); /* 先关闭 I2C */
        base->I2CR |= (1 << 7);
        return I2C_STATUS_ARBITRATIONLOST;
    } else if (status & (1 << 0)) {
        return I2C_STATUS_NAK; /* 返回 NAK(No acknowledge) */
    }
    return I2C_STATUS_OK;
}

void i2c_master_write(I2C_Type *base, const unsigned char *buf, unsigned int size)
{
    while (!(base->I2SR & (1 << 7)));
    base->I2SR &= ~(1 << 1);
    base->I2CR |= 1 << 4;

    while (size--) {
        base->I2DR = *buf++; /* 将 buf 中的数据写入到 I2DR 寄存器 */
        while(!(base->I2SR & (1 << 1)));
        base->I2SR &= ~(1 << 1);

        if(i2c_check_and_clear_error(base, base->I2SR) != I2C_STATUS_OK)
            break;
    }
    base->I2SR &= ~(1 << 1);
    i2c_master_stop(base);
}

void i2c_master_read(I2C_Type *base, unsigned char *buf, unsigned int size)
{
    volatile uint8_t dummy = 0;
    dummy++;

    while (!(base->I2SR & (1 << 7)));
    base->I2SR &= ~(1 << 1);
    base->I2CR &= ~((1 << 4) | (1 << 3)); /* 接收数据 */
    if(size == 1)
        base->I2CR |= (1 << 3);
    dummy = base->I2DR;

    while (size--) {
        while(!(base->I2SR & (1 << 1)));  /* 等待传输完成 */
        base->I2SR &= ~(1 << 1); /* 清除标志位 */

        if(size == 0)
            i2c_master_stop(base);
        if(size == 1)
            base->I2CR |= (1 << 3);
        *buf++ = base->I2DR;
    }
}
unsigned char i2c_master_transfer(I2C_Type *base, struct i2c_transfer *xfer)
{
	unsigned char ret = 0;
	 enum i2c_direction direction = xfer->direction;	

	base->I2SR &= ~((1 << 1) | (1 << 4));			/* 清除标志位 */

	/* 等待传输完成 */
	while(!((base->I2SR >> 7) & 0X1)){}; 

	/* 如果是读的话，要先发送寄存器地址，所以要先将方向改为写 */
    if ((xfer->subaddressSize > 0) && (xfer->direction == kI2C_Read))
    {
        direction = kI2C_Write;
    }

	ret = i2c_master_start(base, xfer->slaveAddress, direction); /* 发送开始信号 */
    if(ret)
    {	
		return ret;
	}

	while(!(base->I2SR & (1 << 1))){};			/* 等待传输完成 */

    ret = i2c_check_and_clear_error(base, base->I2SR);	/* 检查是否出现传输错误 */
    if(ret)
    {
      	i2c_master_stop(base); 						/* 发送出错，发送停止信号 */
        return ret;
    }
	
    /* 发送寄存器地址 */
    if(xfer->subaddressSize)
    {
        do
        {
			base->I2SR &= ~(1 << 1);			/* 清除标志位 */
            xfer->subaddressSize--;				/* 地址长度减一 */
			
            base->I2DR =  ((xfer->subaddress) >> (8 * xfer->subaddressSize)); //向I2DR寄存器写入子地址
  
			while(!(base->I2SR & (1 << 1)));  	/* 等待传输完成 */

            /* 检查是否有错误发生 */
            ret = i2c_check_and_clear_error(base, base->I2SR);
            if(ret)
            {
             	i2c_master_stop(base); 				/* 发送停止信号 */
             	return ret;
            }  
        } while ((xfer->subaddressSize > 0) && (ret == I2C_STATUS_OK));

        if(xfer->direction == kI2C_Read) 		/* 读取数据 */
        {
            base->I2SR &= ~(1 << 1);			/* 清除中断挂起位 */
            i2c_master_repeated_start(base, xfer->slaveAddress, kI2C_Read); /* 发送重复开始信号和从机地址 */
    		while(!(base->I2SR & (1 << 1))){};/* 等待传输完成 */

            /* 检查是否有错误发生 */
			ret = i2c_check_and_clear_error(base, base->I2SR);
            if(ret)
            {
             	ret = I2C_STATUS_ADDRNAK;
                i2c_master_stop(base); 		/* 发送停止信号 */
                return ret;  
            }
           	          
        }
    }	


    /* 发送数据 */
    if ((xfer->direction == kI2C_Write) && (xfer->dataSize > 0))
    {
    	i2c_master_write(base, xfer->data, xfer->dataSize);
	}

    /* 读取数据 */
    if ((xfer->direction == kI2C_Read) && (xfer->dataSize > 0))
    {
       	i2c_master_read(base, xfer->data, xfer->dataSize);
	}
	return 0;	
}
