//#define ENABLE_DEBUG

#define DEBUG_SERIAL_PORT   Serial2
#define DEBUG_RX_PIN        SER_2_PIN_RX
#define DEBUG_TX_PIN        SER_2_PIN_TX

#include "MacroDebugger.h"


#define TAB_SIZE   25
byte byte_buf[TAB_SIZE] = {0};
char char_buf[TAB_SIZE] = {0};

void setup() {
  DEBUG_BEGIN();
}

void loop() {
  DEBUG_W("WTF");

  if(DEBUG_AVAILABLE()){
    DEBUG_FILL_UNTIL(byte_buf, '>');
    for(uint8_t i = 0; i < TAB_SIZE; i++)
      DEBUG("%x|", byte_buf[i]);
    DEBUG_ENDL();

    DEBUG_FLUSH();
  }

  
  delay(1000);
}
