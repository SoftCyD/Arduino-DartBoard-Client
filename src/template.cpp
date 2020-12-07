#include <Arduino.h>

String getKey();

const byte numRows = 7;
const byte numCols = 10;
const int debounceTime = 100;

// Open terminal, take paper and pen, push each zone, note each target and ?xx?
// replace each ?xx? by the target value S1 to S20, D1 to D20, T1 to T20, SB, DB
// keep '<' before and '>' after value 
// then re-upload and test again each value
String keymap[numRows][numCols] = {
  {"<?01?>","<?02?>","<?03?>","<?04?>","<?05?>","<?06?>","<?07?>","<?08?>","<?09?>","<?10?>"},
  {"<?11?>","<?12?>","<?13?>","<?14?>","<?15?>","<?16?>","<?17?>","<?18?>","<?19?>","<?20?>"},
  {"<?21?>","<?22?>","<?23?>","<?24?>","<?25?>","<?26?>","<?27?>","<?28?>","<?29?>","<?30?>"},
  {"<?31?>","<?32?>","<?33?>","<?34?>","<?35?>","<?36?>","<?37?>","<?38?>","<?39?>","<?40?>"},
  {"<?41?>","<?42?>","<?43?>","<?44?>","<?45?>","<?46?>","<?47?>","<?48?>","<?99?>","<?50?>"},
  {"<?51?>","<?52?>","<?53?>","<?54?>","<?55?>","<?56?>","<?57?>","<?58?>","<?59?>","<?60?>"},
  {"<?61?>","<?62?>","<?63?>","<?64?>","<?65?>","<?66?>","<?67?>","<?68?>","<?69?>","<?70?>"}
};
byte rowPins[numRows] = {A0, A1, A2, A3, A4, A5,2};
byte colPins[numCols] = {12, 11, 10, 9, 8 ,7, 6, 5, 4, 3};

void setup()
{
  Serial.begin(115200);
  
  for (int row = 0; row < numRows; row++)
  {
    pinMode(rowPins[row],INPUT); 
    digitalWrite(rowPins[row],HIGH);
  }
  for (int column = 0; column < numCols; column++)
  {
    pinMode(colPins[column],OUTPUT);
    digitalWrite(colPins[column],HIGH); 
  }
}

void loop()
{
  String key = getKey();
  if( key != 0) {
    Serial.print(key);
  }
}

String getKey()
{

  String key = "";

  for(int column = 0; column < numCols; column++)
  {
    digitalWrite(colPins[column],LOW);
    for(int row = 0; row < numRows; row++)
    {
      if(digitalRead(rowPins[row]) == LOW)
      {
        delay(debounceTime);
        while(digitalRead(rowPins[row]) == LOW);
        key = keymap[row][column];
      }
    }
    digitalWrite(colPins[column],HIGH);
  }
  return key;
}


