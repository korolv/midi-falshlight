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

#include "lightsfront.h"
#include <QPainter>

lightsFront::lightsFront(QWidget *parent) :
    QLabel(parent)

{
    /* Начальная инициализация световых приборов и фонового изображения авто */
    lights[BASE] = new QPixmap(":/images/front/BMW_FRONT.png"); isSwitchOn[BASE] = true;
    lights[LEFT_FOG] = new QPixmap(":/images/front/L_FOG.png"); isSwitchOn[LEFT_FOG] = false;
    lights[RIGHT_FOG] = new QPixmap(":/images/front/R_FOG.png"); isSwitchOn[RIGHT_FOG] = false;
    lights[LEFT_TURN] = new QPixmap(":/images/front/L_TURN.png"); isSwitchOn[LEFT_TURN] = false;
    lights[RIGHT_TURN] = new QPixmap(":/images/front/R_TURN.png"); isSwitchOn[RIGHT_TURN] = false;
    lights[LEFT_ANGEL] = new QPixmap(":/images/front/L_ANGEL.png"); isSwitchOn[LEFT_ANGEL] = false;
    lights[RIGHT_ANGEL] = new QPixmap(":/images/front/R_ANGEL.png"); isSwitchOn[RIGHT_ANGEL] = false;
    lights[LEFT_LOW_BEAM] = new QPixmap(":/images/front/L_L_BEAM.png"); isSwitchOn[LEFT_LOW_BEAM] = false;
    lights[RIGHT_LOW_BEAM] = new QPixmap(":/images/front/R_L_BEAM.png"); isSwitchOn[RIGHT_LOW_BEAM] = false;
    lights[LEFT_HIGH_BEAM] = new QPixmap(":/images/front/L_H_BEAM.png"); isSwitchOn[LEFT_HIGH_BEAM] = false;
    lights[RIGHT_HIGH_BEAM] = new QPixmap(":/images/front/R_H_BEAM.png"); isSwitchOn[RIGHT_HIGH_BEAM] = false;
    update();
}

lightsFront::~lightsFront()
{
    for (int i = 0; i < LIGHT_SIZE; i++) {
        free(lights[i]);
    }
}

void lightsFront::setLight(int num, bool state)
{
    if ((num > 0) && (num < LIGHT_SIZE)) {
        isSwitchOn[num] = state;
        update();
    }
}

void lightsFront::paintEvent(QPaintEvent *const event)
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
