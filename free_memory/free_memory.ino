void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(memoryFree());
  delay(1000);

}

extern int __bss_end;
extern void *__brkval;
// свободное ОЗУ
int memoryFree()
{
  int freeValue;
  if ((int)__brkval == 0)
    freeValue = ((int)&freeValue) - ((int)&__bss_end);
  else
    freeValue = ((int)&freeValue) - ((int)__brkval);
  return freeValue;
}
