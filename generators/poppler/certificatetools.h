/***************************************************************************
 *   Copyright (C) 2019 by Bubli <Katarina.Behrens@cib.de>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _CERTIFICATETOOLS_H_
#define _CERTIFICATETOOLS_H_

#include <QWidget>

#include "ui_certsettingswidget.h"

class QTreeWidget;

class CertificateTools : public QWidget
{
    Q_OBJECT

public:
    explicit CertificateTools(QWidget *parent = nullptr);
    bool event(QEvent *e) override;

private:
    void warnRestartNeeded();

    QTreeWidget *m_tree;
    bool m_certificatesAsked = false;
    bool m_warnedAboutRestart = false;
    Ui_DlgSignaturesBase m_certsw;
};

#endif
