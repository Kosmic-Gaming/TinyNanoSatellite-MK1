/*
    Made by Ankur Parchure A.K.A Kosmic
    9th April 2022
    Components Used:
    ATtiny85 / ATmega8a-PU, DHT11 Sensor, RF Transmitter - 434MHz
*/


//Libraries
#include <DFRobot_DHT11.h>

//Define DHT Sensor
DFRobot_DHT11 DHT;

//Pin Definitions
const int pm = 1; // Negative or Positive Determiner
const int en = 2; //SPI Enable
const int tx1 = 3; //Transmission Bit 1
const int tx2 = 4; //Transmission Bit 2
#define DHT11_PIN 0 //Temperature Sensor

//SPI Variables
//Temperature Sensor Digits

int d1 = 0;
int d2 = 0;
int d3 = 0;

int hu1 = 0;
int hu2 = 0;
int hu3 = 0;

//RTC - Hours
int h1 = 0;
int h2 = 0;

//RTC - Minutes
int m1 = 0;
int m2 = 0;

//RTC - Seconds
int s1 = 0;
int s2 = 0;

//Software Variables
int t = 0; //DHT Reading
int h = 0;
int c1 = 0; //Calculation Variable 1
int c2 = 0; //Calculation Variable 2
int temp = 0; //Static Temperature Variable
int hum = 0;
int uart = 0; //Transmission UART
int spi = 0; //Register Selection

//Time Variables
int hours = 0;
int minutes = 0;
int seconds = 0;

void setup() {

  //Pin Modes
  pinMode (pm, OUTPUT); pinMode (en, OUTPUT); pinMode (tx1, OUTPUT); pinMode (tx2, OUTPUT); pinMode (DHT11_PIN, INPUT);

}
void loop() {

  //RTC Check
  seconds == seconds + 6;
  if (seconds >= 60) {
    seconds = 0;
    minutes++;
  }
  if (minutes >= 60) {
    minutes = 0;
    hours++;
  }
  if (hours >= 24) {
    hours = 0;
  }

  //Conversion of RTC Variables to Individual Variables
  h1 = hours / 10;
  h2 = hours % 10;
  m1 = minutes / 10;
  m2 = minutes % 10;
  s1 = seconds / 10;
  s2 = seconds % 10;

  //Update Temperature Reading
  DHT.read(DHT11_PIN);

  //Positive or Negative Integer Check
  t = DHT.temperature;
  h = DHT.humidity;
  Serial.println (t);


  //Conversion of Temperature Variables to Individual Variables
  if (t < 1000) {
    temp = t;
    d3 = temp % 10;
    c1 = temp / 10;
    d2 = c1 % 10;
    c2 = c1 / 10;
    d1 = c2 % 10;

    hum = h;
    hu3 = hum % 10;
    c1 = hum / 10;
    hu2 = c1 % 10;
    c2 = c1 / 10;
    hu1 = c2 % 10;
  }

  //Main SPI Transmission Packets
  while (spi <= 11) {
    if (t < 0) {
      t = t * -1;
      digitalWrite (pm, HIGH);
    }
    else {
      digitalWrite (pm, LOW);
    }

    //Register Select For Transmission
    if (spi == 0) {
      uart = d1;

    }
    if (spi == 1) {
      uart = d2;

    }
    if (spi == 2) {
      uart = d3;

    }
    if (spi == 3) {
      uart = hu1;

    }
    if (spi == 4) {
      uart = hu2;

    }
    if (spi == 5) {
      uart = hu3;

    }
    if (spi == 6) {
      uart = h1;

    }
    if (spi == 7) {
      uart = h2;

    }
    if (spi == 8) {
      uart = m1;

    }
    if (spi == 9) {
      uart = m2;

    }
    if (spi == 10) {
      uart = s1;

    }
    if (spi == 11) {
      uart = s2;

    }

    //Transmission BitCheck
    if (uart == 0) {
      //0000
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 1) {
      //0001
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 2) {
      //0010
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, HIGH);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 3) {
      //0011
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, HIGH);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 4) {
      //0100
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 5) {
      //0101
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 6) {
      //0110
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, HIGH);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 7) {
      //0111
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, HIGH);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 8) {
      //1000
      digitalWrite (tx1, HIGH);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    else if (uart == 9) {
      //1001
      digitalWrite (tx1, HIGH);
      digitalWrite (tx2, LOW);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
      digitalWrite (tx1, LOW);
      digitalWrite (tx2, HIGH);
      delay (80);
      digitalWrite (en, HIGH);
      delay (80);
      digitalWrite (en, LOW);
      delay (80);
    }
    spi++;
  }
  spi = 0;
  //Update for RTC and Temperature Module
  sreset ();
  delay(520);
}

void sreset () {
  digitalWrite (tx1, LOW);
  digitalWrite (tx2, LOW);
}
