## Code and Enclosure for Analog Panel Clock

![](https://i.imgur.com/5gGHVKn.jpg)

Materials
--------------
1 x Arduino Nano (Really any arduino should work that has two PWM outputs, two digital inputs, and SPI)

2 x Analog Panel Voltmeters (0-5V Panel Mount Voltmeters)
   -- https://www.amazon.com/gp/product/B0051E8ONA
   -- https://www.ebay.com/itm/DC-0-5V-Analog-Voltmeter-Analogue-Voltage-panel-meter-SO45-directly-Connect/181981812727

1 x DS3231 RTC Module -- https://www.amazon.com/gp/product/B00LX3V7F0

2 x Tactile buttons

Assembly
----------------
- Disassemble both panel meters, and replace the meter scales.   I just traced the existing scale and printed new ones on paper, gluing them to the existing scale.
- Attach Pin D5 of the Nano to the + side of your hour voltmeter
- Attach Pin D6 of the Nano to the + side of your minute voltmeter
- Attach Pin D3 of the Nano to one side of the first button
- Attach Pin D2 of the Nano to one side of the second button
- Attach Pin A4 to SDA of your RTC module
- Attach Pin A5 to SCL of your RTC module
- Attach 5V pin to VCC of RTC Module
- Attach GND pin to GND of RTC Module

**Be sure to install the appropriate coin cell battery into your RTC module**

Power on and Adjustment
------------------------------
- Power the Nano via the USB port, upload the code
- Press the hour button once and see how far the pin moves on your new scale, you may need to adjust the "hourAnalogUnit" parameter larger or smaller depending on how far the needle for YOUR meter moves per hour
- Repeat the same process for minutes (push it 10 times, the dial should move about 1/6th of the distance, adjust)


