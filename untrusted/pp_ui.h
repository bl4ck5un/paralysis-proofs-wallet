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
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wallet
{
public:
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *left;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QPlainTextEdit *redeemScript;
    QLabel *label_2;
    QPlainTextEdit *utxo;
    QFrame *line;
    QPushButton *loadButton;
    QTextBrowser *walletinfo;
    QGroupBox *right;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLineEdit *accused;
    QLabel *label_4;
    QPlainTextEdit *feeTx;
    QFrame *line_2;
    QPushButton *accuseButton;
    QTextBrowser *Tx1;
    QTextBrowser *Tx2;
    QTextBrowser *TxAppeal;
    QSplitter *splitter;
    QPushButton *copyTx1Button;
    QPushButton *copyTx2Button;
    QPushButton *copyTxAppealButton;
    QHBoxLayout *lower;
    QPushButton *loadExampleButton;
    QPushButton *exitButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;

    void setupUi(QWidget *Wallet)
    {
        if (Wallet->objectName().isEmpty())
            Wallet->setObjectName(QString::fromUtf8("Wallet"));
        Wallet->resize(1742, 1604);
        verticalLayout_3 = new QVBoxLayout(Wallet);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_6 = new QLabel(Wallet);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_6);

        label_5 = new QLabel(Wallet);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        left = new QGroupBox(Wallet);
        left->setObjectName(QString::fromUtf8("left"));
        verticalLayout = new QVBoxLayout(left);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(left);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        redeemScript = new QPlainTextEdit(left);
        redeemScript->setObjectName(QString::fromUtf8("redeemScript"));
        redeemScript->setMinimumSize(QSize(600, 300));

        formLayout->setWidget(0, QFormLayout::FieldRole, redeemScript);

        label_2 = new QLabel(left);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        utxo = new QPlainTextEdit(left);
        utxo->setObjectName(QString::fromUtf8("utxo"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(utxo->sizePolicy().hasHeightForWidth());
        utxo->setSizePolicy(sizePolicy);
        utxo->setMinimumSize(QSize(600, 300));

        formLayout->setWidget(1, QFormLayout::FieldRole, utxo);


        verticalLayout->addLayout(formLayout);

        line = new QFrame(left);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        loadButton = new QPushButton(left);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        verticalLayout->addWidget(loadButton);

        walletinfo = new QTextBrowser(left);
        walletinfo->setObjectName(QString::fromUtf8("walletinfo"));

        verticalLayout->addWidget(walletinfo);


        horizontalLayout_2->addWidget(left);

        right = new QGroupBox(Wallet);
        right->setObjectName(QString::fromUtf8("right"));
        verticalLayout_2 = new QVBoxLayout(right);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_3 = new QLabel(right);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        accused = new QLineEdit(right);
        accused->setObjectName(QString::fromUtf8("accused"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, accused);

        label_4 = new QLabel(right);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        feeTx = new QPlainTextEdit(right);
        feeTx->setObjectName(QString::fromUtf8("feeTx"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(feeTx->sizePolicy().hasHeightForWidth());
        feeTx->setSizePolicy(sizePolicy1);
        feeTx->setMinimumSize(QSize(600, 0));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, feeTx);


        verticalLayout_2->addLayout(formLayout_2);

        line_2 = new QFrame(right);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        accuseButton = new QPushButton(right);
        accuseButton->setObjectName(QString::fromUtf8("accuseButton"));

        verticalLayout_2->addWidget(accuseButton);

        Tx1 = new QTextBrowser(right);
        Tx1->setObjectName(QString::fromUtf8("Tx1"));
        Tx1->setMinimumSize(QSize(0, 300));

        verticalLayout_2->addWidget(Tx1);

        Tx2 = new QTextBrowser(right);
        Tx2->setObjectName(QString::fromUtf8("Tx2"));
        Tx2->setMinimumSize(QSize(0, 300));

        verticalLayout_2->addWidget(Tx2);

        TxAppeal = new QTextBrowser(right);
        TxAppeal->setObjectName(QString::fromUtf8("TxAppeal"));
        TxAppeal->setMinimumSize(QSize(0, 300));

        verticalLayout_2->addWidget(TxAppeal);

        splitter = new QSplitter(right);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        copyTx1Button = new QPushButton(splitter);
        copyTx1Button->setObjectName(QString::fromUtf8("copyTx1Button"));
        splitter->addWidget(copyTx1Button);
        copyTx2Button = new QPushButton(splitter);
        copyTx2Button->setObjectName(QString::fromUtf8("copyTx2Button"));
        splitter->addWidget(copyTx2Button);
        copyTxAppealButton = new QPushButton(splitter);
        copyTxAppealButton->setObjectName(QString::fromUtf8("copyTxAppealButton"));
        splitter->addWidget(copyTxAppealButton);

        verticalLayout_2->addWidget(splitter);


        horizontalLayout_2->addWidget(right);


        verticalLayout_3->addLayout(horizontalLayout_2);

        lower = new QHBoxLayout();
        lower->setObjectName(QString::fromUtf8("lower"));
        loadExampleButton = new QPushButton(Wallet);
        loadExampleButton->setObjectName(QString::fromUtf8("loadExampleButton"));

        lower->addWidget(loadExampleButton);

        exitButton = new QPushButton(Wallet);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        lower->addWidget(exitButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        lower->addItem(horizontalSpacer);

        label_7 = new QLabel(Wallet);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        lower->addWidget(label_7);


        verticalLayout_3->addLayout(lower);


        retranslateUi(Wallet);

        QMetaObject::connectSlotsByName(Wallet);
    } // setupUi

    void retranslateUi(QWidget *Wallet)
    {
        Wallet->setWindowTitle(QApplication::translate("Wallet", "Form", nullptr));
        label_6->setText(QApplication::translate("Wallet", "v0.0.1", nullptr));
        label_5->setText(QApplication::translate("Wallet", "(This is a demo. Don't use it with real coins!!)", nullptr));
        left->setTitle(QApplication::translate("Wallet", "Wallet Information", nullptr));
        label->setText(QApplication::translate("Wallet", "RedeemScript", nullptr));
        redeemScript->setPlaceholderText(QApplication::translate("Wallet", "hex string for the wallet redeemScript", nullptr));
        label_2->setText(QApplication::translate("Wallet", "Wallet UTXO", nullptr));
        utxo->setPlaceholderText(QApplication::translate("Wallet", "hex string for the wallet deposit TX", nullptr));
        loadButton->setText(QApplication::translate("Wallet", "Load Wallet Information", nullptr));
        walletinfo->setPlaceholderText(QApplication::translate("Wallet", "Wallet info will appear here...", nullptr));
        right->setTitle(QApplication::translate("Wallet", "Change Access Control", nullptr));
        label_3->setText(QApplication::translate("Wallet", "accuse who:", nullptr));
        accused->setPlaceholderText(QApplication::translate("Wallet", "e.g., 0, 1, 2, ...", nullptr));
        label_4->setText(QApplication::translate("Wallet", "Fee Payment Tx", nullptr));
        feeTx->setPlaceholderText(QApplication::translate("Wallet", "hex string for the fee payment TX", nullptr));
        accuseButton->setText(QApplication::translate("Wallet", "Accues!", nullptr));
        Tx1->setPlaceholderText(QApplication::translate("Wallet", "TX1 will appear here...", nullptr));
        Tx2->setPlaceholderText(QApplication::translate("Wallet", "TX2 will appear here...", nullptr));
        TxAppeal->setPlaceholderText(QApplication::translate("Wallet", "TX_appeal will appear here", nullptr));
        copyTx1Button->setText(QApplication::translate("Wallet", "Copy Tx1", nullptr));
        copyTx2Button->setText(QApplication::translate("Wallet", "Copy Tx2", nullptr));
        copyTxAppealButton->setText(QApplication::translate("Wallet", "Copy Tx Appeal", nullptr));
        loadExampleButton->setText(QApplication::translate("Wallet", "Load Example", nullptr));
        exitButton->setText(QApplication::translate("Wallet", "Quit", nullptr));
        label_7->setText(QApplication::translate("Wallet", "\302\251 bl4ck5unxx@gmail.com", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Wallet: public Ui_Wallet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PP_H
