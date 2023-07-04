#include <string>

#ifndef DATE_H
#define DATE_H

class Date {
public:
    Date();
    Date(std::string);

    void setDate(std ::string);
    void setAge();

    int getAge() const;
    std ::string getTweetDate();

private:
    int year;
    int month;
    int day;
    int userAge {19};
};

#endif