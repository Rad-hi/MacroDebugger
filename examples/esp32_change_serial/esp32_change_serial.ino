#define ENABLE_DEBUG /* <-- Commenting this line will remove any trace of debug printing */

/* 
 * In order to use a Serial port different than the default one (Serial), 
 * these three macros need to be defined (BEFORE THE LIBRARY IS INCLUDED)
 */
#define DEBUG_SERIAL_PORT     Serial2       /* Optional - Default::Serial */
#define DEBUG_RX_PIN          SER_2_PIN_RX  /* Optional - Default::SER_0_PIN_RX */
#define DEBUG_TX_PIN          SER_2_PIN_TX  /* Optional - Default::SER_0_PIN_TX */

//#define DEBUG_SER_BAUD_RATE   9600          /* Optional - Default::115200 */

#include <MacroDebugger.h>

#define TAB_SIZE   25
char buf[TAB_SIZE] = {0};

void setup() {
  /* Begin the Serial connection  */
  DEBUG_BEGIN();
}

void loop() {
  /* This warning will print every 1s */
  DEBUG_W("WTF %d_0, %s", 0, "a string!");

  /* If you want to interrupt the printing of the above WARNING, 
   * enter something to the Serial monitor (end it with '>', 
   * anything written after the '>' will not be filled into the buffer) 
   */
  if(DEBUG_AVAILABLE()){
    
    DEBUG_FILL_UNTIL(buf, '>');

    /* Print the whole table */
    for(uint8_t i = 0; i < TAB_SIZE; i++)
      DEBUG("%c", buf[i]);

    /* Print a newline */
    DEBUG_ENDL();

    /* Empty the Serial buffer */
    DEBUG_FLUSH();

    DEBUG_I("Done printing the table %s", ";)");
  }
  
  delay(1000);
}
