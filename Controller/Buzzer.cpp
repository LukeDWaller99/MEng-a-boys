#include "Buzzer.h"

Buzzer::Buzzer(PinName pin) : buzzer(pin) {

    setNote();
    stop();

}

void Buzzer::setNote(const char* note, OCTAVE octave){
    buzzer.period_us(notePeriod(note, octave));
}

void Buzzer::buzz(float amount){
    buzzer.write(amount);
}

void Buzzer::stop(){
    buzzer.write(0);
}

void Buzzer::operator = (const char* note){
    setNote(note);
}

void Buzzer::operator = (int on_off){
    if (on_off == 1) {
    buzz();
    } else {
    stop();
    }
}

void Buzzer::operator=(float time){
    buzz(time);
}

void Buzzer::chime(int delay, const char* note1, const char* note2, const char* note3, OCTAVE octave){

    if ((delay < 25000) || (delay > 1000000)){
        delay = 100000;
    }

    setNote(note1, octave);
    buzz();
    wait_us(delay);
    stop();
    wait_us(delay);
    setNote(note2, octave);
    buzz();
    wait_us(delay);
    stop();
    wait_us(delay);
    setNote(note3, octave);
    buzz();
    wait_us(delay);
    stop();
    wait_us(delay);
}


double Buzzer::notePeriod(const char* note, OCTAVE octave){
    
    volatile uint8_t frequencyIndex = noteOffset(note);
    volatile double frequency = frequencyOfNote[frequencyIndex];

    switch (octave) {
    case LOWER:
        frequency *= 0.5;
        break;
    case MIDDLE:
        break;
    case HIGHER:
        frequency *= 2;
        break;
    default:
        break;
    }
    return  1000000 / frequency;
}

uint8_t Buzzer::noteOffset(const char* noteStr){
    
    uint8_t resultant;
    switch (noteStr[0]) {
    case 'A':
        resultant = (noteStr[1]=='#') ? 1 : 0;
        break;
    case 'B':
        resultant = 2;
        break;
    case 'C':
        resultant = (noteStr[1]=='#') ? 4 : 3; 
        break;
    case 'D':
        resultant = (noteStr[1]=='#') ? 6 : 5;                    
        break;
    case 'E':
        resultant = 7;
        break;
    case 'F':
        resultant = (noteStr[1]=='#') ? 9 : 8;                                           
        break;
    case 'G':
        resultant = (noteStr[1]=='#') ? 11 : 10;  
        break;
    default:
        resultant = 0;                   
        break;
    }
    return resultant;
}
