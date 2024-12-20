#include "imageprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent), scaleFactor(1.0) // 初始比例為 1.0
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    imgWin->setScaledContents(true); // 啟用圖片內容縮放
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);
    createActions();
    createMenus();
    createToolBars();
}

ImageProcessor::~ImageProcessor() {}

void ImageProcessor::createActions()
{
    openFileAction = new QAction(QStringLiteral("開啟檔案(&O)"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    connect(openFileAction, &QAction::triggered, this, &ImageProcessor::showOpenFile);

    exitAction = new QAction(QStringLiteral("結束(&Q)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, &QAction::triggered, this, &ImageProcessor::close);

    zoomInAction = new QAction(QStringLiteral("放大"), this);
    zoomInAction->setShortcut(tr("Ctrl+L"));
    connect(zoomInAction, &QAction::triggered, this, &ImageProcessor::zoomIn);

    zoomOutAction = new QAction(QStringLiteral("縮小"), this);
    zoomOutAction->setShortcut(tr("Ctrl+D"));
    connect(zoomOutAction, &QAction::triggered, this, &ImageProcessor::zoomOut);
}

void ImageProcessor::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案(&F)"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);

    viewMenu = menuBar()->addMenu(QStringLiteral("工具(&T)"));
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
}

void ImageProcessor::createToolBars()
{
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);

    viewTool = addToolBar("View");
    viewTool->addAction(zoomInAction);
    viewTool->addAction(zoomOutAction);
}

void ImageProcessor::loadFile(QString filename)
{
    if (img.load(filename)) {
        scaleFactor = 1.0; // 每次載入新檔案時重置比例
        imgWin->setPixmap(QPixmap::fromImage(img).scaled(img.size() * scaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void ImageProcessor::showOpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    QStringLiteral("開啟影像"),
                                                    ".",
                                                    "影像檔案 (*.bmp *.png *.jpg *.jpeg)");
    if (!filename.isEmpty()) {
        loadFile(filename);
    }
}

void ImageProcessor::zoomIn()
{
    scaleFactor *= 1.2; // 增加 20%
    applyScale();
}

void ImageProcessor::zoomOut()
{
    scaleFactor /= 1.2; // 減少 20%
    // 限制最小比例，避免縮到看不見
    if (scaleFactor < 0.1) {
        scaleFactor = 0.1;
    }
    applyScale();
}

void ImageProcessor::applyScale()
{
    if (!img.isNull()) {
        // 根據 scaleFactor 更新圖片顯示
        QSize newSize = img.size() * scaleFactor;
        imgWin->setPixmap(QPixmap::fromImage(img).scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imgWin->resize(newSize); // 同時調整 QLabel 的大小
    }
}
