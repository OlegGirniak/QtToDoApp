#ifndef STRINGHASHER_H
#define STRINGHASHER_H

#include <QCryptographicHash>
#include <QString>

class StringHasher
{
public:
    static QString hashString(const QString &inputString)
    {
        QByteArray inputBytes = inputString.toUtf8();
        QByteArray hashBytes = QCryptographicHash::hash(inputBytes, QCryptographicHash::Sha256);
        QString hashString = QString(hashBytes.toHex());

        return hashString;
    }
};

#endif // STRINGHASHER_H
