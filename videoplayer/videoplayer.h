
#ifndef  _VIDEOPLAYER_H
#define _VIDEOPLAYER_H

#include <QWidget>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <memory>
#include "videoplayer_exports.h"
#include <QButtonGroup>
#include <QBoxLayout>
#include <QScrollArea>
#include "aruco/aruco.h"


class QAbstractButton;
class QSlider;
class QLabel;
class QUrl;
 class VideoImagePlayerBase;
 class SceneImageViewer2;
class APP_VIDEOPLAYER_TOOLS_API VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();
    void addButton(QAbstractButton*);


    cv::Mat getInputImage(){return imIn;}
    cv::Mat getShownImage(){return imshown;}
    std::string getCurrentImageInfo();
    void setProcessImageWithArucoDetector(bool v){_processImageWithArucoDetector=v;};
    bool processImageWithArucoDetector()const{return _processImageWithArucoDetector;}
    std::vector<aruco::Marker> getDetectedMarkers(){return detectedMarkers;}
    bool isVideo()const;
    QStringList getSource()const;


    std::vector<QAction*> getActions(){return _actions;}
    void showAllCandidates(bool v);
public slots:
    void openVideoFile();
    void openImages();
    void setImage(  cv::Mat &img2Show);
    void updateImage();
    bool playNextFrame();


private slots:
    void playPauseButtonClicked( );
    void setPosition(int position);
    void sliderReleased( );
    void valueChanged(int);
signals:
    void newImage(cv::Mat &);
    void openedImageOrVideo();
protected:

private:
    QAbstractButton *m_playButton;

     std::vector<QAction*> _actions;

    std::vector<QAbstractButton *> addedButtons;
    QSlider *m_positionSlider;
    QLabel *m_errorLabel;
    cv::Mat imIn,imshown;
    SceneImageViewer2 *imageWdgt;
    QBoxLayout *controlLayout;
    QScrollArea *scrollArea;
    int isPlaying=0;
    std::shared_ptr<VideoImagePlayerBase> _reader;
    std::vector<aruco::Marker> detectedMarkers;
    bool _processImageWithArucoDetector=true;
    void prepareForOpenedReader();
    bool grabAndShow();
    float scaleFactor=1;


    bool _showAllCandidates=false;
}; 

#endif
