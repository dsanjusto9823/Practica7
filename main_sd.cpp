#include <Arduino.h>
#include <Audio.h>
#include <SD.h>
#include <FS.h>

// Pines
#define SD_CS     5
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_SCK  18

#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC  26

Audio audio;

void setup() {
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  Serial.begin(115200);
  SD.begin(SD_CS);

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(10);  // Rango: 0 a 21

  audio.connecttoFS(SD, "/Ensoniq-ZR-76-01-Dope-77.wav");  // Cambia el nombre si es necesario
}

void loop() {
  audio.loop();
}
