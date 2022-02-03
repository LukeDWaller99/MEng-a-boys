// /**
// @file buffer.h
// buffer and sd card header file
// Author - Noah Harvey
// **/

// #ifndef __FIFO_BUFFER__
// #define __FIFO_BUFFER__

// #include <FATFileSystem.h>
// #include <InterruptIn.h>
// #include <Mutex.h>
// #include <SDBlockDevice.h>
// #include <Semaphore.h>
// #include <ctime>
// #include <mbed.h>


// using namespace std;

// /// macro so define the size of the buffer
// #define buffer_size 100 ///< define buffer size
// // define the pin for the sd card

// /**
// buffer class with sd card functionality and dedicated threads for writig to the
// buffer flushing the sd card
// **/
// class bufferClass {

// private:
//   typedef void (*funcPointer_t)(void);
//   // mutex locks, tickers, timers,
//   Mutex bufferLock;       ///< mutex buffer lock to protect data in buffer
//   Mutex timeLock;         ///< mutex time lock to protect time
//   Ticker bufferWriteTick; ///< ticker for writing into the buffer every 15s
//   Ticker bufferFlushTick; ///< ticker for checking buffer capacity every 60s
//   Timer t;                ///< timer for tracking time in between flushes
//   time_t timestamp;       ///< to obtain real time
//   InterruptIn SDDetector; ///< to check if sd card is mounted

//   /**
//   setting flag to initiate writing data into the buffer
//   **/
//   void writeFlag();
//   Thread writeThread;

//   /**
//   setting flag to initiate flush to sd card
//   **/
//   void flushFlag();
//   Thread flushThread;

//   /**
//     waits for the write flag to indicate that there are new samples to be
//     written into the buffer, then adds the environmental data into the next
//     space
//     **/
//   void writeBufferAuto();
//   /// number of slots in buffer, both used to track position and next space
//   /// available.
//   unsigned int newIDX =
//       buffer_size - 1; ///< track number of data sets in the buffer
//   unsigned int oldIDX = buffer_size - 1;

//   /**
//   waits for the flush flag and checks if a minute has passed since the last
//   flush and that buffer is at 90% capacity. otherwise it will flush after an
//   hour.
//   **/
//   void whenToFlush();
//   float flushTiming;          ///< time since last flush
//   float hourPassed = 59 * 60; ///< hour timer

// public:
//   /**
//      Construct ErrorHandler, sampler and CustomQueue objects. This constructor
//      must be given a pointer to each in order. ErrorHandler - outputs errors
//      over serial. sampler - obtain new enviromental samples. CustomQueue -
//      outputs additional information over serial.
//      **/
//   bufferClass();

//   /**
//   Structure for holding sample data, sampled every 10s, and time and data that
//   the data was obtained.
//       @param LDR float value of light level
//       @param temp float value of temperate
//       @param pressue float value of pressure
//       @param realTime char - time and data
//   **/
//   struct liveData {
//     float LDR;
//     float temp;
//     float pressure;
//     char *realTime;
//   };

//   samples sampleData;                // sampled values, every 10s
//   liveData buffer[buffer_size];      ///< buffer of size defined
//   liveData dataRecord;               ///< for holding data in the buffer
//   liveData printRecord[buffer_size]; ///< for printing data to serial

//   /**
//   return the newest sample set writtin into the buffer along with the time and
//   data so it can be output to the serial
//       @param newIDX the position of latest set of data to be written into the
//   buffer
//   **/
//   void fetchLatestRecord();

//   /**
//   flush all contents of the buffer to the sd card
//       @param runFlush 1 to continue iterating through all samples sets, 0 to
//   terminate as there is no data left
//   **/
//   void flushBuffer();
//   int runFlush = 1;

//   /**
//   return the number of samples in the buffer to the serial
//       @param newIDX holds the number of datasets in the buffer
//   **/
//   void bufferCount();

//   /**
//   Outputs the contents of the buffer to serial. This was used for testing
//   purposes.
//       @param runPrint 1 to continue iteration until empty, 0 to terminate when
//   empty.
//   **/
//   void printBufferContents();
//   int runPrint = 1;

//   /**
//   Initiate the sd card by checking that it is mounted.
//       @param SDDetector to fire an interrupt when the sd card is not mounted,
//   calling initSD to check
//       @param SDMount 1 - sd card is mounted, 0 - the sd card is not mounted
//   **/
//   void initSD();
//   bool SDMount;

// /**
// when the interrupt pin for the sd card falls, check the sd card is mounted
// **/
//   void SDRemoved();

//   /**
//   upon flushing of the buffer to the sd card, the green led shall flash
//   **/
//   void flashGreen(); // for showing that the sd card is being flushed

//   // destructor
//   ~bufferClass();
// };

// #endif
