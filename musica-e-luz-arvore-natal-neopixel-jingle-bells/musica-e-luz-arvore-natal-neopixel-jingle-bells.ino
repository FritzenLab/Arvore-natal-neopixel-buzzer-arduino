/*
 * Christmas tree with light, sound and Arduino!
 * A Digispark ATtiny85 controls both a Buzzer (sound) and
 * a RGB LED (WS2812b neopixel).
 * 
 * The Buzzer plays Jingles Bells from here: 
 * http://blog.giacomocerquone.com/jingle-bell-with-an-arduino-and-a-buzzer/
 * and the LED anternates Red and Green (to the beat of the music)
 * 
 * Developed by Clovis Fritzen in 12/05/2016
 * More info at http://fritzenlab.com.br
*/

#include <Adafruit_NeoPixel.h>  
 #ifdef __AVR__  
  #include <avr/power.h>  
 #endif  
   
 // Which pin on the Arduino is connected to the NeoPixels?  
 #define PIN      0  
   
 // How many NeoPixels are attached to the Arduino?  
 #define NUMPIXELS   1  
   
 Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  
 int passada1 = 1;
 const int j = 0;
 
int buzzerPin = 2;
int tempo = 200;
int playtwice = 0;
int tempomaisum = 0;
int tempoatual = 0;
int tempoantigo = 0;

char notes[] = "eeeeeeegcde fffffeeeeddedg";
int duration[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
void playTheShit(char note, int duration) {
  char notesName[] = { 'c', 'd', 'e', 'f', 'g' };
  int tones[] = { 261, 293, 329, 349, 392 };
  for (int i = 0; i < sizeof(tones); i++) {
    // Bind the note took from the char array to the array notesName
    if (note == notesName[i]) {
      // Bind the notesName to tones
      tone(buzzerPin, tones[i], duration);
    }
  }
}
void setup() {
  pinMode(buzzerPin, OUTPUT);
  pixels.begin(); // This initializes the NeoPixel librar
}

void loop() {

  tempoatual = millis();
  if (tempoatual - tempoantigo > 30000) {
    tempomaisum ++;
    if (tempomaisum > 10) {
      playtwice = 0;
      tempomaisum = 0;
    }
    
  }
  if (playtwice < 2) {
    tempoantigo = millis();
    playtwice = playtwice ++;
  // Scan each char from "notes"
  for (int i = 0; i < sizeof(notes)-1; i++) {
    
    if (notes[i] == ' ') {
       
      // If find a space it rests
     
      delay(duration[i] * tempo);
    } else {
      
      playTheShit(notes[i], duration[i] * tempo);
            
      if (passada1 == 1) {
      pixels.setPixelColor(j, pixels.Color(0,150,0)); // Moderately bright green color.  
      pixels.show(); // This sends the updated pixel color to the hardware.
      passada1= 0;
      } else{
      pixels.setPixelColor(j, pixels.Color(150,0,0)); // Moderately bright green color.  
      pixels.show(); 
      passada1=1; 
      }
    }
    // Pauses between notes
    
    delay((tempo*2)*duration[i]);
  }
  } else {
    
  }
  
}
