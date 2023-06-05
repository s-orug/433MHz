#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);

const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char receivedData[256]; 
    radio.read(&receivedData, sizeof(receivedData));

    Serial.print("Received Data: ");
    Serial.println(receivedData);
  }
}
