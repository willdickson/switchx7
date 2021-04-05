#include <Streaming.h>
#include "serial_receiver.h"

const uint8_t NumPin = 7;
const uint8_t Pin[NumPin] = {0,1,2,3,4,5,6};
const uint8_t PairPin[NumPin] = {10,11,12,13,14,18,19}; 

SerialReceiver receiver;

void handle_message(uint16_t cmd_num, uint16_t cmd_val);

void setup() {
    
    Serial.begin(115200);
    // Set SSR pins to output and set to low
    for (uint8_t i=0; i<NumPin; i++) {
        pinMode(Pin[i], OUTPUT);
        pinMode(PairPin[i], OUTPUT);
        digitalWrite(Pin[i],LOW);
        digitalWrite(PairPin[i],LOW);
    }
}

void loop() {
    uint16_t cmd_num;
    uint16_t cmd_val;
    
    while (Serial.available() > 0) {
        receiver.process(Serial.read());
        if (receiver.messageReady()) {
            cmd_num = receiver.readInt(0);
            cmd_val = receiver.readInt(1);
            handle_message(cmd_num,cmd_val);
            receiver.reset();
        }
    }
}

void handle_message(uint16_t cmd_num, uint16_t cmd_val) {
    if (cmd_num < 7) {
        if ((cmd_val==0) || (cmd_val==1)) {
            digitalWrite(Pin[cmd_num], cmd_val);
            digitalWrite(PairPin[cmd_num], cmd_val); // Hardcode for debugging purposes
        }
    }
    if (cmd_num == 7) {
        if ((cmd_val == 0 ) || (cmd_val==1)) {
            for (uint8_t i=0; i<NumPin; i++) {
                digitalWrite(Pin[i],cmd_val);
                digitalWrite(PairPin[i], cmd_val); // Hardcode for debugging purposes
            }
        }
    }
}
