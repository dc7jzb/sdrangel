/**
 * SDRangel
 * This is the web API of SDRangel SDR software. SDRangel is an Open Source Qt5/OpenGL 3.0+ GUI and server Software Defined Radio and signal analyzer in software. It supports Airspy, BladeRF, HackRF, LimeSDR, PlutoSDR, RTL-SDR, SDRplay RSP1 and FunCube
 *
 * OpenAPI spec version: 4.0.0
 * Contact: f4exb06@gmail.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * SWGCWKeyerSettings.h
 * 
 * 
 */

#ifndef SWGCWKeyerSettings_H_
#define SWGCWKeyerSettings_H_

#include <QJsonObject>


#include <QString>

#include "SWGObject.h"


namespace SWGSDRangel {

class SWGCWKeyerSettings: public SWGObject {
public:
    SWGCWKeyerSettings();
    SWGCWKeyerSettings(QString* json);
    virtual ~SWGCWKeyerSettings();
    void init();
    void cleanup();

    QString asJson ();
    QJsonObject* asJsonObject();
    void fromJsonObject(QJsonObject &json);
    SWGCWKeyerSettings* fromJson(QString &jsonString);

    qint32 getSampleRate();
    void setSampleRate(qint32 sample_rate);

    qint32 getWpm();
    void setWpm(qint32 wpm);

    qint32 getMode();
    void setMode(qint32 mode);

    QString* getText();
    void setText(QString* text);

    qint32 getLoop();
    void setLoop(qint32 loop);


private:
    qint32 sample_rate;
    qint32 wpm;
    qint32 mode;
    QString* text;
    qint32 loop;
};

}

#endif /* SWGCWKeyerSettings_H_ */
