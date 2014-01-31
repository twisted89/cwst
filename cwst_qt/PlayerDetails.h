#ifndef PLAYERDETAILS_H
#define PLAYERDETAILS_H

#include "cwst_qt.h"
#include <QDialog>
#include "ui_PlayerDetails.h"
#include "PlayerProfile.h"

class PlayerDetails : public QDialog
{
	Q_OBJECT
public:
	explicit PlayerDetails::PlayerDetails( PlayerProfile * pp, cwst_qt *parent = 0);
	PlayerDetails::~PlayerDetails(void);
	Ui::PlayerDetails ui;
private:
	private slots:
		void okButton();
};

#endif

