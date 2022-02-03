# Microcontroller Loop pedal
# Link to GitHub Repository

[LINK TO GIT REPO](https://github.com/LukeDWaller99/Loop-pedal.git)

This project is a Microcontroller Based Loop pedal. 

----

# Requirements
The specification outlines multiple requirments needed for the loop pedal to be consider fit for purpose.

1. [ ] The looper must be able to record in real time and store the data onto the DRAM chip.
    1. [ ] Sampler must have appropriate input level (using some form of amplifier).
    2. [ ] Sampler must run at 44kHz and collect data from an input successfully.
    3. [ ] This sampled data must be stored on the DRAM chip.
2. [ ] The looper must be able to playback the recording at its proper recorded rate
    1. [ ] The output must produce an audible signal (unsing some for of amplifier).
    2. [ ] The output must be produced in real time and recreate the input exactly.
    3. [ ] The outputted loop must have been read from the DRAM chip.
3. [ ] The looper must be able to overdub the current recording with a new recording that contains both the old recording and the new one played over the top.
    1. [ ] Sampler must take in data at a suitable rate (see 1) and record this ontop of the current track to create a new track.

----

## Dependancies

The main.cpp file contains all the instantiations needed in the correct order. However, several of the modules of this project can be used as standalone classes. To ensure that these classes are instantiated correctly, the dependencies are listed below.

* Sampler
    * `<mbed.h>`
	* `<Mutex.h>`
	* `<Ticker.h>`

* DRAM
	* `<mbed.h>`

* Output
    * `<mbed.h>`
    * `"DRAM.h"`

----

## Error Codes
In the event of an error, the Error Handler will automatically perform actions based on the severity:

**Luke Waller**

*Authored*
    - Sampler
    - DRAM
    - ErrorHandler

----
