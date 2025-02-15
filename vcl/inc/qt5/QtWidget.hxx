/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#pragma once

#include <QtWidgets/QWidget>
#include <rtl/ustring.hxx>

#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/accessibility/XAccessibleEditableText.hpp>

class QInputEvent;
class QtFrame;
class QtObject;
struct SalAbstractMouseEvent;

class QtWidget : public QWidget
{
    Q_OBJECT

    QtFrame& m_rFrame;
    bool m_bNonEmptyIMPreeditSeen;
    int m_nDeltaX;
    int m_nDeltaY;

    enum class ButtonKeyState
    {
        Pressed,
        Released
    };

    static void commitText(QtFrame&, const QString& aText);
    static bool handleKeyEvent(QtFrame&, const QWidget&, QKeyEvent*, const ButtonKeyState);
    static void handleMouseButtonEvent(const QtFrame&, const QMouseEvent*, const ButtonKeyState);
    static void fillSalAbstractMouseEvent(const QtFrame& rFrame, const QInputEvent* pQEvent,
                                          const QPoint& rPos, Qt::MouseButtons eButtons, int nWidth,
                                          SalAbstractMouseEvent& aSalEvent);

    virtual bool event(QEvent*) override;

    virtual void focusInEvent(QFocusEvent*) override;
    virtual void focusOutEvent(QFocusEvent*) override;
    // keyPressEvent(QKeyEvent*) is handled via event(QEvent*); see comment
    virtual void keyReleaseEvent(QKeyEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void dragEnterEvent(QDragEnterEvent*) override;
    virtual void dragLeaveEvent(QDragLeaveEvent*) override;
    virtual void dragMoveEvent(QDragMoveEvent*) override;
    virtual void dropEvent(QDropEvent*) override;
    virtual void moveEvent(QMoveEvent*) override;
    virtual void paintEvent(QPaintEvent*) override;
    virtual void resizeEvent(QResizeEvent*) override;
    virtual void showEvent(QShowEvent*) override;
    virtual void wheelEvent(QWheelEvent*) override;
    virtual void closeEvent(QCloseEvent*) override;
    virtual void changeEvent(QEvent*) override;

    void inputMethodEvent(QInputMethodEvent*) override;
    QVariant inputMethodQuery(Qt::InputMethodQuery) const override;
    static void closePopup();

public:
    QtWidget(QtFrame& rFrame, Qt::WindowFlags f = Qt::WindowFlags());

    QtFrame& frame() const { return m_rFrame; }
    void endExtTextInput();

    static bool handleEvent(QtFrame&, const QWidget&, QEvent*);
    // key events might be propagated further down => call base on false
    static inline bool handleKeyReleaseEvent(QtFrame&, const QWidget&, QKeyEvent*);
    // mouse events are always accepted
    static inline void handleMousePressEvent(const QtFrame&, const QMouseEvent*);
    static inline void handleMouseReleaseEvent(const QtFrame&, const QMouseEvent*);
};

bool QtWidget::handleKeyReleaseEvent(QtFrame& rFrame, const QWidget& rWidget, QKeyEvent* pEvent)
{
    return handleKeyEvent(rFrame, rWidget, pEvent, ButtonKeyState::Released);
}

void QtWidget::handleMousePressEvent(const QtFrame& rFrame, const QMouseEvent* pEvent)
{
    handleMouseButtonEvent(rFrame, pEvent, ButtonKeyState::Pressed);
}

void QtWidget::handleMouseReleaseEvent(const QtFrame& rFrame, const QMouseEvent* pEvent)
{
    handleMouseButtonEvent(rFrame, pEvent, ButtonKeyState::Released);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
