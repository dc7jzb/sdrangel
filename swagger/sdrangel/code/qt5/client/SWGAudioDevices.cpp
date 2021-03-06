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


#include "SWGAudioDevices.h"

#include "SWGHelpers.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

namespace SWGSDRangel {

SWGAudioDevices::SWGAudioDevices(QString* json) {
    init();
    this->fromJson(*json);
}

SWGAudioDevices::SWGAudioDevices() {
    init();
}

SWGAudioDevices::~SWGAudioDevices() {
    this->cleanup();
}

void
SWGAudioDevices::init() {
    input_volume = 0.0f;
    nb_input_devices = 0;
    input_device_selected_index = 0;
    input_devices = new QList<SWGAudioDevice*>();
    nb_output_devices = 0;
    output_device_selected_index = 0;
    output_devices = new QList<SWGAudioDevice*>();
}

void
SWGAudioDevices::cleanup() {
    



    if(input_devices != nullptr) {
        QList<SWGAudioDevice*>* arr = input_devices;
        foreach(SWGAudioDevice* o, *arr) {
            delete o;
        }
        delete input_devices;
    }



    if(output_devices != nullptr) {
        QList<SWGAudioDevice*>* arr = output_devices;
        foreach(SWGAudioDevice* o, *arr) {
            delete o;
        }
        delete output_devices;
    }
}

SWGAudioDevices*
SWGAudioDevices::fromJson(QString &json) {
    QByteArray array (json.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
    return this;
}

void
SWGAudioDevices::fromJsonObject(QJsonObject &pJson) {
    ::SWGSDRangel::setValue(&input_volume, pJson["inputVolume"], "float", "");
    ::SWGSDRangel::setValue(&nb_input_devices, pJson["nbInputDevices"], "qint32", "");
    ::SWGSDRangel::setValue(&input_device_selected_index, pJson["inputDeviceSelectedIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&input_devices, pJson["inputDevices"], "QList", "SWGAudioDevice");
    
    ::SWGSDRangel::setValue(&nb_output_devices, pJson["nbOutputDevices"], "qint32", "");
    ::SWGSDRangel::setValue(&output_device_selected_index, pJson["outputDeviceSelectedIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&output_devices, pJson["outputDevices"], "QList", "SWGAudioDevice");
    
}

QString
SWGAudioDevices::asJson ()
{
    QJsonObject* obj = this->asJsonObject();
    
    QJsonDocument doc(*obj);
    QByteArray bytes = doc.toJson();
    return QString(bytes);
}

QJsonObject*
SWGAudioDevices::asJsonObject() {
    QJsonObject* obj = new QJsonObject();
    
    obj->insert("inputVolume", QJsonValue(input_volume));

    obj->insert("nbInputDevices", QJsonValue(nb_input_devices));

    obj->insert("inputDeviceSelectedIndex", QJsonValue(input_device_selected_index));

    QJsonArray input_devicesJsonArray;
    toJsonArray((QList<void*>*)input_devices, &input_devicesJsonArray, "input_devices", "SWGAudioDevice");
    obj->insert("inputDevices", input_devicesJsonArray);

    obj->insert("nbOutputDevices", QJsonValue(nb_output_devices));

    obj->insert("outputDeviceSelectedIndex", QJsonValue(output_device_selected_index));

    QJsonArray output_devicesJsonArray;
    toJsonArray((QList<void*>*)output_devices, &output_devicesJsonArray, "output_devices", "SWGAudioDevice");
    obj->insert("outputDevices", output_devicesJsonArray);

    return obj;
}

float
SWGAudioDevices::getInputVolume() {
    return input_volume;
}
void
SWGAudioDevices::setInputVolume(float input_volume) {
    this->input_volume = input_volume;
}

qint32
SWGAudioDevices::getNbInputDevices() {
    return nb_input_devices;
}
void
SWGAudioDevices::setNbInputDevices(qint32 nb_input_devices) {
    this->nb_input_devices = nb_input_devices;
}

qint32
SWGAudioDevices::getInputDeviceSelectedIndex() {
    return input_device_selected_index;
}
void
SWGAudioDevices::setInputDeviceSelectedIndex(qint32 input_device_selected_index) {
    this->input_device_selected_index = input_device_selected_index;
}

QList<SWGAudioDevice*>*
SWGAudioDevices::getInputDevices() {
    return input_devices;
}
void
SWGAudioDevices::setInputDevices(QList<SWGAudioDevice*>* input_devices) {
    this->input_devices = input_devices;
}

qint32
SWGAudioDevices::getNbOutputDevices() {
    return nb_output_devices;
}
void
SWGAudioDevices::setNbOutputDevices(qint32 nb_output_devices) {
    this->nb_output_devices = nb_output_devices;
}

qint32
SWGAudioDevices::getOutputDeviceSelectedIndex() {
    return output_device_selected_index;
}
void
SWGAudioDevices::setOutputDeviceSelectedIndex(qint32 output_device_selected_index) {
    this->output_device_selected_index = output_device_selected_index;
}

QList<SWGAudioDevice*>*
SWGAudioDevices::getOutputDevices() {
    return output_devices;
}
void
SWGAudioDevices::setOutputDevices(QList<SWGAudioDevice*>* output_devices) {
    this->output_devices = output_devices;
}


}

