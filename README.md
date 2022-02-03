# Final Year Project - O.R.C.A. - On-water Rubbish Collection robot with Automatic sensing
# Link to GitHub Repository

[LINK TO GIT REPO](https://github.com/LukeDWaller99/Final_Year_Project.git)

----

# Requirements
The specification outlines multiple requirments needed for O.R.C.A to be consider fit for purpose.

1. [ ]
    1. [ ] 

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