#include <QSplitter>
#include <QPlainTextEdit>
#include "modulearucotest.h"
#include "moduletools/appparams.h"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "arucogparam.h"
using namespace std;
ModuleArucoTest::ModuleArucoTest() {


    vplayer=new modulearucotest::VideoPlayer();
    connect(vplayer,SIGNAL(newImage(cv::Mat&)),this,SLOT(on_newVideoImage(cv::Mat&)));
    setIcon(QPixmap ( QString:: fromUtf8 ( ":/images/aruco_params.png" ) ));
    QToolBar *tbar=new QToolBar("Aruco");
    act_ShowThresImage=  new QAction ( QIcon ( ":/images/blackwhite.png" ), tr ( "&Show thresholded Image..." ), this );
    act_ShowThresImage->setCheckable(true);
    connect(act_ShowThresImage,SIGNAL(triggered()),this,SLOT(on_act_ShowThresImage_triggered( )));
    tbar->addAction(act_ShowThresImage);
    setCentralWidget(vplayer);
    setToolBar(tbar);

    //create a panel showing the detections
    QWidget *controlPanel=new QWidget;

     detectionsLabel=new QPlainTextEdit;
     detectionsLabel->setWordWrapMode(QTextOption::NoWrap);

    QAbstractButton *saveButton = new QPushButton(tr("Save..."));
    saveButton->setIcon(QPixmap ( QString:: fromUtf8 ( ":/images/save.png" )));
    connect(saveButton,SIGNAL(clicked(bool)),this,SLOT(on_saveDetections()));
    QAbstractButton *clearButton = new QPushButton(tr("Clear..."));
    clearButton->setIcon(QPixmap ( QString:: fromUtf8 ( ":/images/reset.png" )));
    connect(clearButton,SIGNAL(clicked(bool)),this,SLOT(on_clearDetections()));
//    connect(openButton, &QAbstractButton::clicked, this, &VideoPlayer::saveDetections);



    QBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(0);

    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(saveButton);


    QBoxLayout *controlLayout = new QVBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(detectionsLabel);
    controlLayout->addLayout(buttonLayout);

    controlPanel->setLayout(controlLayout);
    setControlPanel(controlPanel);


}

void ModuleArucoTest::on_clearDetections(){
    detectionsLabel->clear();
}
void ModuleArucoTest::on_saveDetections(){

}


void ModuleArucoTest::on_global_action(const gparam::ParamSet &paramset){
    if (paramset.getName()=="arucoParamsChanged") redraw();

}

void ModuleArucoTest::getThresholdedImage(cv::Mat &TCopy){
    cv::cvtColor( ArucoMarkerDetector::get(false).getThresholdedImage(0),TCopy,CV_GRAY2BGR);

}

void ModuleArucoTest::redraw(){
    if (currImage.empty()) return;
    cv::Mat im2;
    currImage.copyTo(im2);
    auto markers=ArucoMarkerDetector::get().detect(currImage);
    printDetectionsText(markers);
    cv::Mat im2show;
    if (act_ShowThresImage->isChecked()){
        getThresholdedImage(im2show);
    }
    else{
        for(auto m:markers) m.draw(im2);
        im2show=im2;
    }
    vplayer->setImage(im2show);
}

void ModuleArucoTest::printDetectionsText(const std::vector<aruco::Marker> &markers){
QString text;
text.setNum( vplayer->getFramePos());
text+=" ";
        for(const auto &m:markers){
            std::stringstream str;
            str<<m;
            text+=str.str().c_str();
            text+=" ";
    }
        text+="\n";
        detectionsLabel->insertPlainText(text);
}

void ModuleArucoTest::on_act_ShowThresImage_triggered(){
    redraw();
}
void ModuleArucoTest::on_newVideoImage(cv::Mat &im){
    im.copyTo(currImage);
    auto markers=ArucoMarkerDetector::get().detect(currImage);
    printDetectionsText(markers);
    if (!act_ShowThresImage->isChecked()){
        for(auto m:markers) m.draw(im);
    }
    else{
        getThresholdedImage(im);
    }
}
