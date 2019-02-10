/********************************************************************************
** Form generated from reading UI file 'pp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PP_H
#define UI_PP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
  QAction *actionQuit;
  QAction *actionLoadWallet;
  QWidget *Wallet;
  QVBoxLayout *verticalLayout;
  QGroupBox *info;
  QHBoxLayout *horizontalLayout;
  QFormLayout *formLayout;
  QLabel *versionLabel;
  QLabel *walletVersion;
  QLabel *label_13;
  QLabel *walletPeriod;
  QLabel *label_2;
  QLabel *walletAddress;
  QLabel *label_6;
  QLabel *walletFeeAddress;
  QLabel *label_5;
  QTableView *userInfoView;
  QTabWidget *tabWidget;
  QWidget *Remove;
  QVBoxLayout *verticalLayout_2;
  QFormLayout *formLayout_2;
  QLabel *label_3;
  QLabel *label_4;
  QLabel *label_8;
  QComboBox *whoToRemove;
  QPlainTextEdit *feeTx;
  QPlainTextEdit *walletTx;
  QSplitter *splitter;
  QPushButton *removeActionButton;
  QPushButton *loadRemovalExampleButton;
  QWidget *tab_2;
  QVBoxLayout *verticalLayout_3;
  QFormLayout *formLayout_3;
  QLabel *label;
  QComboBox *whoToAppeal;
  QLabel *label_9;
  QPlainTextEdit *lifesignalTx;
  QSplitter *splitter_2;
  QPushButton *appealActionButton;
  QPushButton *loadAppealExampleButton;
  QTextBrowser *output;
  QHBoxLayout *horizontalLayout_2;
  QHBoxLayout *lower;
  QSpacerItem *horizontalSpacer;
  QLabel *label_7;
  QMenuBar *menubar;
  QMenu *menuFile;
  QMenu *menuHelp;
  QStatusBar *statusbar;
  QToolBar *toolBar;

  void setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(1000, 1616);
    MainWindow->setMinimumSize(QSize(1000, 0));
    MainWindow->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    actionQuit = new QAction(MainWindow);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    QIcon icon;
    QString iconThemeName = QString::fromUtf8("application-exit");
    if (QIcon::hasThemeIcon(iconThemeName)) {
      icon = QIcon::fromTheme(iconThemeName);
    } else {
      icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    actionQuit->setIcon(icon);
    actionLoadWallet = new QAction(MainWindow);
    actionLoadWallet->setObjectName(QString::fromUtf8("actionLoadWallet"));
    QIcon icon1;
    iconThemeName = QString::fromUtf8("document-open");
    if (QIcon::hasThemeIcon(iconThemeName)) {
      icon1 = QIcon::fromTheme(iconThemeName);
    } else {
      icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    actionLoadWallet->setIcon(icon1);
    Wallet = new QWidget(MainWindow);
    Wallet->setObjectName(QString::fromUtf8("Wallet"));
    verticalLayout = new QVBoxLayout(Wallet);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    info = new QGroupBox(Wallet);
    info->setObjectName(QString::fromUtf8("info"));
    horizontalLayout = new QHBoxLayout(info);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    formLayout = new QFormLayout();
    formLayout->setObjectName(QString::fromUtf8("formLayout"));
    versionLabel = new QLabel(info);
    versionLabel->setObjectName(QString::fromUtf8("versionLabel"));

    formLayout->setWidget(0, QFormLayout::LabelRole, versionLabel);

    walletVersion = new QLabel(info);
    walletVersion->setObjectName(QString::fromUtf8("walletVersion"));
    QFont font;
    font.setFamily(QString::fromUtf8("Monospace"));
    walletVersion->setFont(font);

    formLayout->setWidget(0, QFormLayout::FieldRole, walletVersion);

    label_13 = new QLabel(info);
    label_13->setObjectName(QString::fromUtf8("label_13"));

    formLayout->setWidget(1, QFormLayout::LabelRole, label_13);

    walletPeriod = new QLabel(info);
    walletPeriod->setObjectName(QString::fromUtf8("walletPeriod"));
    walletPeriod->setFont(font);

    formLayout->setWidget(1, QFormLayout::FieldRole, walletPeriod);

    label_2 = new QLabel(info);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

    walletAddress = new QLabel(info);
    walletAddress->setObjectName(QString::fromUtf8("walletAddress"));
    walletAddress->setFont(font);

    formLayout->setWidget(2, QFormLayout::FieldRole, walletAddress);

    label_6 = new QLabel(info);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

    walletFeeAddress = new QLabel(info);
    walletFeeAddress->setObjectName(QString::fromUtf8("walletFeeAddress"));
    walletFeeAddress->setFont(font);

    formLayout->setWidget(3, QFormLayout::FieldRole, walletFeeAddress);

    label_5 = new QLabel(info);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

    userInfoView = new QTableView(info);
    userInfoView->setObjectName(QString::fromUtf8("userInfoView"));
    userInfoView->setFont(font);
    userInfoView->setSortingEnabled(true);

    formLayout->setWidget(4, QFormLayout::FieldRole, userInfoView);

    horizontalLayout->addLayout(formLayout);

    verticalLayout->addWidget(info);

    tabWidget = new QTabWidget(Wallet);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setElideMode(Qt::ElideNone);
    tabWidget->setTabBarAutoHide(false);
    Remove = new QWidget();
    Remove->setObjectName(QString::fromUtf8("Remove"));
    verticalLayout_2 = new QVBoxLayout(Remove);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    formLayout_2 = new QFormLayout();
    formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
    label_3 = new QLabel(Remove);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

    label_4 = new QLabel(Remove);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

    label_8 = new QLabel(Remove);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    formLayout_2->setWidget(4, QFormLayout::LabelRole, label_8);

    whoToRemove = new QComboBox(Remove);
    whoToRemove->setObjectName(QString::fromUtf8("whoToRemove"));

    formLayout_2->setWidget(0, QFormLayout::FieldRole, whoToRemove);

    feeTx = new QPlainTextEdit(Remove);
    feeTx->setObjectName(QString::fromUtf8("feeTx"));
    feeTx->setFont(font);

    formLayout_2->setWidget(2, QFormLayout::FieldRole, feeTx);

    walletTx = new QPlainTextEdit(Remove);
    walletTx->setObjectName(QString::fromUtf8("walletTx"));
    walletTx->setFont(font);

    formLayout_2->setWidget(4, QFormLayout::FieldRole, walletTx);

    verticalLayout_2->addLayout(formLayout_2);

    splitter = new QSplitter(Remove);
    splitter->setObjectName(QString::fromUtf8("splitter"));
    splitter->setOrientation(Qt::Horizontal);
    removeActionButton = new QPushButton(splitter);
    removeActionButton->setObjectName(QString::fromUtf8("removeActionButton"));
    QIcon icon2;
    iconThemeName = QString::fromUtf8("system-run");
    if (QIcon::hasThemeIcon(iconThemeName)) {
      icon2 = QIcon::fromTheme(iconThemeName);
    } else {
      icon2.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    removeActionButton->setIcon(icon2);
    splitter->addWidget(removeActionButton);
    loadRemovalExampleButton = new QPushButton(splitter);
    loadRemovalExampleButton->setObjectName(
        QString::fromUtf8("loadRemovalExampleButton"));
    splitter->addWidget(loadRemovalExampleButton);

    verticalLayout_2->addWidget(splitter);

    tabWidget->addTab(Remove, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    verticalLayout_3 = new QVBoxLayout(tab_2);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    formLayout_3 = new QFormLayout();
    formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
    label = new QLabel(tab_2);
    label->setObjectName(QString::fromUtf8("label"));

    formLayout_3->setWidget(0, QFormLayout::LabelRole, label);

    whoToAppeal = new QComboBox(tab_2);
    whoToAppeal->setObjectName(QString::fromUtf8("whoToAppeal"));

    formLayout_3->setWidget(0, QFormLayout::FieldRole, whoToAppeal);

    label_9 = new QLabel(tab_2);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    formLayout_3->setWidget(1, QFormLayout::LabelRole, label_9);

    lifesignalTx = new QPlainTextEdit(tab_2);
    lifesignalTx->setObjectName(QString::fromUtf8("lifesignalTx"));
    lifesignalTx->setFont(font);

    formLayout_3->setWidget(1, QFormLayout::FieldRole, lifesignalTx);

    verticalLayout_3->addLayout(formLayout_3);

    splitter_2 = new QSplitter(tab_2);
    splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
    splitter_2->setOrientation(Qt::Horizontal);
    appealActionButton = new QPushButton(splitter_2);
    appealActionButton->setObjectName(QString::fromUtf8("appealActionButton"));
    appealActionButton->setIcon(icon2);
    splitter_2->addWidget(appealActionButton);
    loadAppealExampleButton = new QPushButton(splitter_2);
    loadAppealExampleButton->setObjectName(
        QString::fromUtf8("loadAppealExampleButton"));
    splitter_2->addWidget(loadAppealExampleButton);

    verticalLayout_3->addWidget(splitter_2);

    tabWidget->addTab(tab_2, QString());

    verticalLayout->addWidget(tabWidget);

    output = new QTextBrowser(Wallet);
    output->setObjectName(QString::fromUtf8("output"));
    output->setFont(font);

    verticalLayout->addWidget(output);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

    verticalLayout->addLayout(horizontalLayout_2);

    lower = new QHBoxLayout();
    lower->setObjectName(QString::fromUtf8("lower"));
    horizontalSpacer =
        new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    lower->addItem(horizontalSpacer);

    label_7 = new QLabel(Wallet);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setAlignment(Qt::AlignRight | Qt::AlignTrailing |
                          Qt::AlignVCenter);

    lower->addWidget(label_7);

    verticalLayout->addLayout(lower);

    MainWindow->setCentralWidget(Wallet);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1000, 41));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);
    toolBar = new QToolBar(MainWindow);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionLoadWallet);
    menuHelp->addAction(actionQuit);
    toolBar->addAction(actionLoadWallet);
    toolBar->addAction(actionQuit);

    retranslateUi(MainWindow);

    tabWidget->setCurrentIndex(0);

    QMetaObject::connectSlotsByName(MainWindow);
  } // setupUi

  void retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(
        QApplication::translate("MainWindow", "MainWindow", nullptr));
    actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
    actionLoadWallet->setText(
        QApplication::translate("MainWindow", "Load", nullptr));
#ifndef QT_NO_TOOLTIP
    actionLoadWallet->setToolTip(
        QApplication::translate("MainWindow", "Load Wallet", nullptr));
#endif // QT_NO_TOOLTIP
    Wallet->setWindowTitle(
        QApplication::translate("MainWindow", "Form", nullptr));
    info->setTitle(QApplication::translate("MainWindow",
                                           "Load a wallet to start", nullptr));
    versionLabel->setText(
        QApplication::translate("MainWindow", "Version", nullptr));
    walletVersion->setText(
        QApplication::translate("MainWindow", "N/A", nullptr));
    label_13->setText(
        QApplication::translate("MainWindow", "Grace Period", nullptr));
    walletPeriod->setText(
        QApplication::translate("MainWindow", "N/A", nullptr));
    label_2->setText(QApplication::translate("MainWindow", "Address", nullptr));
    walletAddress->setText(
        QApplication::translate("MainWindow", "N/A", nullptr));
    label_6->setText(
        QApplication::translate("MainWindow", "Fee Address", nullptr));
    walletFeeAddress->setText(
        QApplication::translate("MainWindow", "N/A", nullptr));
    label_5->setText(
        QApplication::translate("MainWindow", "Current Users", nullptr));
    label_3->setText(
        QApplication::translate("MainWindow", "Who to be removed:", nullptr));
    label_4->setText(
        QApplication::translate("MainWindow", "Fee payment proof:", nullptr));
    label_8->setText(
        QApplication::translate("MainWindow", "Wallet Tx:", nullptr));
    removeActionButton->setText(
        QApplication::translate("MainWindow", "Action!", nullptr));
    loadRemovalExampleButton->setText(
        QApplication::translate("MainWindow", "Load an example", nullptr));
    tabWidget->setTabText(
        tabWidget->indexOf(Remove),
        QApplication::translate("MainWindow", "Remove a key holder", nullptr));
    label->setText(
        QApplication::translate("MainWindow", "Appeal on behalf of", nullptr));
    label_9->setText(QApplication::translate(
        "MainWindow", "Life signal to trigger", nullptr));
    appealActionButton->setText(
        QApplication::translate("MainWindow", "Action!", nullptr));
    loadAppealExampleButton->setText(
        QApplication::translate("MainWindow", "Load an example", nullptr));
    tabWidget->setTabText(
        tabWidget->indexOf(tab_2),
        QApplication::translate("MainWindow", "Spend a life signal", nullptr));
    output->setHtml(QApplication::translate(
        "MainWindow",
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" "
        "\"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style "
        "type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:'Monospace'; "
        "font-size:11pt; font-weight:400; font-style:normal;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; "
        "margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span "
        "style=\" font-family:'Lato';\">Output "
        "panel...</span></p></body></html>",
        nullptr));
    label_7->setText(QApplication::translate(
        "MainWindow", "\302\251 bl4ck5unxx@gmail.com", nullptr));
    menuFile->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    toolBar->setWindowTitle(
        QApplication::translate("MainWindow", "toolBar", nullptr));
  } // retranslateUi
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PP_H
