#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "bme280.h"




static int slaveAddr = 0x77;

void sensorInit(void){
	//First checks if sensor is connected and 
	sleep_ms(1000);
	uint8_t reg = 0x00;
	uint8_t chipID[1];
	i2c_write_blocking(i2c0, slaveAddr, &reg, 1, true);
	i2c_read_blocking(i2c0, slaveAddr, chipID, 1, false);

	if(chipID[0] != 0x60){
		while(1){
			printf("Slave Unresponsive!");
			sleep_ms(5000);
		}
	}



}



int main(){
	//Initializes Serial and i2c
	stdio_init_all();
	i2c_init(i2c0, 152000);
	



	//Initializes Pins and arrays
	gpio_set_function(4, GPIO_FUNC_I2C); // SDA
	gpio_set_function(5, GPIO_FUNC_I2C); // SCL
	gpio_pull_up(4);
	gpio_pull_up(5);




	//Initializes the Sensor
	sensorInit();

	uint8_t buf[] = {slaveAddr}; // 0xE7 is just an example
	//0x77 is the default address. However, if SDO is connected to GND, or soldering the ADDR jumper closed,
	//0x76 is the new address
	
	//Writing
	i2c_write_blocking(i2c0, 0x40, buf, 1, false);
	
	//Reading
	i2c_read_blocking(i2c0, 0x40, buf, 1, false);

	printf("User Register = %X \r\n", buf[0]);


    

}




#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "bme280.h"


uint BUFFER_LEN = 8;
static int slaveAddr = 0x77;


void sensorInit(void){
    //First checks if sensor is connected and 
    sleep_ms(1000);
    uint8_t reg = 0x00;
    uint8_t chipID[1];
    i2c_write_blocking(i2c0, slaveAddr, &reg, 1, true);
    i2c_read_blocking(i2c0, slaveAddr, chipID, 1, false);

    if(chipID[0] != 0x60){
        while(1){
            printf("Slave Unresponsive!");
            sleep_ms(5000);
        }
    }



}



signed char BME280_I2C_read(unsigned char slave_addy, unsigned char reg_addy, 
    unsigned chardata, unsigned char cnt){
        int err = 0;
        unsigned char array[BUFFER_LEN];
        unsigned char stringpos;
        array[0] = reg_addy;
        err = i2c_read_blocking(i2c0, slaveAddr, array, 1, cnt);
        for(stringpos=0;stringpos<cnt;stringpos++){
            *(data+stringpos)=array[stringpos];
        }
        return (signed char)err;
}



int main(){
    //Initializes Serial and i2c
    bme280.bus_read = BME280_I2C_read;
    stdio_init_all();
    i2c_init(i2c0, 152000);
    int readings[3];



    //Initializes Pins and arrays
    gpio_set_function(4, GPIO_FUNC_I2C); // SDA
    gpio_set_function(5, GPIO_FUNC_I2C); // SCL
    gpio_pull_up(4);
    gpio_pull_up(5);






    uint8_t buf[] = {0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE};
    //It is used a placeholder that exchanges both data and data register.

    //Writing
    i2c_write_blocking(i2c0, slaveAddr, buf , 8, false);

    //Reading
    i2c_read_blocking(i2c0, slaveAddr, buf, 8, false);

    for(int i = 0; i <= 8; i++){
        printf("User Register = %X \r\n", buf[i]);
    }






} 
