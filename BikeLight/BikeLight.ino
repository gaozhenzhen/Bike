#include <Adafruit_NeoPixel.h>
#include <MsTimer2.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

 boolean Lightonoff=HIGH; 
 boolean Ledonoff=HIGH; 
 boolean laseronoff=HIGH; 

 int LedPlay=1;
 int ColorMax=11;  //LED灯带显示形式总数
 int SoundMax=500; //声音最大值
 
 //int bt1=0;
 //int bt2=0;


//#define led 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  Serial.begin(9600);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

 // pinMode(led, OUTPUT);
  //digitalWrite(led, HIGH);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //MsTimer2::set(200, BtCheck);
  //MsTimer2::start();

  pinMode(2,INPUT); //按钮1
  pinMode(3,INPUT); //按钮2
  pinMode(4,INPUT); //按钮3

   
  pinMode(8,OUTPUT); //大灯
  pinMode(9,OUTPUT); //激光

  attachInterrupt(0, dolight, CHANGE);
  attachInterrupt(1, doLaser, CHANGE);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW  关闭Led
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue

  //rainbow(10);
 // rainbowCycle(10);
  //theaterChaseRainbow(50);

//=============================================================


//theaterChase(strip.Color(255, 0, 102), 50);//粉红色

//colorWipe(strip.Color(255, 0, 102), 20);//粉红色

//colorWipe(strip.Color(255, 255, 0), 20);//黄色





 
 if (LedPlay==1){
rainbowCycle(10);}//彩虹

 if (LedPlay==2){
colorWipe(strip.Color(0, 0, 0, 255), 50); }//关闭彩灯

if (LedPlay==3){
theaterChaseRainbow(50);}//跑马地彩虹

if (LedPlay==4){
colorWipe(strip.Color(255, 0, 102), 20);//粉红色
}

if (LedPlay==5){
theaterChase(strip.Color(255, 0, 102), 200);//粉红色
}

if (LedPlay==6){
colorWipe(strip.Color(255, 255, 0), 20);//黄色
}

if (LedPlay==7){
theaterChase(strip.Color(255, 255, 0), 200);//黄色
}

if (LedPlay==8){
colorWipe(strip.Color(162,230, 91), 20);//白色
}

if (LedPlay==9){
theaterChase(strip.Color(162,230, 91), 200);//白色
}

if (LedPlay==10){
colorWipe(strip.Color(12, 203, 251), 20);//蓝色
}

if (LedPlay==11){
theaterChase(strip.Color(12, 203, 251), 200);//蓝色
}





  
}

void dolight(){
  if(digitalRead(2)==HIGH)
    {
      digitalWrite(8,Lightonoff);  //写入当前LED状态onoff，
      Lightonoff=(!Lightonoff); //然后LED状态反转，以便下一次使用。
      //Serial.println(Lightonoff);
      delay(10); 
      while(digitalRead(2)==HIGH) 
      {
        delay(1);
      }
    }
  
  }


void doLaser(){
  if(digitalRead(3)==HIGH)
    {
      digitalWrite(9,laseronoff);  //写入当前LED状态onoff，
      laseronoff=(!laseronoff); //然后LED状态反转，以便下一次使用。
      //Serial.println(laseronoff);
      delay(10); 
      while(digitalRead(3)==HIGH) 
      {
        delay(1);
      }
    }
  }


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
     //==========================================================================================      
if(digitalRead(4)==HIGH)
    {
      LedPlay=LedPlay+1;
      
      if (LedPlay>=ColorMax+1){LedPlay=1;}
      delay(10); 
      while(digitalRead(4)==HIGH) 
      {
        delay(1);
      }
      return;
    }

   //声音传感器
    if (analogRead(A0)>SoundMax){
    colorWipe(strip.Color(127, 127, 127), 1);
    break;}
//==========================================================================================
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      //==========================================================================================      
if(digitalRead(4)==HIGH)
    {
      LedPlay=LedPlay+1;
      
      if (LedPlay>=ColorMax+1){LedPlay=1;}
      delay(10); 
      while(digitalRead(4)==HIGH) 
      {
        delay(1);
      }
      return;
    }
    
    //声音传感器
    if (analogRead(A0)>SoundMax){
    colorWipe(strip.Color(127, 127, 127), 1);
    break;}
//==========================================================================================
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//==========================================================================================      
if(digitalRead(4)==HIGH)
    {
      LedPlay=LedPlay+1;
      
      if (LedPlay>=ColorMax+1){LedPlay=1;}
      delay(10); 
      while(digitalRead(4)==HIGH) 
      {
        delay(1);
      }
      return;
    }

    //声音传感器
    if (analogRead(A0)>SoundMax){
    colorWipe(strip.Color(127, 127, 127), 1);
    break;}
//==========================================================================================
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
         //==========================================================================================      
if(digitalRead(4)==HIGH)
    {
      LedPlay=LedPlay+1;
      
      if (LedPlay>=ColorMax+1){LedPlay=1;}
      delay(10); 
      while(digitalRead(4)==HIGH) 
      {
        delay(1);
      }
      return;
    }

    //声音传感器
    if (analogRead(A0)>SoundMax){
    colorWipe(strip.Color(127, 127, 127), 1);
    break;}
//==========================================================================================
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        //==========================================================================================      
if(digitalRead(4)==HIGH)
    {
      LedPlay=LedPlay+1;
      
      if (LedPlay>=ColorMax+1){LedPlay=1;}
      delay(10); 
      while(digitalRead(4)==HIGH) 
      {
        delay(1);
      }
      return;
    }

    //声音传感器
    if (analogRead(A0)>SoundMax){
    colorWipe(strip.Color(127, 127, 127), 1);
    break;}
//==========================================================================================
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
