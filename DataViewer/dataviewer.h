#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QtWidgets/QMainWindow>
#include "ui_dataviewer.h"
#include "BookmarkDialog.h"

#include <qgsmapcanvas.h>

class QgsMapTool;

// ���ݲ鿴��������
class DataViewer : public QMainWindow
{
	Q_OBJECT

public:
	DataViewer(QWidget *parent = 0);
	~DataViewer();

public slots:
	// �򿪹���
	void on_actionOpenProject_triggered();
	// ���湤��
	void on_actionSaveProject_triggered();
	// ��湤��
	void on_actionSaveAsProject_triggered();

	// ���ʸ������
	void on_actionAddVectorData_triggered();
	// ���դ������
	void on_actionAddRasterData_triggered();
	// ���WMSͼ��
	void on_actionAddWmsLayer_triggered();
	// ���WFSͼ��
	void on_actionAddWfsLayer_triggered();
	// ���WCSͼ��
	void on_actionAddWcsLayer_triggered();

	// ʹ�õ�ͼ�Ŵ󹤾�
	void on_actionZoomIn_triggered();
	// ʹ�õ�ͼ��С����
	void on_actionZoomOut_triggered();
	// ʹ�õ�ͼ���ι���
	void on_actionPan_triggered();
	// ���ŵ�ͼ��ʵ�ʱ���
	void on_actionZoomActual_triggered();
	// ���ŵ�ͼ��ȫͼ��Χ
	void on_actionFullExtent_triggered();
	// �����µĵ�ͼ��ǩ
	void on_actionNewBookmark_triggered();
	// ��ʾ��ͼ��ǩ������
	void on_actionShowBookmarks_triggered();

private:
	Ui::DataViewerClass ui;

	// ��ͼ����
	QgsMapCanvas* m_mapCanvas;
	// ͼ���б�
	QList<QgsMapLayer*> m_layerList;

	// ��ͼ���Ź���
	QgsMapTool* m_zoomInTool;
	QgsMapTool* m_zoomOutTool;
	// ��ͼ�������
	QgsMapTool* m_panTool;

	// ��ǩ����
	BookMarkDialog* m_bookmarkDlg;
};



#endif // DATAVIEWER_H
