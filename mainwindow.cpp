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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lightsfront.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

const QHostAddress MULTICAST_ADDRESS("225.0.0.37");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QAction *portMemuAction;
    QAction *netMemuAction;

    UdpPort = 21928;
    ui->setupUi(this);

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {

        portMemuAction = ui->menu_Open_port->addAction(info.portName());
        portMemuAction->setObjectName(info.portName());
        connect(portMemuAction, SIGNAL(triggered()), this, SLOT(actionOpen_port_triggered()));
    }

    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        netMemuAction = ui->menuNework->addAction(interface.humanReadableName());
        netMemuAction->setObjectName(interface.name());
        connect(netMemuAction, SIGNAL(triggered()), this, SLOT(actionNetwork_triggered()));
    }

}

MainWindow::~MainWindow()
{
    serialPort.close();
    udpSocket.abort();
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::actionOpen_port_triggered()
{
    QObject *obj = sender();
    QString serialPortName = obj->objectName(); // Получаем по имени QAction имя порта

    if (serialPort.isOpen())
        serialPort.close();

    udpSocket.abort();

    /* Настройка и открытие порта */
    serialPort.setPortName(serialPortName);
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    if (!serialPort.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Oops"), tr("Could not open port ") + serialPortName);
        return;
    }
    connect(&serialPort, SIGNAL(readyRead()), this, SLOT(serialPort_received()));
    ui->statusBar->showMessage(serialPortName + tr(" activated"));
}

void MainWindow::on_actionAny_triggered()
{
    if (serialPort.isOpen())
        serialPort.close();

    udpSocket.abort();

    udpSocket.bind(QHostAddress::AnyIPv4, UdpPort, QUdpSocket::ShareAddress);
    udpSocket.setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
    udpSocket.setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    if (!udpSocket.joinMulticastGroup(MULTICAST_ADDRESS)) {
         QMessageBox::warning(this, tr("Oops"), tr("Could not join multicast group"));
         udpSocket.abort();
         return;
    }
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(udpSocket_received()), Qt::QueuedConnection);
    ui->statusBar->showMessage(tr("UDP port ") + QString::number(UdpPort) + tr(" activated"));
}

void MainWindow::actionNetwork_triggered()
{
    QObject *obj = sender();
    QString interfaceName = obj->objectName();
    QNetworkInterface iface = QNetworkInterface::interfaceFromName(interfaceName);
    QHostAddress groupAddress = QHostAddress("225.0.0.37");

    if (serialPort.isOpen())
        serialPort.close();

    udpSocket.abort();

    udpSocket.bind(QHostAddress::AnyIPv4, UdpPort, QUdpSocket::ReuseAddressHint|QUdpSocket::ShareAddress);

    if (!udpSocket.joinMulticastGroup(groupAddress)) {
        QMessageBox msgBox;

        msgBox.setText("Error");
        msgBox.exec();
        udpSocket.abort();
        return;
    }
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(udpSocket_received()), Qt::QueuedConnection);
    ui->statusBar->showMessage(tr("UDP port ") + QString::number(UdpPort) + tr(" activated"));
}

void MainWindow::serialPort_received()
{
    QByteArray ba = serialPort.readAll();
    operateData(ba);
}


void MainWindow::udpSocket_received()
{
    char buf[128];
    QByteArray ba;
    int len = udpSocket.readDatagram(buf, 128);

    ba = QByteArray::fromRawData(buf, len);
    operateData(ba);
}

void MainWindow::operateData(QByteArray ba)
{
    bool state = 0;
    int note;
    int n = 0; // Номер байта канального сообщения
    int len = ba.size();

    for (int i = 0; i < len; i++) {

        if ((ba[i] == (char)0x90) || (ba[i] == (char)0x80)) {
            /* Принят статус байт сообщения 1-го канала*/
            state = ba[i] & 0x10;
            if (n != 0) {
                /* Более одного сообщения в буффере */
            }
            n = 1;
        }
        else {
            /* Байт данных */
            if ( n == 1) {
                /* Номер ноты */
                note = ba[i];
                n = 2;
                ui->labelFront->setLight(noteToLightFront(note), state);
                ui->labelBack->setLight(noteToLightBack(note), state);
            }
        }
    }
}

int MainWindow::noteToLightFront(int note)
{
    int light;

    switch (note) {
    case 24:
        light = lightsFront::RIGHT_FOG;
        break;
    case 25:
        light = lightsFront::RIGHT_TURN;
        break;
    case 26:
        light = lightsFront::RIGHT_ANGEL;
        break;
    case 27:
        light = lightsFront::RIGHT_LOW_BEAM;
        break;
    case 28:
        light = lightsFront::RIGHT_HIGH_BEAM;
        break;
    case 29:
        light = lightsFront::LEFT_HIGH_BEAM;
        break;
    case 30:
        light = lightsFront::LEFT_LOW_BEAM;
        break;
    case 31:
        light = lightsFront::LEFT_ANGEL;
        break;
    case 32:
        light = lightsFront::LEFT_TURN;
        break;
    case 33:
        light = lightsFront::LEFT_FOG;
        break;
    default:
        light = -1;
        break;
    }
    return light;
}

int MainWindow::noteToLightBack(int note)
{
    int light;

    switch (note) {
    case 34:
        light = lightsBack::RIGHT_STOP;
        break;
    case 35:
        light = lightsBack::RIGHT_REVERCE;
        break;
    case 36:
        light = lightsBack::RIGHT_FOG;
        break;
    case 37:
        light = lightsBack::RIGHT_PARK_OUT;
        break;
    case 38:
        light = lightsBack::RIGHT_PARK_IN;
        break;
    case 39:
        light = lightsBack::RIGHT_TURN;
        break;
    case 40:
        light = lightsBack::RIGHT_REG_PLATE;
        break;
    case 41:
        light = lightsBack::CENTER_STOP;
        break;
    case 42:
        light = lightsBack::LEFT_REG_PLATE;
        break;
    case 43:
        light = lightsBack::LEFT_TURN;
        break;
    case 44:
        light = lightsBack::LEFT_PARK_IN;
        break;
    case 45:
        light = lightsBack::LEFT_PARK_OUT;
        break;
    case 46:
        light = lightsBack::LEFT_FOG;
        break;
    case 47:
        light = lightsBack::LEFT_REVERCE;
        break;
    case 48:
        light = lightsBack::LEFT_STOP;
        break;
    default:
        light = -1;
        break;
    }
    return light;
}

void MainWindow::on_actionAbout_triggered()
{
    dlgAbout = new About(this);

    dlgAbout->exec();
    delete dlgAbout;
}
