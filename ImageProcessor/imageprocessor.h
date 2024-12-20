#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>

class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);

private slots:
    void showOpenFile();
    void zoomIn();  // 放大
    void zoomOut(); // 縮小

private:
    void applyScale(); // 根據比例更新圖片

    QWidget *central;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QToolBar *fileTool;
    QToolBar *viewTool;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    double scaleFactor; // 影像縮放比例
};

#endif // IMAGEPROCESSOR_H
