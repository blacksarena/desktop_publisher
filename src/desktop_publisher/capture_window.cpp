
#include "desktop_publisher/capture_window.hpp"

CaptureWindow::CaptureWindow(QWidget *parent)
:QMainWindow(parent)
{
    label = new QLabel(this);
    label->move(0, 0);
    label->resize(this->width(), this->height());
    label->show();
}

CaptureWindow::~CaptureWindow()
{   
}

cv::Mat CaptureWindow::getCaptureImage()
{
    int x = this->pos().x();
    int y = this->pos().y();
    int width  = this->size().width();
    int height = this->size().height();
    printf("%d, %d, %d, %d\n", x, y, width, height);
    QPixmap pix = QGuiApplication::primaryScreen()->grabWindow(0, x, y, width, height);
    QImage clip_desktop = pix.toImage();
    label->setPixmap(pix);
    return convertQImageToCvMat(clip_desktop);
}

cv::Mat CaptureWindow::convertQImageToCvMat(const QImage &source, int image_type)
{
    cv::Mat mat(source.height(), source.width(), image_type, (void*)source.bits());
    return mat;
}