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

    //m_oAuthToken = "222985359-LODFDMHKy4gYU1NncP5PqYqrKKZxdLCIBmhw7jR3";
    //m_oAuthTokenSecret = "DwA9I6gjj1E0QoGZhYqASoBGH0THuS13VNQjZNaho0M";

    this->setConsumerKey("TceD1lD6NKRVdIG5FTQlsg");
    this->setConsumerSecret("CVzmEXTIPFN5RKEIzCXErRJardCg6lfA0bX5wU8WHA");
    this->setOauthToken("924279246-QhiYSszZpnV706RGEyTtSufpX7tPNC57t8FdPZWl");
    this->setOauthTokenSecret("MmH158cSUv9Zum9YRJZrfkCJJdqKM9eV1FeoUvkygZo");

    QFile file("/Users/diorahman/Develop/poco/test/oauth/qt/app/test.png");
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
