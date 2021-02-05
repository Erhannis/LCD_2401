 /*
 This sketch is setup to talk to 24x1 LiquidCrystal display (WD-2401P)
 
 This sketch prints "Hello World!" to the LCD and shows the time.
 
 The circuit default pin #s (Can be changed, see below):

 LCD GND to GND
 LCD VCC to 5V
 LCD everything else, starting from RESET up to D7, to pins 13 down to 2, respectively

 Spelled out:
 * LCD GND to GND
 * LCD VCC to 5V
 * LCD RESET pin to digital pin 13
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD R/W pin to digital pin 10
 * LCD D0 pin to digital pin 9
 * LCD D1 pin to digital pin 8
 * LCD D2 pin to digital pin 7
 * LCD D3 pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * Also note that this LCD takes a minimum of 10 pins (can not talk 4 bit mode)
 */
///////////////////////////////////////////////////////////////////////////////////
// The WDC2401P class contains the following functions:                            
// WDC2401P Class_Name(RS, EN, D0, D1, D2, D3, D4, D5, D6, D7); define class       
//   The LCD pins to be remapped as listed above when calling the WDC2401P class   
// Initialize(); initialize the LCD                                                 
// Clear(); clear the lcd display                                                  
// CursorPos(position); sets the position for cursor (position is 0 to 23)         
// PrintChar(string); Prints a character string to the LCD                         
// PrintNum(long); Prints the decimal value of long to LCD                         
///////////////////////////////////////////////////////////////////////////////////
class WDC2401P
{
private:
  byte _rs_pin;      // define RS Arduino pin #
  byte _enable_pin;  // define enable Arduino pin #
  byte _data_pin0;   // define D0 Arduino pin #
  byte _data_pin1;   // define D1 Arduino pin # 
  byte _data_pin2;   // define D2 Arduino pin #
  byte _data_pin3;   // define D3 Arduino pin #
  byte _data_pin4;   // define D4 Arduino pin #
  byte _data_pin5;   // define D5 Arduino pin #
  byte _data_pin6;   // define D6 Arduino pin #
  byte _data_pin7;   // define D7 Arduino pin #   

  WDC2401P& WriteCommand(byte Command = 0x01)  // The following code writes a command to the LCD
  { 
    digitalWrite(_rs_pin, LOW);                // set LCD RS pin low for sending commands 
    digitalWrite(_data_pin0, Command & 0x01);  // set LCD bit d0 
    digitalWrite(_data_pin1, Command & 0x02);  // set LCD bit d1 
    digitalWrite(_data_pin2, Command & 0x04);  // set LCD bit d2
    digitalWrite(_data_pin3, Command & 0x08);  // set LCD bit d3 
    digitalWrite(_data_pin4, Command & 0x10);  // set LCD bit d4 
    digitalWrite(_data_pin5, Command & 0x20);  // set LCD bit d5 
    digitalWrite(_data_pin6, Command & 0x40);  // set LCD bit d6 
    digitalWrite(_data_pin7, Command & 0x80);  // set LCD bit d7
    digitalWrite(_enable_pin, HIGH);   // set LCD Enable High 
    delay(2);
    digitalWrite(_enable_pin, LOW);    // set LCD Enable low - This should latch data
    delay(20);                         // A little delay to allow command to implament
  }

  WDC2401P& WriteData(byte Data = 0x01)     // The following code writes data to the LCD
  { 
    digitalWrite(_rs_pin, HIGH);            // set LCD RS pin low for sending commands 
    digitalWrite(_data_pin0, Data & 0x01);  // set LCD bit d0 
    digitalWrite(_data_pin1, Data & 0x02);  // set LCD bit d1 
    digitalWrite(_data_pin2, Data & 0x04);  // set LCD bit d2
    digitalWrite(_data_pin3, Data & 0x08);  // set LCD bit d3 
    digitalWrite(_data_pin4, Data & 0x10);  // set LCD bit d4 
    digitalWrite(_data_pin5, Data & 0x20);  // set LCD bit d5 
    digitalWrite(_data_pin6, Data & 0x40);  // set LCD bit d6 
    digitalWrite(_data_pin7, Data & 0x80);  // set LCD bit d7
    digitalWrite(_enable_pin, HIGH);   // set LCD Enable High 
    delay(1);
    digitalWrite(_enable_pin, LOW);    // set LCD Enable low - This should latch data
    delay(1);
  }

public:  
  WDC2401P(byte _rs=12, byte _en=10,
           byte _d0=9, byte _d1=8,
           byte _d2=7,  byte _d3=6,
           byte _d4=5,  byte _d5=4,
           byte _d6=3,  byte _d7=2) :
    _rs_pin(_rs),      // define RS Arduino pin #
    _enable_pin(_en),  // define enable Arduino pin #
    _data_pin0(_d0),   // define D0 Arduino pin #
    _data_pin1(_d1),   // define D1 Arduino pin # 
    _data_pin2(_d2),   // define D2 Arduino pin #
    _data_pin3(_d3),   // define D3 Arduino pin #
    _data_pin4(_d4),   // define D4 Arduino pin #
    _data_pin5(_d5),   // define D5 Arduino pin #
    _data_pin6(_d6),   // define D6 Arduino pin #
    _data_pin7(_d7)    // define D7 Arduino pin #   
  {
  }
  
  void Initialize()
  {    
    pinMode(_rs_pin, OUTPUT);
    pinMode(_enable_pin, OUTPUT);
    pinMode(_data_pin0, OUTPUT);
    pinMode(_data_pin1, OUTPUT);
    pinMode(_data_pin2, OUTPUT);
    pinMode(_data_pin3, OUTPUT);
    pinMode(_data_pin4, OUTPUT);
    pinMode(_data_pin5, OUTPUT);
    pinMode(_data_pin6, OUTPUT);
    pinMode(_data_pin7, OUTPUT);
    
    digitalWrite(_enable_pin, LOW);    // set LCD Enable low to start

    // The following code turns on the LCD driver power
    // D0 = set LCD in standby mode 
    // D1 = set LCD in sleep mode 
    // D2 = turn on voltage follower and booster 
    // D3-D7 = LCD Driver Power address
    WriteCommand(0x1C);
    delay(200);                        // delay added to allow LCD time to boot up

    // The following code sets the LCD cursor to non blinking
    // D0 = set LCD line cursor blinking on/off
    // D1 = set LCD 8th row raster segment on/off
    // D2 = set LCD B/W inverting cursor on/off 
    // D3-D7 = LCD Cursor Display address
    WriteCommand(0x08);

    // The following code turns on the LCD character display
    // D0 = set LCD line cursor on/off
    // D1 = set LCD segmant display on/off
    // D2 = set LCD Char display on/off 
    // D3-D7 = LCD Character Display address
    WriteCommand(0x14);

    // The following code sets the LCD display to 1 line 
    // LCD is actually 2 lines of 12 char printed end to end
    // D0 = set LCD display line to be double height (DL1) 
    // D1 = set LCD display line to be double height (DL2)
    // D2 = set LCD display line to be double height (DL3)
    // D3 = set LCD display lines (NL0)
    // D4 = set LCD display lines (NL1) 
    // D5-D7 = LCD Line Display address
    WriteCommand(0x28);

    // The following code sets the LCD contrast to high 
    // D0 = set LCD Contrast adjust (CT0)
    // D1 = set LCD Contrast adjust (CT1)
    // D2 = set LCD Contrast adjust (CT2)
    // D3 = set LCD Contrast adjust (CT3)
    // D4 = set LCD start line (SN2)
    // D5-D7 = LCD Contrast address
    WriteCommand(0x4F);
  }

  void Clear()
  {
    // The following code clears the LCD display and sets DRAM addr 0 in addr counter
    WriteCommand(0x01);
    delay(20);                          // A little delay to allow display to clear
  }
  
  void CursorPos(byte location)
  {
    // Not sure what happened here, but at 16 and above the address steps backwards
    if (location > 15)
    {
      location=location+4;             // This seems messed up but it works
    } 
    if (location > 23 || location < 0) // check for location outside display range
    {
      location = 24;                   // set location of first char outside display range
    }
    location = location + 0xE0;        // add LCD cursor location address (0xE0) to location
    WriteCommand(location);            // Send command to move cursor to selected location
  }

  void PrintChar(char *c_Text)
  {
    char c_Temp;                                                       // Temp holder for character to display
    // The following code prints the characters to LCD
    for (int i = 0; i < 23; i++) {
      c_Temp = *(c_Text+i);
      if (c_Temp == '\0') {
        i=24;
      }
      else
      {
        WriteData(c_Temp);
      }
    }
  }
    
  void PrintNum(long c_Num)
  {
    boolean PrintZero = false;// flag to print trailing zeros of number
    char c_Temp;              // Temp holder for character to display
    long c_Div = 1000000000;  // Temp holder for number to divide long number down
    if (c_Num < 0 )           // If number is negative then print - char to LCD
    {
       WriteData('-');        
       c_Num = abs(c_Num);
    }
    if (c_Num == 0)           // If number is Zero then print 0 char to LCD
    {
       WriteData('0');
    }
    else                      // Print number to LCD
    { 
      for (int i = 0; i < 10; i++) 
      {
        if (c_Num >= c_Div) 
        {
          c_Temp = c_Num / c_Div + 48;  // offset number by 48 for character
          c_Num = c_Num % c_Div;        // Get modulo for next digit
          WriteData(c_Temp);            // write digit to LCD
          PrintZero = true;
        }
        else if (PrintZero)             // Print trailing zeros of number
        {
          WriteData('0');
        }
        c_Div = c_Div / 10;             // setup c_Div for next digit
      }
    }
  }
};
// END OF WDC2401P CLASS //////////////////////////////////////////////

// Setup the LCD Class and interface pins as defined below
//WDC2401P LCD(RS, EN, D0, D1, D2, D3, D4, D5, D6, D7)
WDC2401P LCD(12, 10, 9,8, 7, 6, 5, 4, 3, 2);
//WDC2401P LCD(31, 33, 34, 35, 36, 37, 38, 39, 40, 41);

#define RESET 13
#define RW 11
void setup() {
//  Serial.begin(115200);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Native USB only
//  }
//  Serial.println("Goodnight moon!");

  pinMode( RW, OUTPUT );
  digitalWrite( RW, LOW );

  pinMode( RESET, OUTPUT );
  digitalWrite( RESET, LOW );
  delayMicroseconds(1000*10);
  digitalWrite( RESET, HIGH );
  delayMicroseconds(1000*10);

  
  // Initialize the LCD (this must be done!)
  LCD.Initialize(); 
  // Clear the LCD Display
  LCD.Clear();
  // use PrintChar() command to print to LCD screen
  LCD.PrintChar("goodnight, moon!");
}

void loop() 
  {
    // Set the cursor position (note: first char is 0 not 1)
    LCD.CursorPos(17);
    // print the number of seconds since reset:
    LCD.PrintNum(millis()/1000);
    //Serial.println(millis()/1000);
    delay(200);
  }