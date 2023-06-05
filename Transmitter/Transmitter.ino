#include <SPI.h>
#include <SD.h>
#include <RF24.h>

File dataFile;
const int chipSelect = 10;
RF24 radio(9, 10);

const uint64_t pipe = 0xE8E8F0F0E1LL; // pipe address

void setup()
{
  Serial.begin(9600);

  if (!SD.begin(chipSelect))
  {
    Serial.println("SD card initialization failed!");
    return;
  }

  radio.begin();
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_HIGH);
}

void loop()
{
  dataFile = SD.open("data.csv");
  if (dataFile)
  {
    while (dataFile.available())
    {
      String line = dataFile.readStringUntil('\n');
      line.trim();

      radio.write(line.c_str(), line.length());

      Serial.print("Transmitted Data: ");
      Serial.println(line);

      delay(1000);
    }

    dataFile.close();
    Serial.println("*******Completed the Transmission*******")
    while (true)
    {
    }
  }
  else
  {
    Serial.println("Error opening data.csv");
  }
}
