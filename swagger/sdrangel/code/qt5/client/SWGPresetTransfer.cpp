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


#include "SWGPresetTransfer.h"

#include "SWGHelpers.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

namespace SWGSDRangel {

SWGPresetTransfer::SWGPresetTransfer(QString* json) {
    init();
    this->fromJson(*json);
}

SWGPresetTransfer::SWGPresetTransfer() {
    init();
}

SWGPresetTransfer::~SWGPresetTransfer() {
    this->cleanup();
}

void
SWGPresetTransfer::init() {
    device_set_index = 0;
    preset = new SWGPresetIdentifier();
}

void
SWGPresetTransfer::cleanup() {
    

    if(preset != nullptr) {
        delete preset;
    }
}

SWGPresetTransfer*
SWGPresetTransfer::fromJson(QString &json) {
    QByteArray array (json.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
    return this;
}

void
SWGPresetTransfer::fromJsonObject(QJsonObject &pJson) {
    ::SWGSDRangel::setValue(&device_set_index, pJson["deviceSetIndex"], "qint32", "");
    ::SWGSDRangel::setValue(&preset, pJson["preset"], "SWGPresetIdentifier", "SWGPresetIdentifier");
}

QString
SWGPresetTransfer::asJson ()
{
    QJsonObject* obj = this->asJsonObject();
    
    QJsonDocument doc(*obj);
    QByteArray bytes = doc.toJson();
    return QString(bytes);
}

QJsonObject*
SWGPresetTransfer::asJsonObject() {
    QJsonObject* obj = new QJsonObject();
    
    obj->insert("deviceSetIndex", QJsonValue(device_set_index));

    toJsonValue(QString("preset"), preset, obj, QString("SWGPresetIdentifier"));

    return obj;
}

qint32
SWGPresetTransfer::getDeviceSetIndex() {
    return device_set_index;
}
void
SWGPresetTransfer::setDeviceSetIndex(qint32 device_set_index) {
    this->device_set_index = device_set_index;
}

SWGPresetIdentifier*
SWGPresetTransfer::getPreset() {
    return preset;
}
void
SWGPresetTransfer::setPreset(SWGPresetIdentifier* preset) {
    this->preset = preset;
}


}

