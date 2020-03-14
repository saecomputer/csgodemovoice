#include "frmmain.h"
#include "update.h"
#include "match.h"

#include <QApplication>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qRegisterMetaType<Match>();

    app.setStyle(QStyleFactory::create("Fusion"));
    app.setOrganizationName("SAE Computer");
    app.setOrganizationDomain("sae.computer");
    app.setApplicationName("CSGO Demovoice");

    int id = QFontDatabase::addApplicationFont(":/res/font.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont _font(family, 11);
    qApp->setFont(_font);

    QPalette palette;
    QColor colorFiord = QColor(58,71,106);
    QColor colorMartinique = QColor(48,51,88);
    QColor colorBlackRussian = QColor(0,1,35);
    QColor colorTenn = QColor(212,85,0);
    QColor colorKoromiko = QColor(255,189,108);

    palette.setColor(QPalette::Window, colorFiord);
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, colorMartinique);
    palette.setColor(QPalette::AlternateBase, colorFiord);
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Disabled, QPalette::Text, colorBlackRussian);
    palette.setColor(QPalette::Button, colorFiord);
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, colorBlackRussian);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, colorTenn);
    palette.setColor(QPalette::Highlight, colorKoromiko);
    palette.setColor(QPalette::HighlightedText, Qt::black);
    palette.setColor(QPalette::Disabled, QPalette::HighlightedText, colorBlackRussian);

    app.setPalette(palette);
    app.setStyleSheet("QToolTip { color: #ffbd6c; background-color: #3a476a; border: 1px solid #303358; }");

    Update update;
    if(update.check())
    {
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setText("This version is out of date please update.");
        msgBox->exec();
        update.startUpdater();
        return 0;
    }

    FrmMain w;
    w.show();

    return app.exec();
}
