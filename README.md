# MacroDebugger

## What is it?

The Arduino library that **will save you a ton of time** if (like me), you do a lot of debug printing, but you never want to leave the ```Srial.println()```s in your final code!

So imagine, you write a ```Serial.print("wtf dude, i'm here with value: "); Serial.println(value);``` in your code, you figure out what's not working, and now you have 20+ prints here and there, you go on and delete 18 of them, only to realize that you need to add another feature, and you have to rewrite all of the prints (because who does write a new feature without writing 10 new bugs) ... Sad, isn't it?

Well, ```MacroDebugger``` is to the save! Write your "prints", debug your code, COMMENT ONE LINE, all your prints are gone (not deactivated with an if-else close, NOOOOOO, gone! Not even present in the codebase), then, by UNCOMMENTING that same line, all your prints are back ... Cool, isn't it!

This "magic" is possible thanks to the power of [MACROS](https://gcc.gnu.org/onlinedocs/cpp/Macros.html)!

## Available "functions"

```DEBUG_BEGIN()```: Starts the Serial port (by default it uses Serial, but it could be changed (see examples)) at a given baudrate (by default it's 115200, but could be changed (see examples)).

```DEBUG("format", variables)```: It's basically (literally) C's ```printf()```.

```DEBUGLN("format", variables)```: Literally ```DEBUG```, but since I'm always forgetting to add a ```'\n'```, here's ```DEBUGLN```.

```DEBUG_E(...)```: Prints whatever you give it, but adds ```[ERROR]-``` to the beginning of the string (example: ```DEBUG_E("1/%d = stupid", 0);``` --> ```"[ERROR]- 1/0 = stupid"```).

```DEBUG_W(...)```: Same as error, but it adds ```[WARNING]-```.
```DEBUG_I(...)```: Same as E, and W, but it add ```[INFO]-``` (hopefully this is the one you'll be seeing most of the time).

```DEBUG_ENDL()```: Prints a newline.

```DEBUG_AVAILABLE()```: Returns whether data is available in the Serial buffer or not (check Serial.available() for more info).
```DEBUG_READ()```: Reads a byte from the Serial buffer (if available).

```DEBUG_FILL_UNTIL(B, C)```: Given a buffer B, this will fill it from the Serial buffer (hardware) until it reads the char C, or there's no more data available.

```DEBUG_FLUSH()```: Empties the Serial buffer (hardware).

## Notes

Tested this on an ESP32, and an Arduino Nano. (I don't have an ESP8266, or and Arduino Uno right now, but given my experience with them, they should work as well).
