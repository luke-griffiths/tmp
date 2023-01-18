#include <plib.h>

//use only BIT_x, not the actual x number. otherwise it won't work
//DEFINES :: if something is wrong, it's probably here
#define CONFIG1 I2C_ON | I2C_IDLE_CON | I2C_7BIT_ADD | I2C_SLW_EN | I2C_SM_DIS | I2C_ACK | \
  I2C_ACK_EN | I2C_RCV_EN | I2C_STOP_EN | I2C_RESTART_EN | I2C_START_EN
#define BRG (800000000 / 2 / 400000) - 2 //Fpb is CPU clk divided by 2?
#define SLAVE 0x00h
#define ABSOLUTE_POS_REG 0x21
#define TACHO_REG 0x23 
//functions

//i2c_init
void i2c_init() {
  OpenI2C1(CONFIG1, BRG);
}

//i2c_reset
//i2c_write_eeprom
//i2c_read_reg
uint16_t i2c_read_reg(char register) {
  uint8_t msb;
  uint8_t lsb;
  StartI2C1(); //generates a start condition
  IdleI2C1(); //waits for the bus to settle
  MasterWriteI2C1((SLAVE << 1) | 0); //this writes a byte. SLAVE address is 7 bits, the 0 signals a write
  IdleI2C1();
  MasterWriteI2C1(register);
  IdleI2C1();
  RestartI2C1(); //I guess this is SR? Might need to fix
  IdleI2C1();
  MasterWriteI2C1((SLAVE << 1) | 1); //this writes a byte. SLAVE address is 7 bits, the 1 signals a read
  IdleI2C1();
  msb = MasterReadI2C1();
  IdleI2C1();
  lsb = MasterReadI2C1();
  IdleI2C1();
  StopI2C1();
  //I don't think we  need an Idle here
  short output = (msb << 8) | (lsb & 0xff);
  return output;

}
//i2c_shutdown


//MastergetsI2C1(length, rdptr, i2c_data_wait); page 217 to get data from encoder
//OpenI2C1(unsigned int config1, unsigned int brg); this configures/starts i2c

void init_i2c() {

}