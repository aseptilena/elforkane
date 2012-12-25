/****************************************************************************
//   elforkane Copyright (C) 2012 yahia nouah <yahiaui@gmail.com>
//
//      This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//      This is free software, and you are welcome to redistribute it
//      under certain conditions; type `show c' for details.
//
//  The hypothetical commands `show w' and `show c' should show the appropriate
//  parts of the General Public License.  Of course, your program's commands
//  might be different; for a GUI interface, you would use an "about box".
//
//    You should also get your employer (if you work as a programmer) or school,
//  if any, to sign a "copyright disclaimer" for the program, if necessary.
//  For more information on this, and how to apply and follow the GNU GPL, see
//  <http://www.gnu.org/licenses/>.
//
//    The GNU General Public License does not permit incorporating your program
//  into proprietary programs.  If your program is a subroutine library, you
//  may consider it more useful to permit linking proprietary applications with
//  the library.  If this is what you want to do, use the GNU Lesser General
//  Public License instead of this License.  But first, please read
//  <http://www.gnu.org/philosophy/why-not-lgpl.html>.
// ----------------------------------------------------------
** If you have questions regarding the use of this file, please contact
** yahia nouah (yahiaui@gmail.com)
** $elforkane_END_LICENSE$
**
****************************************************************************/
#include "dialogaddreciter.h"
#include "ui_dialogaddreciter.h"
#include<QFile>
#include<QFileDialog>
DialogAddReciter::DialogAddReciter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddReciter)
{
    ui->setupUi(this);
    ui->comboBoxRiwayat->addItem(trUtf8("Default hafs"),("default"));
    ui->comboBoxRiwayat->addItem(trUtf8("Riwayat hafs"),("hafs"));
    ui->comboBoxRiwayat->addItem(trUtf8("Riwayat warsh"),("warsh"));
    ui->comboBoxRiwayat->addItem(trUtf8("Riwayat hafs by colors"),("hafs-colors"));
    ui->comboBoxRiwayat->addItem(trUtf8("Riwayat warsh by colors"),("warsh-colors"));
}

DialogAddReciter::~DialogAddReciter()
{
    delete ui;
}

void DialogAddReciter::on_toolButtonFileName_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QString(),
                                                    QFileDialog::ShowDirsOnly
                                                    |QFileDialog::DontResolveSymlinks);
   if(!dirName.isEmpty())
    ui->lineEditFileName->setText(dirName);
}

void DialogAddReciter::on_buttonBox_clicked(QAbstractButton *button)
{
     if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Ok){
         if(ui->lineEditReciterName->text().isEmpty())
             return;
         if(ui->lineEditFileName->text().isEmpty())
             return;
     }
   reciterName=ui->lineEditReciterName->text();
   dirName=ui->lineEditFileName->text();
   int index=ui->comboBoxRiwayat->currentIndex();
   riwayaName=ui->comboBoxRiwayat->itemData(index).toString();
   urlName=ui->lineEditUrl->text();
   dataName=dirName+"|"+urlName+"|"+riwayaName;
   this->accept();
}
//--------set----------------------
void DialogAddReciter::setReceterName(QString name)
{
    ui->lineEditReciterName->setText(name);
}

void DialogAddReciter::setDirName(QString name)
{
    ui->lineEditFileName->setText(name);
}

void DialogAddReciter::setUrlName(QString name)
{
    ui->lineEditUrl->setText(name);

}

void DialogAddReciter::setRiwayaName(QString arg)
{
    int ind=0;
    if(arg=="default"){
        ind=0;
    }else if(arg=="hafs"){
        ind=1;
    }else if(arg=="warsh"){
        ind=2;
    }else if(arg=="hafs-colors"){
        ind=3;
    }else if(arg=="warsh-colors"){
        ind=4;
    }

ui->comboBoxRiwayat->setCurrentIndex(ind);

}
//----get-----
QString DialogAddReciter::getReciterName()
{
    return reciterName;
}
QString DialogAddReciter::getDataName()
{
    return dataName;
}
