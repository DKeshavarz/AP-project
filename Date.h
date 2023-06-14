#include <string>

#ifndef DATE_H
#define DATE_H

class Date
{
    public:
        void setDate(std :: string);

        int  getAge ();
        std :: string getTweetDate();


    private:
        std :: string date;
        int userAge;


};










#endif