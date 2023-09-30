#ifndef SOUND_H
#define SOUND_H

#include "irq.h"
#include "clocks.h"
#include "../utils/io.h"

#include <stdint.h>
#include <stddef.h>

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
  float octave;
  float note;
  uint8_t duration;
} __attribute__((packed));

/**
 * Interrupt handler for the Programmable Interval Timer (PIT) used to play sound notes.
 * If there's a note to play and sound is currently playing, it calculates the frequency for the current note,
 * sets the PIT frequency to play the current note, starts playing the sound, decrements the note duration,
 * and checks if the note duration is complete. If the note duration is complete, it moves to the next note in the array.
 *
 * @return void
 */
void pit_interrupt_handler();

/**
 * Copies the given array of notes to the current array and sets the sound playing flag.
 *
 * @param new_array The array of notes to be played.
 * @param length The length of the array.
 */
void play_array(struct note new_array[], uint8_t length);

/**
 * @brief Stops the sound being played and sets the current note to NULL.
 *
 */
void nosound();

#endif // SOUND_H