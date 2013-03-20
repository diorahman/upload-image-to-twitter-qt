#ifndef OAUTH_P_H
#define OAUTH_P_H

#include <QObject>
#include <QNetworkRequest>
#include "oauth_types.h"

class QNetworkAccessManager;
class QNetworkReply;
class QSslConfiguration;
class OAuth;

class OAuthPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(OAuth)

public:
    explicit OAuthPrivate(OAuth *parent = 0);
    enum RequestType { RequestToken, AccessToken, Resource, ResourceStream};

public:
    QString consumerKey;
    QString consumerSecret;
    QString oauthToken;
    QString oauthTokenSecret;
    QString callbackUrl;
    QString multipartBound;

private:
    QNetworkAccessManager * nam;
    OAuth * const q_ptr;
    QSslConfiguration * config;
    QNetworkReply * oauthReply;

private slots:
    QString paramsString(const Params & params);
    QString baseString(const QString & method, const QString & url, const QString & paramStr);
    QString signingKey(const QString & consumerSecretKey, const QString & oauthTokenSecretKey = "");
    QString signature(const QString signingKeyStr, const QString & baseStr);

    QString buildAuthHeader(const QString & method, const QString & url, const Params & data = Params(), const QString & verifier = "");
    QPair<QNetworkRequest, QString> buildRequest(const QString & method, const QString & url, const QString authStr, const Params & data = Params());

    void reply();

public slots:
    void requestToken(const QString & url);
    void accessToken(const QString & url, const QString & verifier);
    void resource(const QString & url, const QString & method, const Params & params, const QByteArray & rawParams = QByteArray());


};

#endif // OAUTH_P_H
