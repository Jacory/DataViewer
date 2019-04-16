#include "BookmarkDialog.h"
#include <QStringListModel>

#include "qgsmapcanvas.h"

BookMarkDialog::BookMarkDialog(QgsMapCanvas* mapCanvas = NULL)
	: m_mapCanvas(mapCanvas)
{
	ui.setupUi(this);

	mStringListModel = new QStringListModel(this);
	ui.listView->setModel(mStringListModel);

	// �����б�����źź;�����²�������
	connect(this, SIGNAL(listUpdate()), this, SLOT(update()));
}

BookMarkDialog::~BookMarkDialog()
{
	
}

void BookMarkDialog::add(QString name, QgsRectangle rect)
{
	// �����ǩ֮�󣬷���������ǩ�б��źţ���ʾ��Ҫ�����б�
	m_bookmarks.insert(name, rect);
	emit listUpdate();
}

void BookMarkDialog::on_zoomToButton_clicked()
{
	// ��ȡ�б�ѡ�е���ǩ���ƣ��Դ��ҵ���Ӧ�ĵ�ͼ��ͼ��Χ���Σ�����ת���÷�Χ
	QModelIndexList selIndexList = ui.listView->selectionModel()->selectedIndexes();
	if (selIndexList.count() <= 0) return;
	QgsRectangle rect = m_bookmarks[mStringListModel->data(selIndexList[0]).toString()];
	m_mapCanvas->setExtent(rect, false);
	m_mapCanvas->refresh();
}

void BookMarkDialog::on_deleteButton_clicked()
{
	// ��ȡ�б�ѡ�е���ǩ���ƣ���ɾ����ѡ����
	QModelIndexList selIndexList = ui.listView->selectionModel()->selectedIndexes();
	if (selIndexList.count() <= 0) return;
	m_bookmarks.remove(mStringListModel->data(selIndexList[0]).toString());
	
	emit listUpdate();
}

void BookMarkDialog::update()
{
	mStringListModel->setStringList(m_bookmarks.keys());
}

