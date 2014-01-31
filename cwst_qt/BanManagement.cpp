#include "BanManagement.h"

cwst_qt * pparent;

void BanManagement::addIPbutton()
{   
	if (!validateIpAddress(ui.tb_IP->text().toStdString()))
		::MessageBoxA( 0, "Invalid IP", "IP validation error", MB_OK);
	else
	{
		ui.lb_bannedIPs->addItem(ui.tb_IP->text());
		ui.tb_IP->clear();
	}
}

void BanManagement::okButton()
{   
	pparent->BlacklistArray.clear();
	for (int i = 0; i < ui.lb_bannedIPs->count(); i++)
	{
		pparent->BlacklistArray.push_back(ui.lb_bannedIPs->item(i)->text().toStdString());
	}
	std::vector<std::string>::const_iterator iter;
	std::string bannedIPs;
	for (iter= pparent->BlacklistArray.begin(); iter!= pparent->BlacklistArray.end(); iter++)
	{
		std::string bIP = *iter;
		if (iter != pparent->BlacklistArray.begin())
			bannedIPs += ", ";
		bannedIPs += bIP;
	}

	char * cBannedIPs = new char[bannedIPs.size() + 1];
	std::copy(bannedIPs.begin(), bannedIPs.end(), cBannedIPs);
	cBannedIPs[bannedIPs.size()] = '\0'; // don't forget the terminating 0
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteString("IP", "BannedIPs", cBannedIPs); 
	delete[] cBannedIPs;
	this->accept();
}

void BanManagement::CancelButton()
{   
	this->close();
}

void BanManagement::contextMenuEvent(const QPoint &pos)
{   
	QList<QModelIndex> indexes = ui.lb_bannedIPs->selectionModel()->selectedRows();
	if (indexes.count() < 1)
		return;
	a = context->exec(ui.lb_bannedIPs->viewport()->mapToGlobal(pos));
	if (a == RemoveBan)
	{	
		qDeleteAll(ui.lb_bannedIPs->selectedItems());
	}
}


BanManagement::BanManagement(cwst_qt *parent) :
	QDialog(parent)
{
	ui.setupUi(this);
	pparent = parent;
	context = new QMenu(this);
	RemoveBan = context->addAction(tr("Remove"));    
	ui.lb_bannedIPs->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.lb_bannedIPs, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuEvent(QPoint)));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okButton()));
	connect(ui.Cancelbtn, SIGNAL(clicked()), this, SLOT(CancelButton()));
	connect(ui.AddIPbtn, SIGNAL(clicked()), this, SLOT(addIPbutton()));

	QString qIP;
	for (std::string &blip : parent->BlacklistArray) // access by reference to avoid copying
	{  
		qIP = QString::fromStdString(blip);
		ui.lb_bannedIPs->addItem(qIP);
	}
}