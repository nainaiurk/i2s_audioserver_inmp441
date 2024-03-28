#include <Arduino.h>
#include "AudioTools.h"

AudioWAVServer server("(Nai)9","12345678");

I2SStream i2sStream;
ConverterFillLeftAndRight<int16_t> filler(RightIsEmpty);

void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // start i2s input with default configuration
  Serial.println("starting I2S...");
  auto config = i2sStream.defaultConfig(RX_MODE);
  config.i2s_format = I2S_STD_FORMAT;
  config.sample_rate = 41000;
  config.channels = 2;
  config.bits_per_sample = 16;
  i2sStream.begin(config);
  Serial.println("I2S started");

  // start data sink
  server.begin(i2sStream, config, &filler);
}

void loop() {
  server.copy();  
}