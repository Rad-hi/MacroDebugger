/* 
 * -----------------------------------------------------------------------------
 * Library: MacroDebugger
 * This is a MACRO-based debug-printing library.
 * The special thing about it is that since it's MACRO-based, this allows us
 * to remove all printing statements through the change of a single line of code
 * (or to be more specific, the commenting of a line).
 * -----------------------------------------------------------------------------
 * It allows for:
 *    - Printing formatted strings (C style)
 *    - Serial read/write, and even filling a buffer with serial data until a 
 * 		a provided character
 *    - Change of the Serial port used (tested on an ESP32 with Serial2 & Putty)
 * All this could be present in your codebase, and you don't have to get back
 * and delete it all (delete this Serial.println, and this one, ...), been there!
 * YOU JUST COMMENT ONE LINE!
 * -----------------------------------------------------------------------------
 * Author: Radhi SGHAIER: https://github.com/Rad-hi
 * -----------------------------------------------------------------------------
 * Date: 07-09-2022 (7th of September, 2022)
 * -----------------------------------------------------------------------------
 * License: Do whatever you want with the code ...
 *          If this was ever useful to you, and we happened to meet on 
 *          the street, I'll appreciate a cup of dark coffee, no sugar please.
 * -----------------------------------------------------------------------------
 */
#ifndef __MACRO_DEBUGGER_H__
#define __MACRO_DEBUGGER_H__
  
  #ifdef ENABLE_DEBUG // Nothing is even included incase we don't want debug-printing

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

/* Architecture dependent macros */
    
    #if defined(ARDUINO_ARCH_ESP32) or defined(ARDUINO_ARCH_ESP8266)

      // Define the Serial pins (multiplexed on the ESPs
      #ifndef DEBUG_RX_PIN
        #define DEBUG_RX_PIN              SER_0_PIN_RX
      #endif
  
      #ifndef DEBUG_TX_PIN
        #define DEBUG_TX_PIN              SER_0_PIN_TX
      #endif
      
      #define DEBUG_BEGIN()               DEBUG_SERIAL_PORT.begin(DEBUG_SER_BAUD_RATE, SERIAL_8N1, DEBUG_RX_PIN, DEBUG_TX_PIN)
      #define DEBUG(X...)                 DEBUG_SERIAL_PORT.printf(X)
      #define DEBUGLN(X...)               ( {DEBUG_SERIAL_PORT.printf(X), DEBUG_SERIAL_PORT.println();} )
    
    #else // Arduino side
    
      // Ref: https://playground.arduino.cc/Main/Printf/

      // Unfortunately, we need to allocate memroy beforehands for this
      #ifndef PRINT_BUFFER_SIZE
        #define PRINT_BUFFER_SIZE           128
      #endif
      
      #include <stdarg.h>
      
      void p(char *fmt, ...){
        char buf[PRINT_BUFFER_SIZE];
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, PRINT_BUFFER_SIZE, fmt, args);
        va_end (args);
        DEBUG_SERIAL_PORT.print(buf);
      }

      // Taking advantage of the fact that the Arduino IDE uses a C++ compiler --> Polymorphism
      void p(const __FlashStringHelper *fmt, ... ){
        char buf[PRINT_BUFFER_SIZE];
        va_list args;
        va_start (args, fmt);
      #ifdef __AVR__
        vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
      #else
        vsnprintf(buf, sizeof(buf), (const char *)fmt, args); // for the rest of the world
      #endif
        va_end(args);
        DEBUG_SERIAL_PORT.print(buf);
      }


      #define DEBUG_BEGIN()               DEBUG_SERIAL_PORT.begin(DEBUG_SER_BAUD_RATE)
      #define DEBUG(X...)                 p(X)
      #define DEBUGLN(X...)               ( {p(X), DEBUG_SERIAL_PORT.println();} )
      
    #endif
        
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
    
    #define DEBUG_AVAILABLE()             0
    #define DEBUG_READ()                  0
    
    #define DEBUG_FILL_UNTIL(B, C)        // Nothing

    #define DEBUG_FLUSH()                 // Nothing
  
  #endif // ENABLE_DEBUG

#endif // __MACRO_DEBUGGER_H__
