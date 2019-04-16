#include "dataviewer.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <QDomDocument>

#include <qgsvectorlayer.h>
#include <qgsrasterlayer.h>
#include <qgsmaptoolzoom.h>
#include <qgsmaptoolpan.h>
#include <qgsrectangle.h>


DataViewer::DataViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_mapCanvas = new QgsMapCanvas();
	this->setCentralWidget(m_mapCanvas);

	m_zoomInTool = new QgsMapToolZoom(m_mapCanvas, false);
	m_zoomOutTool = new QgsMapToolZoom(m_mapCanvas, true);
	m_panTool = new QgsMapToolPan(m_mapCanvas);

	m_bookmarkDlg = new BookMarkDialog(m_mapCanvas);
}

DataViewer::~DataViewer()
{
	
}

void DataViewer::on_actionOpenProject_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ�񹤳��ļ�"),
		"", "QGIS project (*.qgz)");
	QFileInfo fi(filename);
	if (!fi.exists()) { return; }
	QDomDocument domDoc(filename);
	m_mapCanvas->readProject(domDoc);
}

void DataViewer::on_actionSaveProject_triggered()
{
	QString filename = QFileDialog::getSaveFileName(this, QStringLiteral("���̱���Ϊ"),
		"", "QGIS project (*.qgz)");
	QFile file(filename);
	file.open(QIODevice::WriteOnly);
	file.close();
	QDomDocument domDoc(filename);
	m_mapCanvas->writeProject(domDoc);
}

void DataViewer::on_actionSaveAsProject_triggered()
{

}

void DataViewer::on_actionAddVectorData_triggered()
{
	QString layerPath = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ��ʸ������"), "", "shapefile (*.shp)");
	QFileInfo fi(layerPath);
	if (!fi.exists()) { return; }
	QString layerBaseName = fi.baseName(); // ͼ������

	QgsVectorLayer* vecLayer = new QgsVectorLayer(layerPath, layerBaseName);
	if (!vecLayer) { return; }
	if (!vecLayer->isValid())
	{
		QMessageBox::information(0, "", "layer is invalid");
		return;
	}
	m_layerList << vecLayer;
	m_mapCanvas->setLayers(m_layerList);
	m_mapCanvas->setExtent(vecLayer->extent());
	m_mapCanvas->refresh();
}

void DataViewer::on_actionAddRasterData_triggered()
{
	QString layerPath = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ��դ������"), "", "Image (*.img *.tif *.tiff)");
	QFileInfo fi(layerPath);
	if (!fi.exists()) { return; }
	QString layerBaseName = fi.baseName(); // ͼ������

	QgsRasterLayer* vecLayer = new QgsRasterLayer(layerPath, layerBaseName);
	if (!vecLayer) { return; }
	if (!vecLayer->isValid())
	{
		QMessageBox::information(0, "", "layer is invalid");
		return;
	}
	m_layerList << vecLayer;
	m_mapCanvas->setLayers(m_layerList);
	m_mapCanvas->setExtent(vecLayer->extent());
	m_mapCanvas->refresh();
}

void DataViewer::on_actionAddWmsLayer_triggered()
{

}

void DataViewer::on_actionAddWfsLayer_triggered()
{

}

void DataViewer::on_actionAddWcsLayer_triggered()
{

}

void DataViewer::on_actionZoomIn_triggered()
{
	m_mapCanvas->setMapTool(m_zoomInTool);
}

void DataViewer::on_actionZoomOut_triggered()
{
	m_mapCanvas->setMapTool(m_zoomOutTool);
}

void DataViewer::on_actionPan_triggered()
{
	m_mapCanvas->setMapTool(m_panTool);
}

void DataViewer::on_actionZoomActual_triggered()
{
	
}

void DataViewer::on_actionFullExtent_triggered()
{
	m_mapCanvas->zoomToFullExtent();
}

void DataViewer::on_actionNewBookmark_triggered()
{
	bool ok;
	QString text = QInputDialog::getText(this, QStringLiteral("������ǩ����"), "", QLineEdit::Normal, "", &ok);
	if (ok && !text.isEmpty())
	{
		m_bookmarkDlg->add(text, m_mapCanvas->extent());
	}
}

void DataViewer::on_actionShowBookmarks_triggered()
{
	m_bookmarkDlg->show();
}



