#include "sound.h"
#include "irq.h"
#include "../utils/io.h"
#include "../stdlib/math.h"
#include "../stdlib/types.h"

// Global variable to keep track of the current note being played
static struct note *current_note = NULL;

// PIT interrupt handler
void pit_interrupt_handler()
{
  log("PIT Interrupt", LOG_DEBUG);
  // Check if there's a note to play
  if (current_note != NULL)
  {
    // Calculate the frequency for the current note
    double freq = current_note->note * current_note->octave;
    uint16_t div = (uint16_t)(1193180 / freq);

    // Set the PIT frequency to play the current note
    outb(0x43, 0xB6);                // Command to set the PIT to Mode 3 (square wave generator)
    outb(0x42, (uint8_t)(div));      // Send the low byte
    outb(0x42, (uint8_t)(div >> 8)); // Send the high byte

    // Start playing the sound
    uint8_t tmp = inb(0x61);
    if (tmp != (tmp | 3))
    {
      outb(0x61, tmp | 3);
    }

    // Decrement the note duration
    current_note->duration--;

    // Check if the note duration is complete
    if (current_note->duration <= 0)
    {
      // Stop playing the sound
      nosound();
      // Move to the next note in the array
      current_note++;
    }
  }

  // Send the end of interrupt signal (EOI) to the PIC
  outb(0x20, 0x20);
}

void play_sound(uint32_t nFrequence)
{
  uint32_t Div;
  uint8_t tmp;

  // Set the PIT to the desired frequency
  Div = 1193180 / nFrequence;
  outb(0x43, 0xb6);
  outb(0x42, (uint8_t)(Div));
  outb(0x42, (uint8_t)(Div >> 8));

  // And play the sound using the PC speaker
  tmp = inb(0x61);
  if (tmp != (tmp | 3))
  {
    outb(0x61, tmp | 3);
  }
}

void play_array()
{
  struct note notes[] = {
      {OCTAVE_4, NOTE_C, 10},
      {OCTAVE_4, NOTE_D, 10},
      {OCTAVE_4, NOTE_E, 10},
      {OCTAVE_4, NOTE_F, 10},
  };

  // Set the current_note pointer to the first note in the array
  current_note = &notes[0];

  // Start playing the notes
  while (current_note != NULL)
  {
  }
}

void nosound()
{
  uint8_t tmp = inb(0x61) & 0xFC;
  outb(0x61, tmp);
}
