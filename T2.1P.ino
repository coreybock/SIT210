// ------------
// Blink an LED
// ------------

/*-------------

We've heavily commented this code for you. If you're a pro, feel free to ignore it.

Comments start with two slashes or are blocked off by a slash and a star.
You can read them, but your device can't.
It's like a secret message just for you.

Every program based on Wiring (programming language used by Arduino, and Particle devices) has two essential parts:
setup - runs once at the beginning of your program
loop - runs continuously over and over

You'll see how we use these in a second. 

This program will blink an led on and off every second.
It blinks the D7 LED on your Particle device. If you have an LED wired to D0, it will blink that LED as well.

Example modified by Corey Bock for SIT210 T2.1P

-------------*/


int led = D7; 


void setup() {

  pinMode(led, OUTPUT);

}

void blinkLong() {
    digitalWrite(led, HIGH);
    delay(1500);
    digitalWrite(led, LOW);
    delay(500);
}

void blinkShort(){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
}


void blinkLetter(char letter) {
    switch (letter){
        
        case 'C':
            blinkLong();
            blinkShort();
            blinkLong();
            blinkShort();
        
        case 'O':
            blinkLong();
            blinkLong();
            blinkLong();
            
        case 'R':
            blinkShort();
            blinkLong();
            blinkShort();
            
        case 'E':
            blinkShort();
            
        case 'Y':
            blinkLong();
            blinkShort();
            blinkLong();
            blinkLong();
        
    }
    
}

void loop() {

  // Morse Code - firstname Corey
  blinkLetter('C');
  blinkLetter('O');
  blinkLetter('R');
  blinkLetter('E');
  blinkLetter('Y');
  

}



