#ifndef TWITTER_H
#define TWITTER_H

#include <QObject>
#include "oauth/oauth.h"
#include "oauth/oauth_types.h"


class Page;
class QJson;

class Twitter : public OAuth
{
    Q_OBJECT
public:
    explicit Twitter(QObject *parent = 0);
    Q_INVOKABLE void testUploadImage();
    
private slots:
    void onResourceReceived(const QString & resource);

private:
    QString m_oAuthToken;
    QString m_oAuthTokenSecret;
};

#endif // TWITTER_H