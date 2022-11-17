#ifndef _DATE_H_
#define _DATE_H_

typedef struct _DATE_{
    short date[3];
    void* keyRef;      // username(user) | id(riders && drivers)
    char type;         // a - birth_date(driver) | b - account_creation(driver) | c - date(rides) | d - birth_date(users) | e - account_creation(users)
}Date;

Date * createDate(short* date, void* key, char type);
void destroyDate(Date * date);

#endif
