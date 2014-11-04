#ifndef SCORE_H
#define SCORE_H

void score_init();
void score_logic(unsigned long dt);
void score_render();

int load_hi_score();
void save_hi_score();

#endif
