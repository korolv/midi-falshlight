#ifndef UDPMIDICLIENT_H
#define UDPMIDICLIENT_H


class UdpMidiClient : public QObject
{
    Q_OBJECT
public:
    explicit UdpMidiClient(QObject *parent = 0);

signals:

public slots:
};

#endif // UDPMIDICLIENT_H