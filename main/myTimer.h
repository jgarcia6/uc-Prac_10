#ifndef _MY_TIMER0_H_
#define _MY_TIMER0_H_

#define c       261
#define d       294
#define e       329
#define f       349
#define g       391
#define gS      415
#define a       440
#define aS      455
#define b       466

#define cH      523
#define cSH     554
#define dH      587
#define dSH     622
#define eH      659
#define fH      698
#define fSH     740
#define gH      784
#define gSH     830
#define aH      880
// More notes can be found at:
// http://www.intmath.com/trigonometric-graphs/music.php

#define TEMPO   500
#define SILENCE 10

struct note
{
    uint16_t freq;
    uint16_t delay;
};

void timer0Init( void );
void timer1Play(const struct note song[], uint16_t len);
void timer1FreqGen(uint16_t freq);

#endif /* _MY_TIMER0_H_ */