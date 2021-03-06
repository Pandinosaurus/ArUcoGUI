#ifndef ModuleMapper_MODULE_H
#define ModuleMapper_MODULE_H



#include <QToolBox>
#include <QWidget>
#include <QStackedWidget>
#include <QThread>
#include <QAction>
#include <memory>
#include "moduletools/appmodule.h"
#include "gparam/paramsetwdgt.h"
#include "videoplayer/videoplayer.h"
#include "sglviewer/sglviewer.h"
#include "aruco/aruco.h"
#include "modulemapper_exports.h"
#include "mappercontrolpanel.h"
#include <iostream>
 class APP_MODULE_MAPPER_TOOLS_API  ModuleMapper: public AppModule {
    Q_OBJECT
public:
    ModuleMapper();
    std::string getName() const {return "Mapper";}
    std::string getToolBoxTitle() const {return "Mapper Parameters";}

    aruco::MarkerMap getMarkerMapGenerated()const{return _mmap;}

public slots:
    void on_global_action(const gparam::ParamSet &paramset);
    void on_activate();
    void on_process();

private slots:
    void on_vplayer_opened();
 private:

    aruco::MarkerMap _selectedMarkerMap;
      QAbstractButton  *Btn_gotoNextFrame;
    VideoPlayer *vplayer=0;
     QAction *act_View3D;
    mapperControlPanel *CalibPanel;
    aruco::MarkerMap _mmap;

};





#endif // TSDFTOOLBOX_H
