#include "network.h"
#include <QtGui>
#include <QObject>
 #include <QtNetwork>
class QSslError;
class QHttp;
class QHttpResponseHeader;

//! [0]

netWork::netWork(QObject *parent) :
    QObject(parent)
{
}
 void netWork::setProgress(QProgressBar *prog)
 {
  progressDialog= prog;
 }

bool netWork::downloadFile(QString urlPath,QString distPath)
{
    //***************
  //  progressDialog = new QProgressBar(0);
isloaded=false;
    http = new QHttp(this);


    connect(http, SIGNAL(requestFinished(int,bool)),
            this, SLOT(httpRequestFinished(int,bool)));
    connect(http, SIGNAL(dataReadProgress(int,int)),
            this, SLOT(updateDataReadProgress(int,int)));
    connect(http, SIGNAL(responseHeaderReceived(QHttpResponseHeader)),
            this, SLOT(readResponseHeader(QHttpResponseHeader)));

#ifndef QT_NO_OPENSSL
    connect(http, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(sslErrors(QList<QSslError>)));
#endif
 //   connect(this, SIGNAL(progresseIsVisible(bool)), progressDialog, SLOT(setVisible(bool)));

    //******************************
m_urlPath=urlPath;
    QUrl url(m_urlPath);
    QFileInfo fileInfo(url.path());
    QString fileName =distPath+ fileInfo.fileName();
    qDebug()<<"destfileName"<<fileName;
    if (fileName.isEmpty())
        fileName = "index.html";

    if (QFile::exists(fileName)) {
        if (QMessageBox::question(0, tr("HTTP"),
                                  tr("There already exists a file called %1 in "
                                     "the current directory. Overwrite?").arg(fileName),
                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
            return false;
        QFile::remove(fileName);
    }

    fileHttp = new QFile(fileName);
    if (!fileHttp->open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, tr("HTTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(fileHttp->errorString()));
        delete fileHttp;
        fileHttp = 0;
        return false;
    }

    QHttp::ConnectionMode mode = url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
    http->setHost(url.host(), mode, url.port() == -1 ? 0 : url.port());

    if (!url.userName().isEmpty())
        http->setUser(url.userName(), url.password());

    httpRequestAborted = false;
    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    if (path.isEmpty())
        path = "/";
    httpGetId = http->get(path, fileHttp);

// progressDialog->show();

    progressDialog->setValue(0);
    while( httpRequestAborted == false){
qApp->processEvents();
    }
//    QVariant dd=isloaded;
//
//       QMessageBox::information(0, tr("HTTP"),("is finish \n"+dd.toString()));

       if (isloaded==false){
           return false;
       }

return true;

}
void netWork::httpRequestFinished(int requestId, bool error)
{
    if (requestId != httpGetId)
        return;
    if (httpRequestAborted) {
        if (fileHttp) {
            fileHttp->close();
            fileHttp->remove();
            delete fileHttp;
            fileHttp = 0;
        }

      //  progressDialog->hide();
        emit progresseIsVisible(false);
        return;
    }

    if (requestId != httpGetId)
        return;

  //  progressDialog->hide();
    emit progresseIsVisible(false);
    fileHttp->close();

    if (error) {
        fileHttp->remove();
        QMessageBox::information(0, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(http->errorString()));
         httpRequestAborted=true;
    } else {
      //  QString fileName = QFileInfo(QUrl(m_urlPath).path()).fileName();
     //    QMessageBox::information(0, tr("HTTP"),tr("Downloaded %1  to %2").arg(fileName).arg(QDir::homePath())+"/.kirtasse/data/");
       //  mypath=fileName;
         isloaded=true;
         httpRequestAborted=true;
    }


    delete fileHttp;
    fileHttp = 0;
}
void netWork::readResponseHeader(const QHttpResponseHeader &responseHeader)
{
    switch (responseHeader.statusCode()) {
    case 200:                   // Ok
    case 301:                   // Moved Permanently
    case 302:                   // Found
    case 303:                   // See Other
    case 307:                   // Temporary Redirect
        // these are not error conditions
        break;

    default:

        QMessageBox::information(0, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(responseHeader.reasonPhrase()));

      //  progressDialog->hide();
        emit progresseIsVisible(false);
        http->abort();

    }

}
void netWork::updateDataReadProgress(int bytesRead, int totalBytes)
{
    if (httpRequestAborted)
        return;
    emit progresseIsVisible(true);
    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(bytesRead);
}
void netWork::cancelDownload()
{
   //  QMessageBox::information(0, tr("HTTP"),tr("Download canceled."));
   qDebug()<<"Download canceled.";
     httpRequestAborted = true;
    http->abort();

}


#ifndef QT_NO_OPENSSL
void netWork::sslErrors(const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += ", ";
        errorString += error.errorString();
    }

    if (QMessageBox::warning(0, tr("HTTP "),
                             tr("One or more SSL errors has occurred: %1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        http->ignoreSslErrors();
    }
}
#endif
//! [1]
