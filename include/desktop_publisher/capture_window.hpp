
#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

class CaptureWindow : public QMainWindow
{
public:
    CaptureWindow(QWidget *parent = nullptr);
    ~CaptureWindow();
    cv::Mat getCaptureImage();
    cv::Mat convertQImageToCvMat(const QImage &source, int image_type = CV_8UC4);

private:
    QLabel *label;
};
