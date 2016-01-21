int ppm1 = 2;  
int ppm2 = 3;
int N=0,S=0,F=0;
int Long=0,Short=0,Focus_Stop=0;
unsigned long rc1_PulseStartTicks,rc2_PulseStartTicks;        
volatile int rc1_val;
volatile int rc2_val; 

 int led = 13;
 unsigned char data_to_send_near[7] =    {0xff,0x01,0x00,0x20,0x00,0x00,0x21,};
 unsigned char data_to_send_far[7] =     {0xff,0x01,0x00,0x40,0x00,0x00,0x41,};
 unsigned char data_to_send_stop[7] =    {0xff,0x01,0x00,0x00,0x00,0x00,0x01,}; 
unsigned char focus_long[7] =     {0xff,0x01,0x01,0x00,0x00,0x00,0x02,};
unsigned char focus_short[7] =    {0xff,0x01,0x00,0x80,0x00,0x00,0x81,};

void setup() {
        pinMode(led, OUTPUT);
        Serial.begin(9600);  
 
        //PPM inputs from RC receiver
        pinMode(ppm1, INPUT); 
        pinMode(ppm2, INPUT); 
 
        // 电平变化即触发中断
        attachInterrupt(0, rc1, CHANGE);    
        attachInterrupt(1, rc2, CHANGE);   
        Serial.write(data_to_send_stop,7);
}
 
void rc1()
{
        // did the pin change to high or low?
        if (digitalRead( ppm1 ) == HIGH)
                rc1_PulseStartTicks = micros();    // store the current micros() value
        else
                rc1_val = micros() - rc1_PulseStartTicks; 

          if(rc1_val < 1300)
            if(N==0)     
            {
              //Serial.write(data_to_send_stop,7);
              Serial.write(data_to_send_near,7);
              N=1;
              F=0;
              S=0;
            }
          if(rc1_val > 1700)
            if(F==0)
            {
              //Serial.write(data_to_send_stop,7);
              Serial.write(data_to_send_far,7);
              F=1;
              N=0;
              S=0;
            }
         
        if(1300<=rc1_val && rc1_val<=1700)
          if(S==0)
          {
            Serial.write(data_to_send_stop,7);
            S=1;
            N=0;
            F=0;
          }
        
      
}
 
void rc2()
{
        // did the pin change to high or low?
        if (digitalRead( ppm2 ) == HIGH)
                rc2_PulseStartTicks = micros();    // store the current micros() value
        else
                rc2_val = micros() - rc2_PulseStartTicks; 

          if(rc2_val < 1300)
            if(Short ==0)     
            {
              //Serial.write(data_to_send_stop,7);
              Serial.write(focus_short,7);
              Short=1;
              Long=0;
              Focus_Stop=0;
            }
          if(rc2_val > 1700)
            if(Long ==0)
            {
              //Serial.write(data_to_send_stop,7);
              Serial.write(focus_long,7);
              Long=1;
              Short=0;
              Focus_Stop=0;
            }
         
        if(1300<=rc2_val && rc2_val<=1700)
          if(Focus_Stop==0)
          {
            Serial.write(data_to_send_stop,7);
            Focus_Stop=1;
            Long=0;
            Short=0;
          }
        
      
}
 
void loop() {
//        digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
//        delay(1000);               // wait for a second
//        digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
//        delay(1000);               // wait for a second
//        Serial.print("channel 1:  ");
//        Serial.print(rc1_val); 
//        Serial.write(data_to_send,8);
        //print values
//        Serial.print("channel 1:  ");
// //       Serial.println(rc1_val);  
//        Serial.print("        ");
//        if(rc1_val < 50)
//          Serial.write(data_to_send_near,8);
//        else
//          Serial.write(data_to_sende_far,8);
//        Serial.print("channel 2:  ");   
//        Serial.println(rc2_val);  
}
