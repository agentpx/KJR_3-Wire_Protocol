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
#define SIGNAL_LINE 3 
#define MASTER_LINE 4
#define SLAVE_LINE 5
#define LINE_ID '1'

bool SIGNAL_LINE_STAT = false;
bool startRecording = false; 
bool needtosend = false;
String str;
char chx;
uint16_t lapse; 
String cached_str;
bool itsforme = false;

void setup() 
{
  Serial.begin(9600);      
  pinMode(SIGNAL_LINE, INPUT);
  pinMode(MASTER_LINE, INPUT);
  pinMode(SLAVE_LINE, OUTPUT);   

  pinMode(9, OUTPUT);   
}

void loop() 
{
//********************************************************************  
//********************************************************************
SIGNAL_LINE_STAT = digitalRead(SIGNAL_LINE);
//******************************************************************** 
if(!SIGNAL_LINE_STAT) //RESPOND TO MASTER 
 { 
    if(itsforme)
    {    
      if(needtosend){
		const char * data_to_send_to_master = "111111111111111"; //"1-", "2-" ... "X-" SLAVE LINE ID X
        char concatenated_chars[127];  
        sprintf(concatenated_chars,"%c-%s,",LINE_ID, data_to_send_to_master);
        encode_lapse(concatenated_chars, SLAVE_LINE);  
        needtosend = !needtosend;  
      }
    }
 }
//******************************************************************** 
if(SIGNAL_LINE_STAT)
{   
        lapse = pulseIn(MASTER_LINE, HIGH);    
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
          
          if(str[0] == LINE_ID){
              Serial.println(str);  
              cached_str = str;
              itsforme = true; 
              needtosend = true;
              pinMode(SLAVE_LINE, OUTPUT);      
          } else {
              itsforme = false; 
              needtosend = false; 
              pinMode(SLAVE_LINE, INPUT);                
          }          
          str = "";           
          startRecording = false;
        }  
                
}//if        
//******************************************************************** 

digitalWrite(9, cached_str[2]=='0'?false:true); 


}//loop