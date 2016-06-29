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

#ifndef LIGHTS_FRONT_H
#define LIGHTS_FRONT_H

#include <QLabel>
#include <QPixmap>

QT_FORWARD_DECLARE_CLASS(QPaintEvent)

class lightsFront : public QLabel
{
    Q_OBJECT

public:
    explicit lightsFront(QWidget *parent = 0);
    ~lightsFront();
    void setLight(int, bool);
    enum light {
        BASE,
        LEFT_FOG,
        RIGHT_FOG,
        LEFT_TURN,
        RIGHT_TURN,
        LEFT_ANGEL,
        RIGHT_ANGEL,
        LEFT_LOW_BEAM,
        RIGHT_LOW_BEAM,
        LEFT_HIGH_BEAM,
        RIGHT_HIGH_BEAM,
        LIGHT_SIZE
    };

public slots:
//    void setScaledPixmap(const QPixmap &pixmap);
//    void loadPixmapData(const QString &path);

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap *lights[LIGHT_SIZE];
    bool isSwitchOn[LIGHT_SIZE];
};

#endif // LIGHTS_FRONT_H
