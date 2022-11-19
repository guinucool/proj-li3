#ifndef _DATE_H_
#define _DATE_H_

/// \struct Estrutura que define as variáveis do tipo cidade.
typedef struct _DATE_{
    short date[3];      //!< Data a ser considerada
    void* keyRef;       //!< Chave associada à data {username(user) ou id(riders && drivers)}
    char type;          //!< Tipo de data {a - birth_date(driver) ou b - account_creation(driver) ou c - date(rides) ou d - birth_date(users) ou e - account_creation(users)}
}Date;

Date * createDate(short* date, void* key, char type);
void destroyDate(Date * date);

#endif
