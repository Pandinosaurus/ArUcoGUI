#include "aruco/aruco.h"
#include <opencv2/calib3d.hpp>
using namespace  std;
using namespace  aruco;

aruco::CameraParameters aruco_cameraCalibrate(std::vector<std::vector<aruco::Marker> >  &allMarkers, int imageWidth,int imageHeight,float markerSize,float *currRepjErr){


    unsigned char default_a4_board[] = {
            0x30, 0x20, 0x32, 0x34, 0x20, 0x31, 0x36, 0x31, 0x20, 0x34, 0x20, 0x2d,
            0x31, 0x30, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x2d, 0x35, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x2d, 0x35, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x35, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x35,
            0x30, 0x30, 0x20, 0x30, 0x20, 0x32, 0x32, 0x37, 0x20, 0x34, 0x20, 0x2d,
            0x34, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x31, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x31, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x35, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x2d, 0x34, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x35, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x38, 0x35, 0x20, 0x34, 0x20, 0x32, 0x30, 0x30, 0x20, 0x2d, 0x31,
            0x30, 0x30, 0x30, 0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x2d, 0x31,
            0x30, 0x30, 0x30, 0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x2d, 0x31,
            0x35, 0x30, 0x30, 0x20, 0x30, 0x20, 0x32, 0x30, 0x30, 0x20, 0x2d, 0x31,
            0x35, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x36, 0x36, 0x20, 0x34, 0x20,
            0x38, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x31, 0x33, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x31, 0x33, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x35, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x2d, 0x31, 0x35, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x32, 0x34, 0x34, 0x20, 0x34, 0x20, 0x2d, 0x31, 0x30, 0x30,
            0x30, 0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x35, 0x30,
            0x30, 0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x35, 0x30,
            0x30, 0x20, 0x2d, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x31, 0x30,
            0x30, 0x30, 0x20, 0x2d, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x34,
            0x34, 0x20, 0x34, 0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x2d, 0x34, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x31, 0x30, 0x30, 0x20, 0x2d, 0x34, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x31, 0x30, 0x30, 0x20, 0x2d, 0x39, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x2d, 0x39, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x39, 0x30, 0x20, 0x34, 0x20, 0x32, 0x30, 0x30, 0x20, 0x2d,
            0x34, 0x30, 0x30, 0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x2d, 0x34,
            0x30, 0x30, 0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x2d, 0x39, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x32, 0x30, 0x30, 0x20, 0x2d, 0x39, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x32, 0x31, 0x34, 0x20, 0x34, 0x20, 0x38, 0x30, 0x30,
            0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x30, 0x30,
            0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x30, 0x30,
            0x20, 0x2d, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x38, 0x30, 0x30, 0x20,
            0x2d, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x35, 0x33, 0x20, 0x34,
            0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x2d, 0x35, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x2d, 0x35, 0x30, 0x30, 0x20, 0x2d, 0x33, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x2d, 0x33, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x37, 0x20, 0x34, 0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x32, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x31, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x31, 0x30, 0x30, 0x20, 0x2d, 0x33, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x2d, 0x33, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x31, 0x34, 0x33, 0x20, 0x34, 0x20, 0x32, 0x30, 0x30, 0x20, 0x32,
            0x30, 0x30, 0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x2d, 0x33, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x32, 0x30, 0x30, 0x20, 0x2d, 0x33, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x32, 0x31, 0x39, 0x20, 0x34, 0x20, 0x38, 0x30, 0x30, 0x20, 0x32,
            0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x30, 0x30, 0x20, 0x32, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x30, 0x30, 0x20, 0x2d, 0x33, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x2d, 0x33, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x37, 0x38, 0x20, 0x34, 0x20, 0x2d, 0x31, 0x30, 0x30,
            0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x35, 0x30, 0x30,
            0x20, 0x38, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x35, 0x30, 0x30, 0x20,
            0x33, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20,
            0x33, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x35, 0x39, 0x20, 0x34, 0x20,
            0x2d, 0x34, 0x30, 0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31,
            0x30, 0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x30, 0x30,
            0x20, 0x33, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x34, 0x30, 0x30, 0x20,
            0x33, 0x30, 0x30, 0x20, 0x30, 0x20, 0x32, 0x30, 0x39, 0x20, 0x34, 0x20,
            0x32, 0x30, 0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x30, 0x20, 0x37, 0x30,
            0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20,
            0x33, 0x30, 0x30, 0x20, 0x30, 0x20, 0x32, 0x30, 0x30, 0x20, 0x33, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x20, 0x34, 0x20, 0x38, 0x30, 0x30,
            0x20, 0x38, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x30, 0x30, 0x20,
            0x38, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x30, 0x30, 0x20, 0x33,
            0x30, 0x30, 0x20, 0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x33, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x32, 0x34, 0x37, 0x20, 0x34, 0x20, 0x2d, 0x31, 0x30,
            0x30, 0x30, 0x20, 0x31, 0x34, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x35,
            0x30, 0x30, 0x20, 0x31, 0x34, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x35,
            0x30, 0x30, 0x20, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x31, 0x30,
            0x30, 0x30, 0x20, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x32, 0x33, 0x37,
            0x20, 0x34, 0x20, 0x2d, 0x34, 0x30, 0x30, 0x20, 0x31, 0x34, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x31, 0x30, 0x30, 0x20, 0x31, 0x34, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x31, 0x30, 0x30, 0x20, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x2d, 0x34, 0x30, 0x30, 0x20, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31,
            0x30, 0x30, 0x20, 0x34, 0x20, 0x32, 0x30, 0x30, 0x20, 0x31, 0x34, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x31, 0x34, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x39, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x32, 0x30, 0x30, 0x20, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x36,
            0x20, 0x34, 0x20, 0x38, 0x30, 0x30, 0x20, 0x31, 0x34, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x31, 0x33, 0x30, 0x30, 0x20, 0x31, 0x34, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x31, 0x33, 0x30, 0x30, 0x20, 0x39, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x38, 0x30, 0x30, 0x20, 0x39, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31,
            0x37, 0x37, 0x20, 0x34, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20, 0x32,
            0x30, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x35, 0x30, 0x30, 0x20, 0x32,
            0x30, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x35, 0x30, 0x30, 0x20, 0x31,
            0x35, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x31, 0x30, 0x30, 0x30, 0x20,
            0x31, 0x35, 0x30, 0x30, 0x20, 0x30, 0x20, 0x39, 0x33, 0x20, 0x34, 0x20,
            0x2d, 0x34, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x31, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30, 0x30, 0x20, 0x30, 0x20, 0x31,
            0x30, 0x30, 0x20, 0x31, 0x35, 0x30, 0x30, 0x20, 0x30, 0x20, 0x2d, 0x34,
            0x30, 0x30, 0x20, 0x31, 0x35, 0x30, 0x30, 0x20, 0x30, 0x20, 0x38, 0x36,
            0x20, 0x34, 0x20, 0x32, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30, 0x30, 0x20,
            0x30, 0x20, 0x37, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30, 0x30, 0x20, 0x30,
            0x20, 0x37, 0x30, 0x30, 0x20, 0x31, 0x35, 0x30, 0x30, 0x20, 0x30, 0x20,
            0x32, 0x30, 0x30, 0x20, 0x31, 0x35, 0x30, 0x30, 0x20, 0x30, 0x20, 0x32,
            0x32, 0x39, 0x20, 0x34, 0x20, 0x38, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x30, 0x30, 0x20, 0x32, 0x30, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x31, 0x33, 0x30, 0x30, 0x20, 0x31, 0x35, 0x30,
            0x30, 0x20, 0x30, 0x20, 0x38, 0x30, 0x30, 0x20, 0x31, 0x35, 0x30, 0x30,
            0x20, 0x30, 0x20, 0x41, 0x52, 0x55, 0x43, 0x4f, 0x5f, 0x4d, 0x49, 0x50,
            0x5f, 0x33, 0x36, 0x68, 0x31, 0x32
    };
    unsigned int default_a4_board_size = 1254;
    // given the set of markers detected, the function determines the get the 2d-3d correspondes
    auto getMarker2d_3d_=[](vector<cv::Point2f>& p2d, vector<cv::Point3f>& p3d, const vector<Marker>& markers_detected,
                            const MarkerMap& bc)
    {
        p2d.clear();
        p3d.clear();
        // for each detected marker
        for (size_t i = 0; i < markers_detected.size(); i++)
        {
            // find it in the bc
            auto fidx = std::string::npos;
            for (size_t j = 0; j < bc.size() && fidx == std::string::npos; j++)
                if (bc[j].id == markers_detected[i].id)
                    fidx = j;
            if (fidx != std::string::npos)
            {
                for (int j = 0; j < 4; j++)
                {
                    p2d.push_back(markers_detected[i][j]);
                    p3d.push_back(bc[fidx][j]);
                }
            }
        }
    };

    aruco::MarkerMap mmap;
    stringstream sstr;
    sstr.write((char*)default_a4_board, default_a4_board_size);
    mmap.fromStream(sstr);
    if (!mmap.isExpressedInMeters())
        mmap = mmap.convertToMeters(static_cast<float>( markerSize));



    vector<vector<cv::Point2f> >calib_p2d;
    vector<vector<cv::Point3f> > calib_p3d;

    for(auto &detected_markers:allMarkers){
        vector<cv::Point2f> p2d;
        vector<cv::Point3f> p3d;
        getMarker2d_3d_(p2d, p3d, detected_markers, mmap);
        for(auto p:p3d)cout<<p<<" ";cout<<endl;
        if (p3d.size() > 0)
        {
            calib_p2d.push_back(p2d);
            calib_p3d.push_back(p3d);
        }
    }

    vector<cv::Mat> vr, vt;
    CameraParameters cameraParams;
    cameraParams.CamSize = cv::Size(imageWidth,imageHeight);
    float err=cv::calibrateCamera(calib_p3d, calib_p2d, cameraParams.CamSize, cameraParams.CameraMatrix, cameraParams.Distorsion, vr, vt);
    cameraParams.CameraMatrix.convertTo(cameraParams.CameraMatrix,CV_32F);
    cameraParams.Distorsion.convertTo(cameraParams.Distorsion,CV_32F);
    if (currRepjErr!=0) *currRepjErr=err;

    stringstream str;
    str<<cameraParams;
    str<<" cm="<<cameraParams.CameraMatrix;
     return cameraParams;
}
