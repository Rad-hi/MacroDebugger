#ifndef __MACRO_DEBUGGER_H__
#define __MACRO_DEBUGGER_H__
  
  #ifdef ENABLE_DEBUG

    #include "Arduino.h"

    // Hardware Serial connection pins (These could be multiplexed to most pins)
    #define SER_0_PIN_RX                  03
    #define SER_0_PIN_TX                  01
    #define SER_1_PIN_RX                  17
    #define SER_1_PIN_TX                  16
    #define SER_2_PIN_RX                  27
    #define SER_2_PIN_TX                  26

    // By default, use 115.2 Kbits/s
    #ifndef DEBUG_SER_BAUD_RATE
      #define DEBUG_SER_BAUD_RATE         115200  // 115.2K baud serial connection to computer
    #endif

    // By default, use Serial 0
    #ifndef DEBUG_SERIAL_PORT
      #define DEBUG_SERIAL_PORT           Serial
    #endif

    #ifndef DEBUG_RX_PIN
      #define DEBUG_RX_PIN                SER_0_PIN_RX
    #endif

    #ifndef DEBUG_TX_PIN
      #define DEBUG_TX_PIN                SER_0_PIN_TX
    #endif
    
    #define DEBUG_BEGIN()                 DEBUG_SERIAL_PORT.begin(DEBUG_SER_BAUD_RATE, SERIAL_8N1, DEBUG_RX_PIN, DEBUG_TX_PIN)
    #define DEBUG(X...)                   DEBUG_SERIAL_PORT.printf(X)
    #define DEBUGLN(X...)                 ( {DEBUG_SERIAL_PORT.printf(X), DEBUG_SERIAL_PORT.println();} )

    #define DEBUG_E(X...)                 ( {DEBUG("%-10s-- ", "[ERROR]"),   DEBUGLN(X);} )
    #define DEBUG_W(X...)                 ( {DEBUG("%-10s-- ", "[WARNING]"), DEBUGLN(X);} )
    #define DEBUG_I(X...)                 ( {DEBUG("%-10s-- ", "[INFO]"),    DEBUGLN(X);} )

    #define DEBUG_ENDL()                  DEBUGLN("%s", "")
    
    #define DEBUG_AVAILABLE()             DEBUG_SERIAL_PORT.available()
    #define DEBUG_READ()                  DEBUG_SERIAL_PORT.read()
    
    #define DEBUG_FILL_UNTIL(B, C)        ({              \
      typeof(C) c = 0;                                    \
      uint32_t idx = 0;                                   \
      while( DEBUG_AVAILABLE() ){                         \
        if( (c = (typeof(C))DEBUG_READ()) == (C) ) break; \
        B[idx++] = c;                                     \
      }                                                   \
    })

    #define DEBUG_FLUSH()                ({               \
      while( DEBUG_AVAILABLE() ) DEBUG_READ();            \
    })
  
  #else
  
    #define DEBUG_BEGIN()                 // Nothing
    #define DEBUG(X...)                   // Nothing
    #define DEBUGLN(X...)                 // Nothing

    #define DEBUG_E(X...)                 // Nothing
    #define DEBUG_W(X...)                 // Nothing
    #define DEBUG_I(X...)                 // Nothing

    #define DEBUG_ENDL()                  // Nothing
    
    #define DEBUG_AVAILABLE()             (-1)
    #define DEBUG_READ()                  0
    
    #define DEBUG_FILL_UNTIL(B, C)        // Nothing

    #define DEBUG_FLUSH()                 // Nothing
  
  #endif // ENABLE_DEBUG

#endif // __MACRO_DEBUGGER_H__
