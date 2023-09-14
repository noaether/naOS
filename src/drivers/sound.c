#include "sound.h"

struct note CMajScale[] = {
    {OCTAVE_4, NOTE_C, 0},
    {OCTAVE_4, NOTE_D, 10},
    {OCTAVE_4, NOTE_E, 10},
    {OCTAVE_4, NOTE_F, 10},
    {OCTAVE_4, NOTE_G, 10},
    {OCTAVE_4, NOTE_A, 10},
    {OCTAVE_4, NOTE_B, 10},
    {OCTAVE_5, NOTE_C, 20},
    {OCTAVE_5, NOTE_D, 10},
    {OCTAVE_5, NOTE_E, 10},
    {OCTAVE_5, NOTE_F, 10},
    {OCTAVE_5, NOTE_G, 10},
    {OCTAVE_5, NOTE_A, 10},
    {OCTAVE_5, NOTE_B, 10},
    {OCTAVE_6, NOTE_C, 20},
    {OCTAVE_5, NOTE_B, 10},
    {OCTAVE_5, NOTE_A, 10},
    {OCTAVE_5, NOTE_G, 10},
    {OCTAVE_5, NOTE_F, 10},
    {OCTAVE_5, NOTE_E, 10},
    {OCTAVE_5, NOTE_D, 10},
    {OCTAVE_5, NOTE_C, 20},
    {OCTAVE_4, NOTE_B, 10},
    {OCTAVE_4, NOTE_A, 10},
    {OCTAVE_4, NOTE_G, 10},
    {OCTAVE_4, NOTE_F, 10},
    {OCTAVE_4, NOTE_E, 10},
    {OCTAVE_4, NOTE_D, 10},
    {OCTAVE_4, NOTE_C, 20},
    {OCTAVE_4, NOTE_E, 10},
    {OCTAVE_4, NOTE_G, 10},
    {OCTAVE_5, NOTE_C, 20},
    {OCTAVE_5, NOTE_E, 10},
    {OCTAVE_5, NOTE_G, 10},
    {OCTAVE_6, NOTE_C, 20},
    {OCTAVE_5, NOTE_G, 10},
    {OCTAVE_5, NOTE_E, 10},
    {OCTAVE_5, NOTE_C, 20},
    {OCTAVE_4, NOTE_G, 10},
    {OCTAVE_4, NOTE_E, 10},
    {OCTAVE_4, NOTE_C, 20},
    {0, 0, 0} // End of array
};

struct note mary_had_a_little_lamb[] = {
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_C, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 2},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_G, 4},
    {OCTAVE_4, NOTE_G, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_C, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 2},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_G, 4},
    {OCTAVE_4, NOTE_G, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_C, 4},
    {0, 0, 0} // End of array
};

struct note boot_melody[] = {
    {OCTAVE_4, NOTE_C, 10},
    {OCTAVE_4, NOTE_E, 10},
    {OCTAVE_4, NOTE_FS, 10},
    {OCTAVE_4, NOTE_AS, 10},
    {OCTAVE_5, NOTE_C, 10},
};

struct note current_array[] = {
    {OCTAVE_4, NOTE_C, 10},
    {OCTAVE_4, NOTE_E, 10},
    {OCTAVE_4, NOTE_FS, 10},
    {OCTAVE_4, NOTE_AS, 10},
    {OCTAVE_5, NOTE_C, 10},
    {0, 0, 0},
};

static struct note *current_note = NULL;
static int current_note_index = -1; // Keep track of the current note index
static int sound_playing = 0;               // Flag to indicate whether a sound is currently playing
void play_array()
{
  set_pit(20);
  sound_playing = 1; // Set sound playing flag
  // Set the current_note pointer to the first note in the array
  current_note = &current_array[0];
  current_note_index = 0;
}

void pit_interrupt_handler()
{
  if (current_note == NULL)
  {
    return;
  }
  // Check if there's a note to play and sound is currently playing
  if (current_note != NULL && sound_playing)
  {
    if (current_note->note == 0 && current_note->octave == 0 && current_note->duration == 0)
    {
      if (current_note_index == 0)
      {
        current_note_index++;
      }
      else
      {
        nosound();
        current_note = NULL;
        asm volatile("int $0x29");
        return;
      }
    }
    // Calculate the frequency for the current note
    double freq = current_note->note * current_note->octave;
    uint16_t div = (uint16_t)(1193180 / freq);

    // Set the PIT frequency to play the current note
    // https://wiki.osdev.org/Programmable_Interval_Timer#I.2FO_Ports
    // https://wiki.osdev.org/Programmable_Interval_Timer#Mode_3_.E2.80.93_Square_Wave_Generator
    outb(0x43, 0xB6);                       // Command to set the PIT to Mode 3 (square wave generator)
    outb(0x42, (uint8_t)(div & 0xFF));      // Send the low byte
    outb(0x42, (uint8_t)(div >> 8) & 0xFF); // Send the high byte

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
      current_note_index++; // Move to the next note in the array

      // Otherwise, set the current note to the next note in the array
      current_note = &current_array[current_note_index];
    }
  }

  // Send the end of interrupt signal (EOI) to the PIC
  outb(0x20, 0x20);
}
void nosound()
{
  sound_playing = 0;

  uint8_t tmp = inb(0x61) & 0xFC;
  outb(0x61, tmp);
}