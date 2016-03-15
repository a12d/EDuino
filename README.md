EDuino
======

Arduino sketch to use an arduino pro micro with a keypad driven macro system for elite:dangerous. Anyone that's played elite:dangerous will know that some aspect can be a bot of a grind, especially if you're trying to stack missions and are switching from open to solo and back.

As well as that there are a few things like docking which have a repeatable set of commands which are easily automated. These sketches can take over actions such as these and makes the game a little easier to play. This is especialy useful when doing something like trading where you are doing the same, repetative actions.

simple_keypad
-------------

This is a sketch for a keypad which is just a set of switches and not a matrix keypad (e.g. http://www.amazon.com/dp/B000TA8PE4). This doesn't require any other libraries to work and can only be reprogrammed by uploading a new sketch to the arduino.

matrix_keypad
-------------

This sketch is for a more complicated setup. It works with a matrix keypad (e.g. http://www.amazon.com/dp/B004S7PT48) and a micro sd card reader (e.g. http://www.amazon.com/dp/B00SL0QWDU). It uses the HashMap (http://playground.arduino.cc/Code/HashMap) and Keypad (http://playground.arduino.cc/Code/Keypad) libraries. Configuration for the macros is read from a microSD card and so it can be reconfigured more easily.

