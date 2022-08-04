/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "digitalclock.h"

#include <QTime>
#include <QTimer>


DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint |Qt::Tool | Qt::X11BypassWindowManagerHint);//无边框/置顶/无任务栏
    setAttribute(Qt::WA_TranslucentBackground);//背景透明

    setSegmentStyle(Filled);//有三种风格
    setStyleSheet("background:transparent;color:#00ccff;"); //背景透明 设置字体色
    setDigitCount(8); //设置位数
    setMode(QLCDNumber::Dec); //十进制显示
    resize(300,120);//设置大小  字体大小会按自动调整
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);
    showTime();

    //    setWindowTitle(tr("Digital Clock"));


}

//#include <QDebug>
void DigitalClock::showTime()

{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    //    qDebug()<<text;
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    display(text);
}
void DigitalClock::mousePressEvent(QMouseEvent *e)
{
    //鼠标左键
    this->setFocus();
    if(Qt::LeftButton == e->button() && 0 == (Qt::WindowMaximized & this->windowState()))
    {
        QPoint temp=e->globalPos();
        pLast=temp;    //记录鼠标按下的位置
        e->ignore();
    }
    m_bPressed = true; //标记鼠标为按下状态
    if(Qt::RightButton == e->button() )
    {
        int ret = QMessageBox::question(this,  "退出",  "请问你是否要退出程序？",
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
      if(ret == QMessageBox::Yes)
       {
//          this->close();
          QApplication::exit(0);
       }
      else {

      }
    }

}

void DigitalClock::mouseMoveEvent(QMouseEvent *e)
{
    if(this->isMaximized()) //如果当前是最大化，则不允许移动
        return;

    if((e->buttons() & Qt::LeftButton) && m_bPressed)//是否左击
    {
        QPoint ptemp=e->globalPos();              //当前鼠标全局位置
/*        ptemp=ptemp-pLast;                        //计算移动变量
        ptemp=ptemp+pos(); */                       //窗口原始位置（pos()） + 鼠标移动变量（ptemp） = 最终窗口位置
        move(ptemp);                              //移动窗口到新的位置
    }

}

void DigitalClock::mouseReleaseEvent(QMouseEvent *e)
{
    QApplication::restoreOverrideCursor();//恢复鼠标指针性状
    e->ignore();
    m_bPressed = false;
}

