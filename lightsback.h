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

#ifndef LIGHTSBACK_H
#define LIGHTSBACK_H

#include <QLabel>
#include <QPixmap>

QT_FORWARD_DECLARE_CLASS(QPaintEvent)

class lightsBack : public QLabel
{
    Q_OBJECT

public:
    explicit lightsBack(QWidget *parent = 0);
    ~lightsBack();
    void setLight(int, bool);
    enum light {
        BASE,
        LEFT_FOG,
        RIGHT_FOG,
        LEFT_TURN,
        RIGHT_TURN,
        LEFT_REVERCE,
        RIGHT_REVERCE,
        LEFT_PARK_IN,
        RIGHT_PARK_IN,
        LEFT_PARK_OUT,
        RIGHT_PARK_OUT,
        LEFT_PARK,
        RIGHT_PARK,
        LEFT_STOP,
        RIGHT_STOP,
        CENTER_STOP,
        LEFT_REG_PLATE,
        RIGHT_REG_PLATE,
        LIGHT_SIZE
    };

public slots:

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap *lights[LIGHT_SIZE];
    bool isSwitchOn[LIGHT_SIZE];
};

#endif // LIGHTSBACK_H
