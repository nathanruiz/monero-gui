#ifndef P2POOLMINER_H
#define P2POOLMINER_H

#include <memory>

#include <QMutex>
#include <QObject>
#include <QUrl>
#include <QProcess>
#include <QVariantMap>
#include "qt/FutureScheduler.h"
#include "NetworkType.h"

class P2PoolMiner : public QObject
{
    Q_OBJECT

public:
    explicit P2PoolMiner(QObject *parent = 0);
    ~P2PoolMiner();
    bool startMining(const QString &address);
    bool stopMining();
    bool isMining();
    double miningHashRate();

private:
    std::unique_ptr<QProcess> m_p2pool_daemon;
    QMutex m_p2poolMutex;
    QString m_p2pool;
    bool is_mining;
};

#endif