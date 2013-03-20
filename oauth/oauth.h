#ifndef OAUTH_H
#define OAUTH_H

#include <QObject>
#include "oauth_types.h"

class OAuthPrivate;

class OAuth : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString consumerKey READ consumerKey WRITE setConsumerKey NOTIFY consumerKeyChanged)
    Q_PROPERTY(QString consumerSecret READ consumerSecret WRITE setConsumerSecret NOTIFY consumerSecretChanged)
    Q_PROPERTY(QString oauthToken READ oauthToken WRITE setOauthToken NOTIFY oauthTokenChanged)
    Q_PROPERTY(QString oauthTokenSecret READ oauthTokenSecret WRITE setOauthTokenSecret NOTIFY oauthTokenSecretChanged)
    Q_PROPERTY(QString callbackUrl READ callbackUrl WRITE setCallbackUrl NOTIFY callbackUrlChanged)
    Q_PROPERTY(QString mutipartBoundary READ mutipartBoundary)

    Q_DECLARE_PRIVATE(OAuth)

public:
    explicit OAuth(QObject *parent = 0);
    explicit OAuth(const QString & consumerKey,
                   const QString & consumerSecret,
                   const QString & oauthToken,
                   const QString & oauthTokenSecret,
                   const QString & callbackUrl = "",
                   QObject *parent = 0);

    virtual ~OAuth();

signals:
    void accessTokenReceived(const Params & tokens, const QString & raw);
    void requestTokenReceived(const Params & tokens, const QString & raw);
    void resourceReceived(const QString & resource);
    void errorOccurred(const QString & errorString);

signals:
    void consumerKeyChanged();
    void consumerSecretChanged();
    void oauthTokenChanged();
    void oauthTokenSecretChanged();
    void callbackUrlChanged();

public slots:
    void requestToken(const QString & url);
    void accessToken(const QString & url, const QString & oauthToken, const QString & oauthTokenSecret, const QString & oauthVerifier);
    void resource(const QString & url, const QString oauthToken, const QString & oauthTokenSecret, const QString & method, const Params & params = Params(), const QByteArray & rawParams = QByteArray());
    void resource(const QString & url, const QString & method, const Params & params = Params(), const QByteArray & rawParams = QByteArray());

public:
    void setConsumerKey(const QString & aConsumerKey);
    void setConsumerSecret(const QString & aConsumerSecret);
    void setOauthToken(const QString & anOauthToken);
    void setOauthTokenSecret(const QString & anOauthTokenSecret);
    void setCallbackUrl(const QString & aCallbackUrl);

    QString consumerKey();
    QString consumerSecret();
    QString oauthToken();
    QString oauthTokenSecret();
    QString callbackUrl();

    QString mutipartBoundary();

protected:
    OAuthPrivate * const d_ptr;


};

#endif // OAUTH_H
