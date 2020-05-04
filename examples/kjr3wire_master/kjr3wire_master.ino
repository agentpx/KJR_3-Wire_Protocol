 /***
 *      _  ______      _    _  _______ _   _       _ ____      ___ ___ _____ 
 *     | |/ /  _ \    / \  | |/ / ____| \ | |     | |  _ \    |_ _/ _ \_   _|
 *     | ' /| |_) |  / _ \ | ' /|  _| |  \| |  _  | | |_) |    | | | | || |  
 *     | . \|  _ <  / ___ \| . \| |___| |\  | | |_| |  _ < _   | | |_| || |  
 *     |_|\_\_| \_\/_/   \_\_|\_\_____|_| \_|  \___/|_| \_(_) |___\___/ |_|  
 *     
 *                          KJR 3 WIRE PROTOCOL 
 *                       https://krakenjriot.tech/
 *                  https://internetofthingsbuilder.com/
 *                          funsideofwine@gmail.com   
 *                                        
 * MIT License
 *
 * Copyright (c) 2020 Rolly Falco Villacacan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "kjr3wire.h"
#define SIGNAL_LINE 3 //3  
#define MASTER_LINE 4 //4
#define SLAVE_LINE  5 //5
#define LINE_ID '0'
#define MAX_NODES 2 //Total Number of Slave Nodes


#define INTERVAL_MESSAGE1 1000 // timer for 3-wires
unsigned long time_1 = 0;


unsigned int call_counter = 0; //calling slaves index

bool SIGNAL_LINE_STAT = false;
bool startRecording = false; 
String str;
char chx;
uint16_t lapse;  
bool needtosend = false;
String id;

void setup() 
{
//********************************************************************   
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to initialize
    //logo();
  }
  //Serial.println("Serial ready"); 

//********************************************************************       
  pinMode(SIGNAL_LINE, OUTPUT);
  pinMode(MASTER_LINE, OUTPUT);
  pinMode(SLAVE_LINE, INPUT); 
//********************************************************************   
}

void loop() 
{
//******************************************************************** 
if(millis() >= time_1 + INTERVAL_MESSAGE1)
{
  time_1 +=INTERVAL_MESSAGE1;      
  SIGNAL_LINE_STAT = !SIGNAL_LINE_STAT;
  digitalWrite(SIGNAL_LINE,SIGNAL_LINE_STAT); 
  needtosend = true;  
}    
//********************************************************************



  
//******************************************************************** 
if(SIGNAL_LINE_STAT)
 { 
      if(needtosend){        
        char concatenated_chars[127];  
        call_counter++;
        if(call_counter == MAX_NODES + 1) call_counter = 1;  
        const char* data_to_send_to_slave = "000000000000000";		
        sprintf(concatenated_chars,"%i-%s,", call_counter, data_to_send_to_slave);                
        encode_lapse(concatenated_chars, MASTER_LINE);  
        needtosend = !needtosend; 
      } 
 }
//******************************************************************** 
 if(!SIGNAL_LINE_STAT)
 {
        lapse = pulseIn(SLAVE_LINE, HIGH);    
        chx = decode_lapse(lapse);
        if(chx == '{')
        {
          startRecording = true;
        } 
        if(startRecording) 
        {
          if(chx != '{' && chx != '}')
          {
            str += chx;  
          }          
        }
        if(chx == '}')
        {
          Serial.println(str);  
          str = "";           
          startRecording = false;  
        }      
    }//if   
         
//******************************************************************** 
//******************************************************************** 




       
}//loop