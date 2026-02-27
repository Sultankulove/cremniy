#ifndef CODEEDITORTAB_H
#define CODEEDITORTAB_H

#include "QCodeEditor.hpp"
#include "tooltab.h"
#include <QWidget>
#include <qfileinfo.h>
#include <qlabel.h>
#include "utils.h"

class CodeEditorTab : public QWidget, public ToolTab
{
    Q_OBJECT

private:
    QCodeEditor* m_codeEditorWidget;
    QWidget* m_overlayWidget;
    bool forceSetData = false;

public:
    explicit CodeEditorTab(QWidget *parent, QString path);

    void saveToFile(QString path) override {
        QFile f(path);
        if (!f.open(QFile::WriteOnly)) return;
        f.write(m_codeEditorWidget->getBData());
        f.close();
        m_codeEditorWidget->document()->setModified(false);
    };

    void setTabData(QByteArray &data) override {

        if (isBinary(data) && !forceSetData){
            m_codeEditorWidget->hide();
            m_overlayWidget->show();
        }
        else{
            m_codeEditorWidget->show();
            m_overlayWidget->hide();
            m_codeEditorWidget->setBData(data);
            forceSetData = false;
        }
    };

signals:
    void modifyData(bool modified);
    void askData();
    void setHexViewTab();
};

#endif // CODEEDITORTAB_H
