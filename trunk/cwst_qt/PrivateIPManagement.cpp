#include "PrivateIPManagement.h"

cwst_qt * pparent1;

void PrivateIPManagement::addIPbutton()
{   
	if (!validateIpAddress(ui.tb_IP->text().toStdString()))
		::MessageBoxA( 0, "Invalid IP", "IP validation error", MB_OK);
	else
	{
		ui.lb_privateIPs->addItem(ui.tb_IP->text());
		ui.tb_IP->clear();
	}
}

void PrivateIPManagement::okButton()
{   
	pparent1->PrivateIPArray.clear();
	for (int i = 0; i < ui.lb_privateIPs->count(); i++)
	{
		pparent1->PrivateIPArray.push_back(ui.lb_privateIPs->item(i)->text().toStdString());
	}
	std::vector<std::string>::const_iterator iter;
	std::string PrivateIPs;
	for (iter= pparent1->PrivateIPArray.begin(); iter!= pparent1->PrivateIPArray.end(); iter++)
	{
		std::string bIP = *iter;
		if (iter != pparent1->PrivateIPArray.begin())
			PrivateIPs += ", ";
		PrivateIPs += bIP;
	}

	char * cPrivateIPs = new char[PrivateIPs.size() + 1];
	std::copy(PrivateIPs.begin(), PrivateIPs.end(), cPrivateIPs);
	cPrivateIPs[PrivateIPs.size()] = '\0'; // don't forget the terminating 0
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteString("IP", "PrivateIPs", cPrivateIPs); 
	delete[] cPrivateIPs;
	this->accept();
}

void PrivateIPManagement::CancelButton()
{   
	this->close();
}

void PrivateIPManagement::contextMenuEvent(const QPoint &pos)
{   
	QList<QModelIndex> indexes = ui.lb_privateIPs->selectionModel()->selectedRows();
	if (indexes.count() < 1)
		return;
	a = context->exec(ui.lb_privateIPs->viewport()->mapToGlobal(pos));
	if (a == RemovePrivateIP)
	{	
		qDeleteAll(ui.lb_privateIPs->selectedItems());
	}
}

PrivateIPManagement::PrivateIPManagement(cwst_qt *parent) :
	QDialog(parent)
{
	ui.setupUi(this);
	pparent1 = parent;
	context = new QMenu(this);
	RemovePrivateIP = context->addAction(tr("Remove"));    
	ui.lb_privateIPs->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.lb_privateIPs, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuEvent(QPoint)));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okButton()));
	connect(ui.Cancelbtn, SIGNAL(clicked()), this, SLOT(CancelButton()));
	connect(ui.AddIPbtn, SIGNAL(clicked()), this, SLOT(addIPbutton()));

	QString qIP;
	for (std::string &pip : parent->PrivateIPArray) // access by reference to avoid copying
	{  
		qIP = QString::fromStdString(pip);
		ui.lb_privateIPs->addItem(qIP);
	}
}
