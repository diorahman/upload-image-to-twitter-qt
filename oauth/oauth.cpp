#include "oauth.h"
#include "oauth_p.h"

OAuth::OAuth(QObject *parent) :
    QObject(parent), d_ptr(new OAuthPrivate(this))
{
}

OAuth::OAuth(const QString & consumerKey,
               const QString & consumerSecret,
               const QString & oauthToken,
               const QString & oauthTokenSecret,
               const QString & callbackUrl,
               QObject *parent) : QObject(parent), d_ptr(new OAuthPrivate(this))

 {
      Q_D(OAuth);
      d->consumerKey = consumerKey;
      d->consumerSecret = consumerSecret;
      d->oauthToken = oauthToken;
      d->oauthTokenSecret = oauthTokenSecret;
      d->callbackUrl = callbackUrl;
}

OAuth::~OAuth()
{
    delete d_ptr;
}

void OAuth::requestToken(const QString & url){
    Q_D(OAuth);
    d->requestToken(url);
}

void OAuth::accessToken(const QString & url, const QString & oauthToken, const QString & oauthTokenSecret, const QString & oauthVerifier){
    Q_D(OAuth);
    d->oauthToken = oauthToken;
    d->oauthTokenSecret = oauthTokenSecret;
    d->accessToken(url, oauthVerifier);

}
void OAuth::resource(const QString & url, const QString oauthToken, const QString & oauthTokenSecret, const QString & method, const Params & params, const QByteArray & rawParams){
    Q_D(OAuth);
    d->oauthToken = oauthToken;
    d->oauthTokenSecret = oauthTokenSecret;
    resource(url, method, params, rawParams);
}

void OAuth::resource(const QString & url, const QString & method, const Params & params, const QByteArray & rawParams){
    Q_D(OAuth);
    d->resource(url, method, params, rawParams);

}

void OAuth::setConsumerKey(const QString & aConsumerKey){
    Q_D(OAuth);
    if(aConsumerKey != d->consumerKey){
        d->consumerKey = aConsumerKey;
        emit consumerKeyChanged();
    }
}

void OAuth::setConsumerSecret(const QString & aConsumerSecret){
    Q_D(OAuth);
    if(aConsumerSecret != d->consumerKey){
        d->consumerSecret = aConsumerSecret;
        emit consumerSecretChanged();
    }
}
void OAuth::setOauthToken(const QString & anOauthToken){
    Q_D(OAuth);
    if(anOauthToken != d->consumerKey){
        d->oauthToken = anOauthToken;
        emit oauthTokenChanged();
    }
}
void OAuth::setOauthTokenSecret(const QString & anOauthTokenSecret){
    Q_D(OAuth);
    if(anOauthTokenSecret != d->consumerKey){
        d->oauthTokenSecret = anOauthTokenSecret;
        emit oauthTokenSecretChanged();
    }
}
void OAuth::setCallbackUrl(const QString & aCallbackUrl){
    Q_D(OAuth);
    if(aCallbackUrl != d->consumerKey){
        d->callbackUrl = aCallbackUrl;
        emit callbackUrlChanged();
    }

}

QString OAuth::consumerKey(){
    Q_D(OAuth);
    return d->consumerKey;
}
QString OAuth::consumerSecret(){
    Q_D(OAuth);
    return d->consumerSecret;
}
QString OAuth::oauthToken(){
    Q_D(OAuth);
    return d->oauthToken;
}
QString OAuth::oauthTokenSecret(){
    Q_D(OAuth);
    return d->oauthTokenSecret;
}
QString OAuth::callbackUrl(){
    Q_D(OAuth);
    return d->callbackUrl;
}

QString OAuth::mutipartBoundary()
{
    Q_D(OAuth);
    return d->multipartBound;
}


