#include <QApplication>
#include <QSlider>
#include <QPixmap>
#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>

class CircleWidget:public QWidget {
    Q_OBJECT
public:
    CircleWidget() = default;
    CircleWidget(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
public slots:
    void setGreen();
    void setYellow();
    void setRed();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonGreenPixmap;
    QPixmap mButtonYellowPixmap;
    QPixmap mButtonRedPixmap;
    bool isDown = false;
};

CircleWidget::CircleWidget(QWidget *parent) {
    setParent(parent);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonGreenPixmap = QPixmap("G:\\work\\Prog\\progs\\DZ36\\greenButton.png");
    mButtonYellowPixmap = QPixmap("G:\\work\\Prog\\progs\\DZ36\\yellowButton.png");
    mButtonRedPixmap = QPixmap ("G:\\work\\Prog\\progs\\DZ36\\redButton.png");
    mCurrentButtonPixmap = mButtonGreenPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
}

void CircleWidget::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize CircleWidget::sizeHint() const {
    return QSize (200,250);
}

QSize CircleWidget::minimumSizeHint() const {
    return QSize (100,100);
}

void CircleWidget::setGreen() {
    mCurrentButtonPixmap = mButtonGreenPixmap;
    update();
}

void CircleWidget::setYellow() {
    mCurrentButtonPixmap = mButtonYellowPixmap;
    update();
}

void CircleWidget::setRed() {
    mCurrentButtonPixmap = mButtonRedPixmap;
    update();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget appWindow;
    auto *layout = new QVBoxLayout(&appWindow);
    CircleWidget paint(&appWindow);
    QSlider slider(Qt::Horizontal);
    slider.setParent(&appWindow);
    slider.setMinimum(0);
    slider.setMaximum(100);
    slider.resize(200, 10);
    layout->addWidget(&paint);
    layout->addWidget(&slider);
    appWindow.setFixedSize (200, 250);
    appWindow.move (2000, 500);
    QObject::connect(&slider, &QSlider::valueChanged, [&slider, &paint](int newValue){
        if (newValue >= 0 && newValue <= 33)
            paint.setGreen();
        else if (newValue >= 34 && newValue <= 66)
            paint.setYellow();
        else paint.setRed();
    });
    slider.show();
    appWindow.show();
    delete layout;
    return app.exec();
}
#include "main.moc"