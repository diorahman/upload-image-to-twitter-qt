#ifndef OAUTH_TYPES_H
#define OAUTH_TYPES_H

#include <QString>
#include <QMap>

struct Part{
    QByteArray contentDisposition;
    QByteArray contentType;
    QByteArray data;
};

typedef QMap<QString, QString> Params;
typedef QMap<QString, Part> Parts;

#endif // OAUTH_TYPES_H
