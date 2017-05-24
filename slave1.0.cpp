#include "mbed.h"
#include "USBSerial.h"
//master
/*intからcharへの分解
   分解の際
   dat1 = data % 256;
   dat2 = data / 256;
   復元の際
   data = dat2 * 256 + dat1;
   参考元：https://oshiete.goo.ne.jp/qa/6219385.html
 */
USBSerial pc;
Timer timer;
struct {
        char highbyte;
        char lowbyte;
        short intdat;
} data;

SPISlave device(D11, D12, D13, D10); // mosi, miso, sclk, ssel

int main() {

        int counter = 1;
        device.format(8,3);    // Setup:  bit data, high steady state clock, 2nd edge capture
        device.frequency(16000000); // 1MHz

        int reply = 99;
        device.reply(reply);          // Prime SPI with first reply
        device.reply(reply);          // Prime SPI with first reply, again

        pc.printf("======================================================\r\n");
        pc.printf("Startup Next reply will be %d\r\n", reply);

        while (1) {
                if (device.receive()) {
                        int valueFromMaster = device.read();
                        pc.printf("%d Something rxvd, and should have replied with %d\n\r", counter++, reply);
                        device.reply(++reply);  // Prime SPI with next reply
                        pc.printf("    Received value from Master (%d) Next reply will be %d \r\n", valueFromMaster, reply);
                }
        }
}
