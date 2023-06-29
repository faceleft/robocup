#ifndef ROBOT_BUTTONS_H
#define ROBOT_BUTTONS_H

/*
должна быть запущена в void loop()
аргументы - функции которые вызываются при 
нажатии соответствующей кнопки, 
если функции нет передать NULL
*/
void buttons_task(\
    void (*button1_handler)(void),\
    void (*button2_handler)(void),\
    void (*button3_handler)(void),\
    void (*button4_handler)(void),\
    void (*button5_handler)(void),\
    void (*button6_handler)(void)\
);

#endif