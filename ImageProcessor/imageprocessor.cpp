#include "imageprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QDialog>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent),
    zoomFactor(1.0)  // 初始化 zoomFactor
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300,200);
    initPixmap->fill(QColor(255,255,255));
    imgWin->resize(300,200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);
    createActions();
    createMenus();
    createToolBars();
}

ImageProcessor::~ImageProcessor()
{

}
void ImageProcessor::createActions()
{
    openFileAction=new QAction(QStringLiteral("開啟檔案&0"),this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));


    zoomInAction = new QAction(QStringLiteral("放大"), this); // 放大操作
    zoomInAction->setStatusTip(QStringLiteral("放大影像"));
    connect(zoomInAction, &QAction::triggered, this, &ImageProcessor::enlargeImage);

    zoomOutAction = new QAction(QStringLiteral("縮小"), this); // 縮小操作
    zoomOutAction->setStatusTip(QStringLiteral("縮小影像"));
    connect(zoomOutAction, &QAction::triggered, this, &ImageProcessor::shrinkImage);

    exitAction= new QAction(QStringLiteral("結束&Q"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
}
void ImageProcessor::createMenus()
{
    fileMenu=menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);

    toolMenu = menuBar()->addMenu(QStringLiteral("工具&T"));
    toolMenu->addAction(zoomInAction);  // 添加放大操作
    toolMenu->addAction(zoomOutAction); // 添加缩小操作
}
void ImageProcessor::createToolBars()
{
    fileTool= addToolBar("file");
    fileTool->addAction(openFileAction);

    zoomTool = addToolBar("zoom");
    zoomTool->addAction(zoomInAction);  // 工具欄添加放大操作
    zoomTool->addAction(zoomOutAction); // 工具欄添加缩小操作
}
void ImageProcessor::loadFile(QString filename)
{
    qDebug()<<QString("file name:%1").arg(filename);
    //QByteArray ba=filename.toLatin1();
    //printf("FN:%s\n",(char *) ba.data());
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
}
void ImageProcessor::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(this,QStringLiteral("開啟影像"),tr("."),"bmp(*.bmp);;png(*.png)"";;Jpeg(*.jpg)");
    if(img.isNull())
    {
        loadFile(filename);
    }
    /*else
    {
        ImageProcessor *newIPWin = new ImageProcessor();
        newIPWin->show();
        newIPWin->loadFile(filename);
    }*/
}

void ImageProcessor::enlargeImage()
{
    if (!img.isNull())
    {
        // 放大圖像（放大一倍）
        QSize newSize = img.size() * 2; // 放大一倍
        QImage enlargedImg = img.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 創建一个新的 Dialog 來顯示放大的圖像
        QDialog *zoomDialog = new QDialog(this);
        zoomDialog->setWindowTitle("放大圖像");

        QLabel *zoomLabel = new QLabel(zoomDialog);
        zoomLabel->setPixmap(QPixmap::fromImage(enlargedImg));
        zoomLabel->setAlignment(Qt::AlignCenter);

        QVBoxLayout *layout = new QVBoxLayout(zoomDialog);
        layout->addWidget(zoomLabel);
        zoomDialog->setLayout(layout);
        zoomDialog->resize(600, 400);
        zoomDialog->exec(); // 顯示放大窗口
    }
}

void ImageProcessor::shrinkImage()
{
    if (!img.isNull())
    {
        // 缩小圖像（缩小一倍）
        QSize newSize = img.size() / 2; // 缩小一倍
        QImage shrunkImg = img.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 創建一个新的 Dialog 來顯示缩小的圖像
        QDialog *zoomDialog = new QDialog(this);
        zoomDialog->setWindowTitle("縮小圖像");

        QLabel *zoomLabel = new QLabel(zoomDialog);
        zoomLabel->setPixmap(QPixmap::fromImage(shrunkImg));
        zoomLabel->setAlignment(Qt::AlignCenter);

        QVBoxLayout *layout = new QVBoxLayout(zoomDialog);
        layout->addWidget(zoomLabel);
        zoomDialog->setLayout(layout);
        zoomDialog->resize(600, 400);
        zoomDialog->exec(); // 顯示缩小窗口
    }
}
