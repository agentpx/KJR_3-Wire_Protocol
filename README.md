 **KJR 3-Wire-Protocol**
 
 **The techinical aspect behind the inner working of the kjr-3-wire-protocol and why it works well!**
 - It uses electrical energy pulses (pulse of certain duration)
 - Electrical energy travels at a constant speed no matter the medium (wire) resistance is
 - This protocol is similar to morse code, it depends on the duration of the beeps
 
 **Advantages**
 - Eliminated the distance limitations of common wire communication protocols (i.e. I2C, RS-232 (Serial), Parallel, & etc.)
 - Very to easy to setup and implement
 - You can add as many slaves as you want as long as you can accept the added delays for each slaves as this protocol works on queue concept as well
 
 **Disadvantages**
 - Slow transfer as this method of detection depends on the delay of the pulses
 - Voltage drop along the wires is directly proportional to the distance, if your project will require only few meters that would not be an issue, if you wanted to implement this at a larger distances, you can still make this work, just keep and maintain the voltage at the recieving end at a allowable detection threshold, you can use an external power booster
 - Electromagnetic interference from nearby location can cause crosstalks and could cause inaccurate data, to avoid this you can use the twisted wires or ideally use network cable cat 5e or cat6 or higher version.

**Note**
- The current version has a 17 character sets only ( Dot { } 0 1 2 3 4 5 6 7 8 9 + - Comma )

 **See below sample layout connections** 
 <img src="https://github.com/krakenjriot/KJR_3-Wire_Protocol/blob/master/sample_layout_connections.png" width=800 />  
 
 

