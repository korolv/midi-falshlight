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

#include "lightsback.h"
#include <QPainter>

lightsBack::lightsBack(QWidget *parent) :
    QLabel(parent)

{
    /* Начальная инициализация задних световых приборов и фонового изображения авто */
    lights[BASE] = new QPixmap(":/images/back/BMW_BACK.png"); isSwitchOn[BASE] = true;
    lights[LEFT_FOG] = new QPixmap(":/images/back/L_FOG.png"); isSwitchOn[LEFT_FOG] = false;
    lights[RIGHT_FOG] = new QPixmap(":/images/back/R_FOG.png"); isSwitchOn[RIGHT_FOG] = false;
    lights[LEFT_TURN] = new QPixmap(":/images/back/L_TURN.png"); isSwitchOn[LEFT_TURN] = false;
    lights[RIGHT_TURN] = new QPixmap(":/images/back/R_TURN.png"); isSwitchOn[RIGHT_TURN] = false;
    lights[LEFT_REVERCE] = new QPixmap(":/images/back/L_REVERCE.png"); isSwitchOn[LEFT_REVERCE] = false;
    lights[RIGHT_REVERCE] = new QPixmap(":/images/back/R_REVERCE.png"); isSwitchOn[RIGHT_REVERCE] = false;
    lights[LEFT_PARK_IN] = new QPixmap(":/images/back/L_PARK_IN.png"); isSwitchOn[LEFT_PARK_IN] = false;
    lights[RIGHT_PARK_IN] = new QPixmap(":/images/back/R_PARK_IN.png"); isSwitchOn[RIGHT_PARK_IN] = false;
    lights[LEFT_PARK_OUT] = new QPixmap(":/images/back/L_PARK_OUT.png"); isSwitchOn[LEFT_PARK_OUT] = false;
    lights[RIGHT_PARK_OUT] = new QPixmap(":/images/back/R_PARK_OUT.png"); isSwitchOn[RIGHT_PARK_OUT] = false;
    lights[LEFT_PARK] = new QPixmap(":/images/back/L_PARK.png"); isSwitchOn[LEFT_PARK] = false;
    lights[RIGHT_PARK] = new QPixmap(":/images/back/R_PARK.png"); isSwitchOn[RIGHT_PARK] = false;
    lights[LEFT_STOP] = new QPixmap(":/images/back/L_STOP.png"); isSwitchOn[LEFT_STOP] = false;
    lights[RIGHT_STOP] = new QPixmap(":/images/back/R_STOP.png"); isSwitchOn[RIGHT_STOP] = false;
    lights[CENTER_STOP] = new QPixmap(":/images/back/C_STOP.png"); isSwitchOn[CENTER_STOP] = false;
    update();
}

lightsBack::~lightsBack()
{
    for (int i = 0; i < LIGHT_SIZE; i++) {
        free(lights[i]);
    }
}

void lightsBack::setLight(int num, bool state)
{
    if ((num > 0) && (num < LIGHT_SIZE)) {
        isSwitchOn[num] = state;
        update();
    }
}

void lightsBack::paintEvent(QPaintEvent *const event)
{
    QPainter painter(this);
    for (int i = 0; i < LIGHT_SIZE; i++) {
        QPoint centerPoint(0, 0);
        QSize baseSize = size();
        if (!lights[i]->isNull() && isSwitchOn[i]) {
            QPixmap scaledPixmap = lights[i]->scaled(baseSize, Qt::KeepAspectRatio);
            centerPoint.setX((baseSize.width() - scaledPixmap.width())/2);
            centerPoint.setY((baseSize.height() - scaledPixmap.height())/2);
            painter.drawPixmap(centerPoint, scaledPixmap);
        }
    }
    QLabel::paintEvent(event);
}
