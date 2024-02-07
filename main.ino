#include <MIDIUSB.h>

const int buttonPin1 = 3;             // Button untuk nada C4
const int buttonPin2 = 4;             // Button untuk nada D4
const int encoderButtonPin = 5;       // Tombol encoder untuk start/stop
const int encoderPinA = 6;            // Pin A rotary encoder
const int encoderPinB = 7;            // Pin B rotary encoder
const int additionalEncoderPinA = 8;  // Pin A rotary encoder tambahan
const int additionalEncoderPinB = 9;  // Pin B rotary encoder tambahan
const int scaleCount = 32;            // Jumlah total skala
int currentScaleIndex = 0;            // Indeks skala yang sedang dipilih
int currentNoteIndex = 0;             // Indeks nota yang sedang dipilih dalam skala
int currentNote = 60;                 // Nada awal (C4)
int scales[][15] = {
  { 0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24 },     // Mayor
  { 0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22, 24 },     // Minor
  { 0, 2, 4, 5, 6, 8, 10, 12, 14, 16, 17, 18, 20, 22, 24 },     // Arabian
  { 0, 1, 5, 7, 8, 12, 13, 17, 19, 20, 24, 25, 29, 31, 32 },    // Japanese
  { 0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26, 29, 31 },        // Hungarian Minor
  { 0, 4, 5, 7, 9, 12, 16, 17, 19, 21, 24, 28, 31, 33 },        // Hungarian Major
  { 0, 1, 5, 7, 8, 12, 13, 17, 19, 20, 24, 25 },                // Spanish
  { 0, 1, 5, 7, 8, 12, 13, 17, 19, 20, 24, 25, 29, 31 },        // Gipsy
  { 0, 1, 5, 7, 8, 12, 13, 17, 19, 20, 24, 25, 29, 31, 32 },    // Balinese
  { 0, 1, 5, 7, 8, 9, 13, 17, 19, 20, 21, 25, 29, 31 },         // Persian
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },         // Chromatic
  { 0, 4, 7, 8, 9, 12, 16, 19, 20, 21, 24, 28 },                // Blues Minor
  { 0, 4, 7, 8, 9, 12, 13, 17, 19, 20, 24, 28, 31, 33, 36 },    // Blues Major
  { 0, 2, 5, 7, 9, 12, 14, 17, 19, 21, 24, 26, 29, 31 },        // Chinese Scale
  { 0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26, 28, 31 },        // Hindu Scale
  { 0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26, 28, 31 },        // Jazz Minor
  { 0, 4, 7, 9, 12, 16, 19, 21, 24, 28, 31, 33, 36, 40 },       // Pentatonic Minor
  { 0, 2, 5, 7, 9, 12, 14, 17, 19, 21, 24, 26, 29, 31 },        // Pentatonic Major
  { 0, 2, 4, 7, 9, 10, 14, 16, 19, 21, 22, 26, 28, 31 },        // Arabian 2
  { 0, 1, 4, 7, 9, 12, 14, 16, 19, 21, 24, 25, 28, 31 },        // Japanese 2
  { 0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26, 28, 31, 33 },    // Bebop
  { 0, 4, 9, 14, 21, 24, 28, 33, 36, 40, 45, 50, 57, 60, 64 },  // Diminished
  { 0, 1, 5, 9, 12, 14, 17, 21, 24, 26 },                       // Alfered Pentatonic
  { 0, 1, 4, 5, 7, 9, 10, 14, 16, 19, 21, 22, 24, 28, 31 },     // Spanish 8 tones
  { 0, 1, 5, 7, 9, 12, 14, 16, 19, 21, 24, 25, 28, 31 },        // Jewish
  { 0, 1, 4, 7, 9, 10, 14, 16, 19, 21, 22, 26, 28, 31, 34 },    // Oriental
  { 0, 4, 5, 9, 12, 14, 17, 21, 24, 26, 28, 33 },               // Augmented
  { 0, 2, 7, 9, 12, 14, 17, 19, 21, 26, 28, 31 },               // Egyptian
  { 0, 2, 4, 7, 9, 10, 14, 16, 19, 21, 22, 26, 28, 31, 34 },    // Lydian
  { 0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26, 28, 31, 34 },    // Mixolydian
  { 0, 2, 4, 7, 9, 12, 14, 17, 19, 21, 24, 26, 28, 31, 33 },    // Aeolian
  { 0, 1, 4, 7, 9, 10, 14, 17, 19, 21, 22, 26, 28, 31, 34 },    // Locrian
  { 0, 1, 3, 7, 8, 12, 13, 15, 19, 20, 24, 25, 27, 31, 32 }     // Javanese
};

const char* scaleNames[] = {
  "Mayor",
  "Minor",
  "Arabian",
  "Japanese",
  "Hungarian Minor",
  "Hungarian Major",
  "Spanish",
  "Gipsy",
  "Balinese",
  "Chromatic",
  "Blues Minor",
  "Blues Major",
  "Chinese Scale",
  "Hindu Scale",
  "Jazz Minor",
  "Pentatonic Minor",
  "Pentatonic Major",
  "Arabian 2",
  "Japanese 2",
  "Bebop",
  "Diminished",
  "Alfered Pentatonic",
  "Spanish 8 tones",
  "Jewish",
  "Oriental",
  "Augmented",
  "Egyptian",
  "Lydian",
  "Mixolydian",
  "Aeolian",
  "Locrian",
  "Javanese"
};


bool lastButtonState1 = HIGH;
bool lastButtonState2 = HIGH;
bool lastEncoderButtonState = HIGH;
bool lastEncoderPinAState = HIGH;
bool lastEncoderPinBState = HIGH;
bool lastAdditionalEncoderValue = HIGH;
bool playing = false;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(encoderButtonPin, INPUT_PULLUP);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(additionalEncoderPinA, INPUT_PULLUP);
  pinMode(additionalEncoderPinB, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool buttonState1 = digitalRead(buttonPin1);
  bool buttonState2 = digitalRead(buttonPin2);

  if (buttonState1 == LOW && lastButtonState1 == HIGH) {
    playNote(60);  // Nada C4
    currentNote = 60;
  }

  if (buttonState2 == LOW && lastButtonState2 == HIGH) {
    playNote(62);  // Nada D4
    currentNote = 62;
  }

  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;

  bool encoderButtonState = digitalRead(encoderButtonPin);
  bool encoderPinAState = digitalRead(encoderPinA);
  bool encoderPinBState = digitalRead(encoderPinB);

  if (encoderButtonState == LOW && lastEncoderButtonState == HIGH) {
    if (playing) {
      playing = false;
      Serial.println("Scale Stopped");
    } else {
      playing = true;
      Serial.println("Scale Started");
      playScale(scales[currentScaleIndex]);
    }
  }

  if (encoderPinAState != lastEncoderPinAState) {
    if (encoderPinAState == LOW) {
      if (encoderPinBState == LOW) {
        // Putar ke kanan
        currentScaleIndex = (currentScaleIndex + 1) % scaleCount;
        printCurrentScale();
      } else {
        // Putar ke kiri
        currentScaleIndex = (currentScaleIndex - 1 + scaleCount) % scaleCount;
        printCurrentScale();
      }
    }
  }

  lastEncoderButtonState = encoderButtonState;
  lastEncoderPinAState = encoderPinAState;
  lastEncoderPinBState = encoderPinBState;

  // delay(10);

  int additionalEncoderValue = digitalRead(additionalEncoderPinA);
  if (additionalEncoderValue != lastAdditionalEncoderValue) {
    if (additionalEncoderValue == LOW) {
      if (digitalRead(additionalEncoderPinB) == LOW) {
        // Putar ke kanan
        currentNoteIndex = (currentNoteIndex + 1) % 15;
      } else {
        // Putar ke kiri
        currentNoteIndex = (currentNoteIndex - 1 + 15) % 15;
      }
      playNoteByIndex(currentScaleIndex, currentNoteIndex);
    }
  }
  lastAdditionalEncoderValue = additionalEncoderValue;

  // delay(10);
}

void playNoteByIndex(int scaleIndex, int noteIndex) {
  int note = currentNote + scales[scaleIndex][noteIndex];
  playNote(note);
}

void playNote(int note) {
  noteOn(0, note, 64);
  MidiUSB.flush();
  delay(300);
  noteOff(0, note, 64);
  MidiUSB.flush();
}

void playScale(int scale[]) {
  for (int i = 0; i <= 15; ++i) {
    playNote(currentNote + scale[i]);
  }
}

void printCurrentScale() {
  Serial.print("Current Scale (");
  Serial.print(scaleNames[currentScaleIndex]);
  Serial.print("): ");
  for (int i = 0; i <= 15; ++i) {
    Serial.print(currentNote + scales[currentScaleIndex][i]);
    Serial.print(" ");
  }
  Serial.println();
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = { 0x0B, 0xB0 | channel, control, value };
  MidiUSB.sendMIDI(event);
}

void programChange(byte channel, byte program) {
  midiEventPacket_t message = { 0x0C, 0xC0 | channel, program, 0 };
  MidiUSB.sendMIDI(message);
}

void channelPressure(byte channel, byte pressure) {
  midiEventPacket_t message = { 0x0D, 0xD0 | channel, pressure, 0 };
  MidiUSB.sendMIDI(message);
}

void aftertouch(byte channel, byte note, byte pressure) {
  midiEventPacket_t message = { 0x02, 0xA0 | channel, note, pressure };
  MidiUSB.sendMIDI(message);
}

void polyAftertouch(byte channel, byte note, byte pressure) {
  midiEventPacket_t message = { 0x02, 0xD0 | channel, note, pressure };
  MidiUSB.sendMIDI(message);
}
