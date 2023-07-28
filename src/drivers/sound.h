#ifndef SOUND_H
#define SOUND_H

#include "../stdlib/types.h"

#define OCTAVE_0 0
#define OCTAVE_1 1
#define OCTAVE_2 2
#define OCTAVE_3 3
#define OCTAVE_4 1
#define OCTAVE_5 2
#define OCTAVE_6 4
#define OCTAVE_7 8
#define OCTAVE_8 16

#define NOTE_C 261.63  // Frequency for C (261.63 Hz)
#define NOTE_CS 277.18 // Frequency for C# (277.18 Hz)
#define NOTE_D 293.66  // Frequency for D (293.66 Hz)
#define NOTE_DS 311.13 // Frequency for D# (311.13 Hz)
#define NOTE_E 329.63  // Frequency for E (329.63 Hz)
#define NOTE_F 349.23  // Frequency for F (349.23 Hz)
#define NOTE_FS 369.99 // Frequency for F# (369.99 Hz)
#define NOTE_G 392.00  // Frequency for G (392.00 Hz)
#define NOTE_GS 415.30 // Frequency for G# (415.30 Hz)
#define NOTE_A 440.00  // Frequency for A (440.00 Hz)
#define NOTE_AS 466.16 // Frequency for A# (466.16 Hz)
#define NOTE_B 493.88  // Frequency for B (493.88 Hz)

struct note
{
  uint8_t octave;
  double note;
  uint32_t duration;
};

void play_sound(uint32_t nFrequence);

void play_array();
void nosound();

#endif // SOUND_H