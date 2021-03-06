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
 * SWGDeviceState.h
 * 
 * Device running state
 */

#ifndef SWGDeviceState_H_
#define SWGDeviceState_H_

#include <QJsonObject>


#include <QString>

#include "SWGObject.h"


namespace SWGSDRangel {

class SWGDeviceState: public SWGObject {
public:
    SWGDeviceState();
    SWGDeviceState(QString* json);
    virtual ~SWGDeviceState();
    void init();
    void cleanup();

    QString asJson ();
    QJsonObject* asJsonObject();
    void fromJsonObject(QJsonObject &json);
    SWGDeviceState* fromJson(QString &jsonString);

    QString* getState();
    void setState(QString* state);


private:
    QString* state;
};

}

#endif /* SWGDeviceState_H_ */
