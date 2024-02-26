#include <MIDI.h>

// Definir los pines de entrada digital
const int digitalPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int numDigitalPins = 12;

// Definir los pines de entrada analógica
const int analogPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int numAnalogPins = 8;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Configurar pines de entrada digital
  for (int i = 0; i < numDigitalPins; i++) {
    pinMode(digitalPins[i], INPUT_PULLUP);
  }

  // Configurar pines de entrada analógica
  for (int i = 0; i < numAnalogPins; i++) {
    pinMode(analogPins[i], INPUT);
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);  // Iniciar MIDI en todos los canales
}

void loop() {
  // Leer entradas digitales y enviar mensajes MIDI
  for (int i = 0; i < numDigitalPins; i++) {
    int value = digitalRead(digitalPins[i]);
    if (value == LOW) {
      MIDI.sendNoteOn(i + 1, 127, 1);  // Enviar mensaje de nota MIDI (note on)
    } else {
      MIDI.sendNoteOff(i + 1, 0, 1);   // Enviar mensaje de nota MIDI (note off)
    }
    delay(5);  // Pequeña pausa para evitar rebotes
  }

  // Leer entradas analógicas y enviar mensajes MIDI
  for (int i = 0; i < numAnalogPins; i++) {
    int value = analogRead(analogPins[i]);
    MIDI.sendControlChange(i + 1, value / 8, 1);  // Enviar mensaje de cambio de control MIDI
    delay(5);  // Pequeña pausa para evitar rebotes
  }
}
