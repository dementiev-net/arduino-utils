#include <EEPROM.h>

int i = 0;
int x = 0;
String val = "";
int ch = 0;
int adress = 0;
int number = 0;

void setup()
{
  Serial.begin(9600);  //Скорость порта
  Serial.println("To erase all EEPROM block input in the Port Monitor window: clear");
  Serial.println("To view the contents of the all EEPROM block input in the Port Monitor window: read");
  Serial.println("To write a new value to a single cell in the EEPROM input in the Port Monitor window: write 23,127");
  Serial.println("where 23 - cell address, and 127 - the contents");
}

void loop()
{
  if (Serial.available())
  {
    //Сохраняем строку в переменную val
    while (Serial.available())
    {
      ch = Serial.read();
      val += char(ch);
      delay(20);
    }
    Serial.println(val);
  }
  if (val.indexOf("read") > -1) ReadMemory();
  if (val.indexOf("clear") > -1) ClearMemory();
  if (val.indexOf("write") > -1) WriteMemory();
  val = "";
}

void ReadMemory()
{
  for (i = 0; i < 64; i++)
  {
    for (x = 0; x < 16; x++)
    {
      Serial.print(EEPROM.read((i * 16) + x)); Serial.print(" ");
    }
    Serial.println(" ");
  }
  Serial.println("OK");
}

void ClearMemory()
{
  for (i = 0; i < 1024; i++)
  {
    EEPROM.write(i, 255);
    delay(4);
  }
  Serial.println("OK");
}

void WriteMemory()
{
  val.replace("write ", "");
  adress = (val.substring(0, val.indexOf(","))).toInt();
  number = (val.substring(val.indexOf(",") + 1)).toInt();
  EEPROM.write(adress, number);
  Serial.print("Result: ");
  Serial.print(adress);
  Serial.print(",");
  Serial.println(EEPROM.read(adress));
  Serial.println("OK");
}
