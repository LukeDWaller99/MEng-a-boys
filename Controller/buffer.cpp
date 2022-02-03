// #include "buffer.h"

// Semaphore spaceInBuffer(buffer_size); // space in buffer
// Semaphore samplesInBuffer(0);         // samples in buffer
// FILE *fp;
// SDBlockDevice mysd(PB_5, PB_4, PB_3, PF_3);
// DigitalOut greenLED(PC_6);

// // constructor
// bufferClass::bufferClass(){

//   t.start();
//   bufferClass::initSD();
//   SDDetector.rise(callback(this, &bufferClass::SDRemoved));
//   SDDetector.fall(callback(this, &bufferClass::initSD));
//   //sd detctor fall?
//   writeThread.start(callback(this, &bufferClass::writeBufferAuto));
//   bufferWriteTick.attach(callback(this, &bufferClass::writeFlag), 15s);
//   flushThread.start(callback(this, &bufferClass::whenToFlush));
//   bufferFlushTick.attach(callback(this, &bufferClass::flushFlag), 60s);
// }

// void bufferClass::writeFlag() { bufferClass::writeThread.flags_set(1); }

// void bufferClass::flushFlag() { bufferClass::flushThread.flags_set(1); }

// void bufferClass::writeBufferAuto() {
//   while (true) {
//     ThisThread::flags_wait_any(1);
//     if (spaceInBuffer.try_acquire_for(1ms) == 0) {
//       PQ->custom.call(printf, "buffer full\n");
//       BEH->setErrorFlag(BUFFER_FULL); // critical error
//     } else {
//       if (bufferLock.trylock_for(1ms) == 0) { // PROTECT THE BUFFER
//         PQ->custom.call(printf, "buffer lock timeout\n");
//         BEH->setErrorFlag(BUFFER_LOCK_TIMEOUT); // critical error
//       } else {
//         if (timeLock.trylock_for(1ms) == 0) { // PROTECT THE DATA
//           PQ->custom.call(printf, "timeLockTimeout\n");
//           BEH->setErrorFlag(TIMER_LOCK_TIMEOUT); // critical error
//         } else {
//           sampledData = bSamp->sampleData;
//           timestamp = time(NULL);
//           dataRecord.realTime = ctime(&timestamp);
//           timeLock.unlock();
//           // copy environmental data
//           dataRecord.LDR = sampledData.LDR;
//           dataRecord.temp = sampledData.temp;
//           dataRecord.pressure = sampledData.pressure;
//         }
//         newIDX = (newIDX + 1) % buffer_size; // increment buffer size
//         buffer[newIDX] = dataRecord;         // update the buffer
//       }
//       bufferLock.unlock();
//     }
//     samplesInBuffer.release();
//   }
//   ThisThread::flags_clear(1);
// }

// void bufferClass::bufferCount() {
//   PQ->custom.call(
//       printf, "Number of environmental data sets in the buffer: %i\n", newIDX);
// }

// void bufferClass::flashGreen() {
//   greenLED = 0;
//   ThisThread::sleep_for(500ms);
//   greenLED = 1;
// }

// void bufferClass::whenToFlush() {
//   while (true) {
//     ThisThread::flags_wait_any(1);
//     flushTiming = duration_cast<seconds>(t.elapsed_time()).count();
//     if ((flushTiming > 60) &&                         // it has been a minute
//         (newIDX == (oldIDX - (buffer_size * 0.1)))) { // flush buffer at 90%
//       PQ->custom.call(printf, "Time recorded = %s\n", ctime(&timestamp));
//       // bufferClass::printBufferContents(); //used to check contents
//       flashGreen();
//       bufferClass::flushBuffer();
//     }
//     if (flushTiming == hourPassed) { // must flush at least once an hour
//       flashGreen();
//       PQ->custom.call(printf, "Time recorded = %s\n", ctime(&timestamp));
//       // bufferClass::printBufferContents(); //used to check contents
//       bufferClass::flushBuffer();
//     }
//   }
//   ThisThread::flags_clear(1);
// }

// void bufferClass::printBufferContents() {
//   while (true) {
//     ThisThread::flags_wait_any(1);
//     if (samplesInBuffer.try_acquire_for(1ms) ==
//         0) {                          // check for samples in the buffer
//       BEH->setErrorFlag(EMPTY_FLUSH); // critical error
//       PQ->custom.call(printf, "no data\n");
//     } else {
//       samplesInBuffer.release();
//       if (bufferLock.trylock_for(1ms) == 0) {   // try to acquire buffer data
//         BEH->setErrorFlag(BUFFER_LOCK_TIMEOUT); // critical error
//         PQ->custom.call(printf, "could not unlock buffer\n");
//       } else {
//         while (runPrint == 1) {   // remain in loop, iterating through data
//           if (oldIDX == newIDX) { // all data from buffer has been copied
//             runPrint = 0;         // terminate
//           } else {
//             samplesInBuffer.try_acquire_for(1ms);
//             oldIDX = (oldIDX + 1) % buffer_size;
//             liveData flushRecord = buffer[oldIDX];
//             PQ->custom.call(printf, "Time recorded = %s\n\t",
//                             flushRecord.realTime);
//             PQ->custom.call(
//                 printf,
//                 "Temperature = %2.1f, \tPressure = %3.1f, \tLDR = %1.2f;\n\r",
//                 flushRecord.temp, flushRecord.pressure, flushRecord.LDR);

//             spaceInBuffer.release(); // another space free
//           }
//         }
//         bufferLock.unlock();
//         t.reset(); // reset flush timer
//       }
//     }
//   }
//   ThisThread::flags_clear(1);
// }

// void bufferClass::flushBuffer() {
//   if (samplesInBuffer.try_acquire_for(1ms) ==
//       0) { // check for data in the buffer
//     PQ->custom.call(printf, "empty buffer\n");
//     BEH->setErrorFlag(BUFFER_LOCK_TIMEOUT); // critical error
//     return;
//   } else {
//     // samplesInBuffer.release();
//     if (bufferLock.trylock_for(1ms) == 0) { // attempt to obtain buffer lock
//       PQ->custom.call(printf, "buffer lock timeout\n");
//       BEH->setErrorFlag(BUFFER_LOCK_TIMEOUT); // critical error
//     } else {
//       FATFileSystem fs("sd", &mysd);
//       FILE *fp = fopen("/sd/environmental_data.txt", "a");

//       if (fp == NULL) {
//         PQ->custom.call(printf, "no sd file\n");
//       } else {
//         while (runFlush == 1) {   // there is still data in the buffer
//           if (oldIDX == newIDX) { // buffer is empty
//             runFlush = 0;         // terminate
//           } else {
//             samplesInBuffer.try_acquire_for(1ms);
//             oldIDX = (oldIDX + 1) % buffer_size; // move to next set of data
//             liveData flushRecord =
//                 buffer[oldIDX]; // obtain data from that position in the buffer
//             fprintf(fp, "Time recorded = %s\n\t", flushRecord.realTime);
//             fprintf(fp,
//                     " \tTemperature = %2.1f, \tPressure = %3.1f,\tLDR = % "
//                     "1.2f;\n\r ",
//                     flushRecord.temp, flushRecord.pressure, flushRecord.LDR);
//             spaceInBuffer.release(); // space in buffer signal
//           }
//         }
//         PQ->custom.call(printf, "Buffer Flushed\n");
//         bufferLock.unlock();
//       }
//     }
//   }
// }

// void bufferClass::fetchLatestRecord() {
//   if (samplesInBuffer.try_acquire_for(1ms) ==
//       0) { // check for samples in the buffer
//     PQ->custom.call(printf, "fetch latest recorded returned no data\n");
//   } else {
//     samplesInBuffer.release();
//     if (bufferLock.trylock_for(1ms) == 0) {   // try to acquire buffer data
//       BEH->setErrorFlag(BUFFER_LOCK_TIMEOUT); // critical error
//       PQ->custom.call(printf, "could not unlock buffer\n");
//     } else {
//       liveData flushRecord = buffer[newIDX]; // get latest set of data
//       PQ->custom.call(printf, "Time recorded = %s\n\t", flushRecord.realTime);
//       PQ->custom.call(
//           printf, "Temperature = %2.1f, \tPressure = %3.1f, \tLDR = %1.2f;\n\r",
//           flushRecord.temp, flushRecord.pressure, flushRecord.LDR);
//       bufferLock.unlock();
//       samplesInBuffer.release();
//     }
//   }
// }

// void bufferClass::initSD() {
//   if (SDDetector == 1) { //-ve logic, sd card is not mounted
//     PQ->custom.call(printf, "sd card not mounted\n");
//     BEH->setErrorFlag(MOUNT_ERROR);
//     greenLED = 0;
//     SDMount = 0;
//   } else { // the sd card is mounted
//     SDMount = 1;
//     greenLED = 1;
//     PQ->custom.call(printf, "sd card is mounted\n");
//   }
// }

// void bufferClass::SDRemoved(){
//     greenLED = 0;
//     SDMount = 0;
//     PQ->custom.call(printf, "sd card not mounted\n");
//     BEH->setErrorFlag(MOUNT_ERROR);
// }