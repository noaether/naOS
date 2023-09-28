#ifndef CLOCKS_H
#define CLOCKS_H

#define PIT_CHANNEL_0 0x40
#define PIT_CHANNEL_1 0x41
#define PIT_COMMAND_PORT 0x43

/**
 * Initializes the Programmable Interval Timer (PIT) with the given frequency.
 *
 * @param hz The frequency to set the PIT to.
 *
 * @return no it doesnt
 *
 * @remarks The PIT is set in mode 3 (square wave generator) and channel 0 is used.
 * The frequency must be between 18 and 1000 Hz, otherwise the function returns without doing anything.
 * This function disables interrupts while setting up the PIT and enables them afterwards.
 */
void pit_init(int hz);

/**
 * Sets the frequency of the Programmable Interval Timer (PIT).
 *
 * @param hz The desired frequency in hertz.
 */
void set_pit(int hz); // alias for pit_init

#define CURRENT_YEAR 2023 // Change this each year!

char *read_rtc();

#endif // CLOCKS_H