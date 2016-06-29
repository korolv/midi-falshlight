/*
 * Copyright 2016 Vladimir Korol <vovabox@mail.ru>
 *
 * MIDI Flashlight is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MIDI Flashlight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MIDI Flashlight. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QNetworkInterface>
#include <QUdpSocket>
#include "about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void actionOpen_port_triggered();
    void serialPort_received();
    void udpSocket_received();
    void operateData(QByteArray);
    void on_actionAny_triggered();
    void actionNetwork_triggered();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    About *dlgAbout;
    QSerialPort serialPort;
    QUdpSocket udpSocket;
    int UdpPort;
    int noteToLightFront(int);
    int noteToLightBack(int);
};

#endif // MAINWINDOW_H
