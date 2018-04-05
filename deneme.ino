#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>

// OLED display TWI address
#define OLED_ADDR   0x3C
#define TxD 2
#define RxD 3

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth

void setup() {
  mySerial.begin(9600); // For Bluetooth
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);
}

void loop() {

  boolean isValidInput; 
  
  do { 
    byte c; // get the next character from the bluetooth serial port

    while ( !mySerial.available() ) ; // LOOP... 
    c = mySerial.read(); // Execute the option based on the character recieved
    Serial.print(c); // Print the character received to the IDE serial monitor
    
        switch ( c ) { 
        case '1': 
            display.clearDisplay();
            writeToOled("Gonderebildik");
            mySerial.println( "GRUP 6" );
            isValidInput = true;
            break;
        case '0': 
            display.clearDisplay();
            writeToOled("Naber \n GRUP 6");
            mySerial.println( "TURN OFF" );
            isValidInput = true;
            break;
        default:
            mySerial.println( "Please enter 'a' or 'b'" );
        
        isValidInput = false;
        break;
        }
    
    } while ( isValidInput == true ); 
}

void writeToOled(char arr[])
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27,30);
    display.print(arr);
    display.display();
  
}


