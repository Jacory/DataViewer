#pragma once
#include <qdialog.h>
#include "ui_bookmark.h"
#include <QListView>
#include <QStringListModel>

class QgsMapCanvas;
class QgsRectangle;

// ��ǩ��������
class BookMarkDialog : public QDialog
{
	Q_OBJECT
public:
	BookMarkDialog(QgsMapCanvas* mapCanvas);
	~BookMarkDialog();

	// �����ǩ
	void add(QString name, QgsRectangle rect);

signals:
	// �б�����ź�
	void listUpdate();

protected slots:
	// ������ǩ�б�
	void update();
	
	void on_zoomToButton_clicked();
	void on_deleteButton_clicked();

private:
	Ui::BookMarkDialog ui;

	QgsMapCanvas* m_mapCanvas = NULL;
	// ��ǩ�洢���ݽṹ����QMap�洢������ǩ���ƺͶ�Ӧ�ĵ�ͼ��ͼ���������
	QMap<QString, QgsRectangle> m_bookmarks;
	// ��ǩ�б������ģ��
	QStringListModel* mStringListModel = NULL;
};

