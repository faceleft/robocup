#ifndef buttons_h
#define buttons_h

void buttons_task(\ //NULL если нет действий
    void (*button1_handler)(void),\
    void (*button2_handler)(void),\
    void (*button3_handler)(void),\
    void (*button4_handler)(void),\
    void (*button5_handler)(void),\
    void (*button6_handler)(void),\
);

#endif