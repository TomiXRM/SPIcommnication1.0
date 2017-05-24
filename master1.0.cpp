#include "mbed.h"
//https://developer.mbed.org/forum/helloworld/topic/2541/
/*intからcharへの分解
   分解の際
   dat1 = data % 256;
   dat2 = data / 256;
   復元の際
   data = dat2 * 256 + dat1;
   参考元：https://oshiete.goo.ne.jp/qa/6219385.html*/
#define spi_start 0x01
SPI spi(PC_12, PC_11, PC_10); // mosi, miso, sclk
DigitalOut chipSelect(D10);
Serial pc(USBTX, USBRX); // tx, rx
//DigitalOut LED(LED1);
int USF,USR,USL,USB;
int dataFromSlave;
int valueToSendToSlave;
int main() {

        int valueToSendToSlave = 20; // Starting value only, this increments
        spi.format(8,3);    // Setup:  bit data, high steady state clock, 2nd edge capture
        spi.frequency(16000000); //1MHz

        pc.printf("======================================================\r\n");
        pc.printf("Press any key to start...\r\n");
        pc.getc(); // wait for keyboard

        int counter = 1;
        while (1) {

                ///pc.printf("%d Value to send = %d ", counter++, valueToSendToSlave);

                chipSelect = 0; // Select device
                int dataFromSlave =  spi.write(valueToSendToSlave);
                chipSelect = 1; // Deselect device
                pc.printf("returns %d\r\n", dataFromSlave);
                valueToSendToSlave++;
                //wait_ms(100); // Wait for 5 seconds for readability only

        }
}
