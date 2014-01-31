#include "PlayerDetails.h"

//cwst_qt * fparent;

void PlayerDetails::okButton()
{
	this->close();
}

PlayerDetails::PlayerDetails(PlayerProfile * pp, cwst_qt *parent) : QDialog(parent)
{
	ui.setupUi(this);
	//pparent = parent;

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okButton()));
	ui.tb_level->setText(QString::number(pp->Level));
	ui.tb_ArmorMultiplier->setText(QString::number(pp->ArmorMultiplier));
	ui.tb_DamageMultiplier->setText(QString::number(pp->DamageMultiplier));
	ui.tb_hp->setText(QString::number(pp->HP));
	ui.tb_MaxHPMultiplier->setText(QString::number(pp->MaxHPMultiplier));
	ui.tb_mp->setText(QString::number(pp->MP));
	ui.tb_ResistanceMultiplier->setText(QString::number(pp->ResistanceMultiplier));
	ui.tb_ShootSpeed->setText(QString::number(pp->ShootSpeed));
	ui.tb_username->setText(QString::fromStdString(pp->Name));
	ui.tb_xp->setText(QString::number(pp->CurrentXP));
}


PlayerDetails::~PlayerDetails(void)
{
}
