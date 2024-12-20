#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QACtion>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include <QFileDialog>  // 用于文件對話框
#include <QDialog>      // 用于創建放大/縮小新窗口
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
    void showOpenFile();  // 打開文件

    void enlargeImage();  // 放大圖像並彈出新窗口
    void shrinkImage();   // 縮小圖像並彈出新窗口

private:
    QWidget *central;
    QMenu *fileMenu;
    QMenu *toolMenu;      // 添加工具菜單
    QToolBar *fileTool;
    QToolBar *zoomTool;   // 添加放大/缩小工具欄
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomInAction;  // 放大操作
    QAction *zoomOutAction; // 缩小操作

    double zoomFactor;  // 用于紀錄圖像的缩放比例
};
#endif // IMAGEPROCESSOR_H
