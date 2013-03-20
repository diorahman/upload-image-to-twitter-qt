#ifndef OAUTH_HELPER_H
#define OAUTH_HELPER_H

#include <QString>
#include <QChar>
#include <QList>
#include <QTime>
#include <QStringList>
#include <QCryptographicHash>
#include <qmath.h>
#include "oauth_types.h"

namespace Helper{


static Params qsToMap(const QString & qs){

    QMap<QString, QString> m;
    QStringList l = qs.split("&");
    QStringList::const_iterator i;
    for (i = l.constBegin(); i != l.constEnd(); ++i){
        QString val = *i;
        m.insert(val.split("=")[0], val.split("=")[1]);
    }

    return m;
}

static QByteArray buildMultipartBody(const QString bound, Parts params)
{

    QByteArray data(QString("--"+bound+"\r\n").toAscii());

    Parts::iterator p;
    for (p = params.begin(); p != params.end(); ++p){

        Part part = p.value();
        data += "Content-Disposition: form-data;";
        data += " " + part.contentDisposition + "\r\n";
        if(part.contentType.length()) data += part.contentType + "\r\n";
        data += "\r\n";
        data += part.data;
        data += "\r\n";

        data += QString("--" + bound + "\r\n").toAscii();
    }

    return data.mid(0 , data.length() - 2) + "--";
}

static int chr(const QString & s){
    return (int) ((QChar) s.at(0).toAscii()).toAscii();
}

static QString pick(const QList<int> & xs){
    int x = xs.at(qFloor(((qrand() + 0.0)/RAND_MAX) * xs.length()));
    return QString(QChar(x));
}

static qint64 timestamp(){ return qFloor(QDateTime::currentMSecsSinceEpoch()/1000.0);}

static QString identifier(const int & n, const bool & f = false){

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    qrand();

    QList<int> letters;
    if(f)
    letters.push_back(chr("_"));
    int i = 0;
    for (i = 0; i < 26; i++) letters.push_back(chr("A") + i);
    for (i = 0; i < 26; i++) letters.push_back(chr("a") + i);

    QList<int> words = QList<int>(letters);
    for (i = 0; i < 10; i++) words.push_back(chr("0") + i);

    QString output = pick(letters);
    for (i = 1; i < n; i++) output += pick(words);
    return output;
}

static QString hmacSha1Base64(const QString & key, const QString & data){

    QByteArray ipad;
    QByteArray opad;
    QByteArray ctx;
    QByteArray sha1;
    QByteArray k;

    k = key.toAscii();

    int keyLen = key.size();

    if(keyLen > 64){

        QByteArray tempKey;
        tempKey.append(key);
        k = QCryptographicHash::hash(tempKey, QCryptographicHash::Sha1);

        keyLen = 20;
    }

    ipad.fill( 0, 64);
    opad.fill(0, 64);

    ipad.replace(0, keyLen, k);
    opad.replace(0, keyLen, k);

    for (int i=0; i<64; i++)
    {
        ipad[i] = ipad[i] ^ 0x36;
        opad[i] = opad[i] ^ 0x5c;
    }

    ctx.append(ipad,64);
    ctx.append(data);

    sha1 = QCryptographicHash::hash(ctx, QCryptographicHash::Sha1);

    ctx.clear();
    ctx.append(opad,64);
    ctx.append(sha1);

    sha1.clear();

    sha1 = QCryptographicHash::hash(ctx, QCryptographicHash::Sha1);

    return sha1.toBase64();
}



}



#endif // OAUTH_HELPER_H
