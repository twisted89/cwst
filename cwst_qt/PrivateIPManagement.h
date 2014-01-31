
//PrivateIPManagement

#ifndef PRIVATEIPMANAGEMENT_H
#define PRIVATEIPMANAGEMENT_H

#include "cwst_qt.h"
#include <QDialog>
#include "ui_PrivateIPManagementForm.h"


class PrivateIPManagement : public QDialog
{
	Q_OBJECT
public:
	explicit PrivateIPManagement::PrivateIPManagement(cwst_qt *parent = 0);
	Ui::PrivateIPDialog ui;
private:
	QMenu * context;
	QAction * RemovePrivateIP;
	QAction *a;
	private slots:
		void contextMenuEvent(const QPoint &pos);
		void okButton();
		void CancelButton();
		void addIPbutton();
};

#endif

