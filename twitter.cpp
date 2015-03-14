#include "twitter.h"
#include "oauth/oauth_helper.h"

#include <QFile>
#include <QDebug>

Twitter::Twitter(QObject *parent) :
    OAuth(parent)
{
    connect(this, SIGNAL(resourceReceived(QString)), this, SLOT(onResourceReceived(QString)));
}

void Twitter::testUploadImage()
{
    this->setConsumerKey("consumer_key");
    this->setConsumerSecret("consumer_secret");
    this->setOauthToken("oauth_token");
    this->setOauthTokenSecret("oauth_token_secret");

    QFile file("test.png");
    file.open(QIODevice::ReadOnly);

    Part imagePart;
    imagePart.contentDisposition = "name=\"media[]\"; filename=\"1234.png\"";
    imagePart.contentType = "application/octet-stream";
    imagePart.data = file.readAll();

    Part statusPart;
    statusPart.contentDisposition = "name=\"status\"";
    statusPart.contentType = "";
    statusPart.data = "Abrakadabra";

    Parts parts;
    parts.insert("image", imagePart);
    parts.insert("status", statusPart);

    QByteArray data = Helper::buildMultipartBody(this->mutipartBoundary(), parts);
    resource("https://upload.twitter.com/1/statuses/update_with_media.json", "POST", Params(), data);
}

void Twitter::onResourceReceived(const QString &resource)
{
    qDebug() << "Resource";
    qDebug() << resource;
}
