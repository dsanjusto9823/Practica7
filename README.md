# Practica7: Buses de Comunicacion III (S2I)
## Objetivo:
El objetivo de esta practica es comprender el funcionamiento del protocolo de comunicación, que se utliza para transferir señales digitales entre dispositivos.
En esta práctica se realizaran dos ejercicios en los cuales uno reproduce un audio ya dentro de la memoria intena del ESP32 y el segundo hace lo mismo pero desde un archivo .wav almacenado en una tarjeta SD externa. 
## Apartado 1:
En este apartado usamos la memoria interna del ESP32 para reproducir el audio. 
Los materiales usados han sido
1. ESP32-S3
2. Placa de conexión de audio MAX98357
3. Altavoz
![image](https://github.com/user-attachments/assets/7d275fcb-95ae-4be8-a38f-4dff498f9ef8)
![image](https://github.com/user-attachments/assets/a4babf49-ae14-4c8f-80eb-a74a8f6e9bb4)
### Código usado:
```
#include <Arduino.h>
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"  // Este archivo debe contener el array con el audio AAC

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup() {
  Serial.begin(115200);

  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out->SetGain(0.125);
  out->SetPinout(26, 25, 22);  // DIN, BCLK, LRC

  aac->begin(in, out);
}

void loop() {
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac->stop();
    Serial.println("Sound Generator");
    delay(1000);
  }
}
```
### Funcionamiento del código:
Este código reproduce el archivo de audio almacenado dentro de la memoria interna del ESP32 usada en este apartado. 
###Salidas:
En el puerto serie se muestra: 
```
Sound Generator
Sound Generator
```
![image](https://github.com/user-attachments/assets/bcd29c6e-1614-4358-9b69-f83ffa5b2183)


## Apartado 2:
En este apartado queremos hacer lo mismo que en el apartado 1 lo único que ahora el archivo .wav se almacena en una tarjeta SD y tiene que ser escogido por los alumnos, descargado y guardado en la tarjeta SD. 
Los materiales usados han sido
1. ESP32-S3
2. Placa de conexión de audio MAX98357
3. Altavoz
4. Tarjeta SD
### Código usado:
```
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
```
### Funcionamiento del código:
Este código funciona igual que en el apartado 1, la diferencia es que este, inicializa la SD, configura la I2S y reproduce el archivo WAV. 
###Salidas:
En el puerto serie se muestra: 
```
info WAV file detected streaminfo 44100 Hz, 16-bit stereo bitrate 1411 kbps
```

