#ifndef BANMANAGEMENT_H
#define BANMANAGEMENT_H

#include "cwst_qt.h"
#include <QDialog>
#include "ui_BanManagementForm.h"


class BanManagement : public QDialog
{
	Q_OBJECT
public:
	explicit BanManagement::BanManagement(cwst_qt *parent = 0);
	Ui::BannedIPDialog ui;
private:
	QMenu * context;
	QAction * RemoveBan;
	QAction *a;
	private slots:
		void contextMenuEvent(const QPoint &pos);
		void okButton();
		void CancelButton();
		void addIPbutton();
};

#endif

