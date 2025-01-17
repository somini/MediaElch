#pragma once

#include "globals/Meta.h"
#include "globals/ScraperResult.h"
#include "network/NetworkManager.h"
#include "tv_shows/TvShow.h"

#include <QDialog>
#include <QElapsedTimer>
#include <QFile>
#include <QMediaPlayer>
#include <QNetworkReply>
#include <QTableWidgetItem>

namespace Ui {
class TvTunesDialog;
}

namespace mediaelch {
namespace scraper {
class TvTunes;
}
} // namespace mediaelch

class TvTunesDialog : public QDialog
{
    Q_OBJECT

public:
    TvTunesDialog(TvShow& show, QWidget* parent = nullptr);
    ~TvTunesDialog() override;

public slots:
    int exec() override;

private slots:
    void onSearch();
    void onShowResults(QVector<ScraperSearchResult> results);
    void onStateChanged(ELCH_MEDIA_PLAYBACK_STATE newState);
    void onPlayPause();
    void onResultClicked(QTableWidgetItem* item);
    void startDownload();
    void cancelDownload();
    void downloadProgress(qint64 receivedBytes, qint64 totalBytes);
    void downloadFinished();
    void downloadReadyRead();
    void onClose();
    void onUpdateTime(qint64 currentTime);
    void onNewTotalTime(qint64 totalTime);

private:
    Ui::TvTunesDialog* ui = nullptr;
    mediaelch::scraper::TvTunes* m_tvTunes;
    TvShow& m_show;
    qint64 m_totalTime = 0;
    QMediaPlayer* m_mediaPlayer = nullptr;
    mediaelch::network::NetworkManager* m_network = nullptr;
    QNetworkReply* m_downloadReply = nullptr;
    QElapsedTimer m_downloadTime;
    QFile m_output;
    QUrl m_themeUrl;
    bool m_downloadInProgress = false;
    bool m_fileDownloaded = false;
    void clear();
};
