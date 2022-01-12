#include "P2PoolMiner.h"
#include "common/util.h"
#include <QElapsedTimer>
#include <QFile>
#include <QMutexLocker>
#include <QThread>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QUrl>
#include <QtConcurrent/QtConcurrent>
#include <QApplication>
#include <QProcess>
#include <QStorageInfo>
#include <QVariantMap>
#include <QVariant>
#include <QMap>


bool P2PoolMiner::startMining(const QString &address)
{
    QStringList arguments;
    arguments << "--host";
    arguments << "127.0.0.1";
    arguments << "--wallet";
    arguments << address;
    m_p2pool_daemon.reset(new QProcess());
    is_mining = true;
    return m_p2pool_daemon->startDetached(m_p2pool, arguments);

}

P2PoolMiner::P2PoolMiner(QObject *parent)
    : QObject(parent)
{

    // Platform depetent path to monerod
#ifdef Q_OS_WIN
    m_p2pool = QApplication::applicationDirPath() + "/p2pool.exe";
#elif defined(Q_OS_UNIX)
    m_p2pool = QApplication::applicationDirPath() + "/p2pool";
#endif

    if (m_p2pool.length() == 0) {
        qCritical() << "no daemon binary defined for current platform";
    }
    is_mining = false;
}

bool P2PoolMiner::stopMining()
{
    if(is_mining){
        //m_p2pool_daemon->close();
        QProcess::execute("pkill", {"p2pool"});
        is_mining = false;
        return true;
    }
    return false;
}

bool P2PoolMiner::isMining()
{
    return is_mining;
}

double P2PoolMiner::miningHashRate()
{
    return 20.0;
}

P2PoolMiner::~P2PoolMiner()
{
    stopMining();
}