#include <Arduino.h>

#define array_size 500
#define analogPin_0 34
#define analogPin_1 35

#define LED_L 26
#define LED_R 27

//int mic1_values[array_size];
//int mic2_values[array_size];
int mic1_value;
int mic2_value;

int checkTime;
long long int prev = 0;

void setup()
{
  Serial.begin(115200);
  
   /*for(int i=0; i<array_size; i++)
   {
    mic1_values[i] = analogRead(analogPin_0);
    mic2_values[i] = analogRead(analogPin_1);
    delayMicroseconds(500);
   }
   //prev = micros() - prev;
   //Serial.println(prev);
   for(int i=0; i<array_size; i++)
   {
    if(mic1_values[i]<10000 && mic2_values[i]<10000){
    Serial.println(mic1_values[i]);
    Serial.println(mic2_values[i]);
    }; 
   }*/
}



int i=0;

void loop()
{
   //prev = micros();
   /*for(int i=0; i<array_size; i++)
   {
    mic1_values[i] = analogRead(analogPin_0);
    mic2_values[i] = analogRead(analogPin_1);
    delayMicroseconds(500);
   }
   //prev = micros() - prev;
   //Serial.println(prev);
   for(int i=0; i<array_size; i++)
   {
    if(mic1_values[i]<10000 && mic2_values[i]<10000){
    Serial.print(mic1_values[i]);
    Serial.print(" ");
    Serial.println(mic2_values[i]);
    }; 
   }*/

    /*while(i<array_size){
      mic1_values[i] = analogRead(analogPin_0);
      mic2_values[i] = analogRead(analogPin_1);
      delayMicroseconds(500);
  
      i++;
    }*/

    mic1_value = analogRead(analogPin_0);
    mic2_value = analogRead(analogPin_1);

    Serial.println(mic1_value);

    /*Serial.print(mic1_value);
    Serial.print(" ");*/
    Serial.println(mic2_value);
  
  /*if(Serial.available()>0){
    String stat;
    stat = Serial.readString();

    Serial.print("Received: ");
    Serial.println(stat);
    
    if(stat=="mic1"){
      digitalWrite(LED_L,HIGH);
      digitalWrite(LED_R,LOW);
    }
    else if(stat=="mic2"){
      digitalWrite(LED_R,HIGH);
      digitalWrite(LED_L,LOW);
    }
    else{
      digitalWrite(LED_R,HIGH);
      digitalWrite(LED_L,HIGH);
    }
  }*/
  
}
