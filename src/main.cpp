#include <Arduino.h>

String getKey();

const byte numRows = 7;
const byte numCols = 10;
const int debounceTime = 100;

String keymap[numRows][numCols] = {
  {"<T7>","<T19>","<T3>","<T17>","<T2>","<T15>","<T16>","<T8>","<T11>","<T14>"},
  {"<D7>","<D19>","<D3>","<D17>","<D2>","<D15>","<D16>","<D8>","<D11>","<D14>"},
  {"<S7>","<S19>","<S3>","<S17>","<S2>","<S15>","<S16>","<S8>","<S11>","<S14>"},
  {"<?31?>","<?32?>","<?33?>","<?34?>","<?35?>","<?36?>","<?37?>","<?38?>","<SB>","<DB>"},
  {"<S1>","<S18>","<S4>","<S13>","<S6>","<S10>","<S20>","<S5>","<S12>","<S9>"},
  {"<D1>","<D18>","<D4>","<D13>","<D6>","<D10>","<D20>","<D5>","<D12>","<D9>"},
  {"<T1>","<T18>","<T4>","<T13>","<T6>","<T10>","<T20>","<T5>","<T12>","<T9>"}
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


