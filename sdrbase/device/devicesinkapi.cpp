///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#include "device/devicesinkapi.h"
#include "plugin/plugingui.h"
#include "plugin/pluginapi.h"
#include "plugin/plugininterface.h"
#include "gui/glspectrum.h"
#include "gui/channelwindow.h"
#include "mainwindow.h"
#include "settings/preset.h"

DeviceSinkAPI::DeviceSinkAPI(MainWindow *mainWindow,
        int deviceTabIndex,
        DSPDeviceSinkEngine *deviceSinkEngine,
        GLSpectrum *glSpectrum,
        ChannelWindow *channelWindow) :
    m_mainWindow(mainWindow),
    m_deviceTabIndex(deviceTabIndex),
    m_deviceSinkEngine(deviceSinkEngine),
    m_spectrum(glSpectrum),
    m_channelWindow(channelWindow),
    m_sampleSinkSequence(0),
    m_sampleSinkPluginGUI(0)
{
}

DeviceSinkAPI::~DeviceSinkAPI()
{
}

void DeviceSinkAPI::addSink(BasebandSampleSink *sink)
{
    m_deviceSinkEngine->addSink(sink);
}

void DeviceSinkAPI::removeSink(BasebandSampleSink* sink)
{
    m_deviceSinkEngine->removeSink(sink);
}

void DeviceSinkAPI::addSource(BasebandSampleSource *source)
{
    m_deviceSinkEngine->addSource(source);
}

void DeviceSinkAPI::removeSource(BasebandSampleSource* source)
{
    m_deviceSinkEngine->removeSource(source);
}

void DeviceSinkAPI::addThreadedSource(ThreadedBasebandSampleSource* source)
{
    m_deviceSinkEngine->addThreadedSource(source);
}

void DeviceSinkAPI::removeThreadedSource(ThreadedBasebandSampleSource* source)
{
    m_deviceSinkEngine->removeThreadedSource(source);
}

void DeviceSinkAPI::setSink(DeviceSampleSink* sink)
{
    m_deviceSinkEngine->setSink(sink);
}

bool DeviceSinkAPI::initGeneration()
{
    return m_deviceSinkEngine->initGeneration();
}

bool DeviceSinkAPI::startGeneration()
{
    return m_deviceSinkEngine->startGeneration();
}

void DeviceSinkAPI::stopGeneration()
{
    m_deviceSinkEngine->stopGeneration();
}
DSPDeviceSinkEngine::State DeviceSinkAPI::state() const
{
    return m_deviceSinkEngine->state();
}

QString DeviceSinkAPI::errorMessage()
{
    return m_deviceSinkEngine->errorMessage();
}

uint DeviceSinkAPI::getDeviceUID() const
{
    return m_deviceSinkEngine->getUID();
}

MessageQueue *DeviceSinkAPI::getDeviceInputMessageQueue()
{
    return m_deviceSinkEngine->getInputMessageQueue();
}

MessageQueue *DeviceSinkAPI::getDeviceOutputMessageQueue()
{
    return m_deviceSinkEngine->getOutputMessageQueue();
}

GLSpectrum *DeviceSinkAPI::getSpectrum()
{
    return m_spectrum;
}

void DeviceSinkAPI::addChannelMarker(ChannelMarker* channelMarker)
{
    m_spectrum->addChannelMarker(channelMarker);
}

ChannelWindow *DeviceSinkAPI::getChannelWindow()
{
    return m_channelWindow;
}

void DeviceSinkAPI::addRollupWidget(QWidget *widget)
{
    m_channelWindow->addRollupWidget(widget);
}

void DeviceSinkAPI::setOutputGUI(QWidget* outputGUI, const QString& sinkDisplayName)
{
    m_mainWindow->setDeviceGUI(m_deviceTabIndex, outputGUI, sinkDisplayName, false);
}

void DeviceSinkAPI::setSampleSinkId(const QString& id)
{
    m_sampleSinkId = id;
}

void DeviceSinkAPI::setSampleSinkSerial(const QString& serial)
{
    m_sampleSinkSerial = serial;
}

void DeviceSinkAPI::setSampleSinkSequence(int sequence)
{
    m_sampleSinkSequence = sequence;
    m_deviceSinkEngine->setSinkSequence(sequence);
}

void DeviceSinkAPI::setSampleSinkPluginGUI(PluginGUI *gui)
{
    if (m_sampleSinkPluginGUI != 0)
    {
        m_sampleSinkPluginGUI->destroy();
        m_sampleSinkId.clear();
    }

    m_sampleSinkPluginGUI = gui;
}

void DeviceSinkAPI::registerChannelInstance(const QString& channelName, PluginGUI* pluginGUI)
{
    m_channelInstanceRegistrations.append(ChannelInstanceRegistration(channelName, pluginGUI));
    renameChannelInstances();
}

void DeviceSinkAPI::removeChannelInstance(PluginGUI* pluginGUI)
{
    for(ChannelInstanceRegistrations::iterator it = m_channelInstanceRegistrations.begin(); it != m_channelInstanceRegistrations.end(); ++it)
    {
        if(it->m_gui == pluginGUI)
        {
            m_channelInstanceRegistrations.erase(it);
            break;
        }
    }

    renameChannelInstances();
}

void DeviceSinkAPI::renameChannelInstances()
{
    for(int i = 0; i < m_channelInstanceRegistrations.count(); i++)
    {
        m_channelInstanceRegistrations[i].m_gui->setName(QString("%1:%2").arg(m_channelInstanceRegistrations[i].m_channelName).arg(i));
    }
}

void DeviceSinkAPI::freeAll()
{
    for(int i = 0; i < m_channelInstanceRegistrations.count(); i++)
    {
        qDebug("DeviceSinkAPI::freeAll: destroying channel [%s]", qPrintable(m_channelInstanceRegistrations[i].m_channelName));
        m_channelInstanceRegistrations[i].m_gui->destroy();
    }


    if(m_sampleSinkPluginGUI != 0)
    {
        qDebug("DeviceSinkAPI::freeAll: destroying m_sampleSourcePluginGUI");
        m_deviceSinkEngine->setSink(0);
        m_sampleSinkPluginGUI->destroy();
        m_sampleSinkPluginGUI = 0;
        m_sampleSinkId.clear();
    }
}

void DeviceSinkAPI::loadSinkSettings(const Preset* preset)
{
    if (preset->isSourcePreset())
    {
        qDebug("DeviceSinkAPI::loadSinkSettings: Preset [%s | %s] is not a sink preset\n", qPrintable(preset->getGroup()), qPrintable(preset->getDescription()));
    }
    else
    {
        qDebug("DeviceSinkAPI::loadSinkSettings: Loading preset [%s | %s]\n", qPrintable(preset->getGroup()), qPrintable(preset->getDescription()));

        if(m_sampleSinkPluginGUI != 0)
        {
            // TODO: is "source" limiting to source devices?
            const QByteArray* sourceConfig = preset->findBestDeviceConfig(m_sampleSinkId, m_sampleSinkSerial, m_sampleSinkSequence);

            if (sourceConfig != 0)
            {
                qDebug() << "DeviceSinkAPI::loadSinkSettings: deserializing sink " << qPrintable(m_sampleSinkId);
                m_sampleSinkPluginGUI->deserialize(*sourceConfig);
            }

            qint64 centerFrequency = preset->getCenterFrequency();
            m_sampleSinkPluginGUI->setCenterFrequency(centerFrequency);
        }
    }
}

void DeviceSinkAPI::saveSinkSettings(Preset* preset)
{
    if (preset->isSourcePreset())
    {
        qDebug("DeviceSinkAPI::saveSinkSettings: not a sink preset");
    }
    else
    {
        qDebug("DeviceSinkAPI::saveSinkSettings: sink preset");

        if(m_sampleSinkPluginGUI != NULL)
        {
            // TODO: is "source" limiting to source devices?
            preset->addOrUpdateDeviceConfig(m_sampleSinkId, m_sampleSinkSerial, m_sampleSinkSequence, m_sampleSinkPluginGUI->serialize());
            preset->setCenterFrequency(m_sampleSinkPluginGUI->getCenterFrequency());
        }
    }
}

void DeviceSinkAPI::loadChannelSettings(const Preset *preset, PluginAPI *pluginAPI)
{
    if (preset->isSourcePreset())
    {
        qDebug("DeviceSinkAPI::loadChannelSettings: Loading preset [%s | %s] not a sink preset\n", qPrintable(preset->getGroup()), qPrintable(preset->getDescription()));
    }
    else
    {
        qDebug("DeviceSinkAPI::loadChannelSettings: Loading preset [%s | %s]\n", qPrintable(preset->getGroup()), qPrintable(preset->getDescription()));

        // Available channel plugins
        PluginAPI::ChannelRegistrations *channelRegistrations = pluginAPI->getRxChannelRegistrations();

        // copy currently open channels and clear list
        ChannelInstanceRegistrations openChannels = m_channelInstanceRegistrations;
        m_channelInstanceRegistrations.clear();

        for(int i = 0; i < preset->getChannelCount(); i++)
        {
            const Preset::ChannelConfig& channelConfig = preset->getChannelConfig(i);
            ChannelInstanceRegistration reg;

            // if we have one instance available already, use it

            for(int i = 0; i < openChannels.count(); i++)
            {
                qDebug("DeviceSourceAPI::loadChannelSettings: channels compare [%s] vs [%s]", qPrintable(openChannels[i].m_channelName), qPrintable(channelConfig.m_channel));

                if(openChannels[i].m_channelName == channelConfig.m_channel)
                {
                    qDebug("DeviceSourceAPI::loadChannelSettings: channel [%s] found", qPrintable(openChannels[i].m_channelName));
                    reg = openChannels.takeAt(i);
                    m_channelInstanceRegistrations.append(reg);
                    break;
                }
            }

            // if we haven't one already, create one

            if(reg.m_gui == NULL)
            {
                for(int i = 0; i < channelRegistrations->count(); i++)
                {
                    if((*channelRegistrations)[i].m_channelName == channelConfig.m_channel)
                    {
                        qDebug("DeviceSourceAPI::loadChannelSettings: creating new channel [%s]", qPrintable(channelConfig.m_channel));
                        reg = ChannelInstanceRegistration(channelConfig.m_channel, (*channelRegistrations)[i].m_plugin->createTxChannel(channelConfig.m_channel, this));
                        break;
                    }
                }
            }

            if(reg.m_gui != NULL)
            {
                qDebug("DeviceSourceAPI::loadChannelSettings: deserializing channel [%s]", qPrintable(channelConfig.m_channel));
                reg.m_gui->deserialize(channelConfig.m_config);
            }
        }

        // everything, that is still "available" is not needed anymore
        for(int i = 0; i < openChannels.count(); i++)
        {
            qDebug("DeviceSourceAPI::loadChannelSettings: destroying spare channel [%s]", qPrintable(openChannels[i].m_channelName));
            openChannels[i].m_gui->destroy();
        }

        renameChannelInstances();
    }
}

void DeviceSinkAPI::saveChannelSettings(Preset *preset)
{
    if (preset->isSourcePreset())
    {
        qDebug("DeviceSinkAPI::saveChannelSettings: not a sink preset");
    }
    else
    {
        qDebug("DeviceSinkAPI::saveChannelSettings: sink preset");

        qSort(m_channelInstanceRegistrations.begin(), m_channelInstanceRegistrations.end()); // sort by increasing delta frequency and type

        for(int i = 0; i < m_channelInstanceRegistrations.count(); i++)
        {
            preset->addChannel(m_channelInstanceRegistrations[i].m_channelName, m_channelInstanceRegistrations[i].m_gui->serialize());
        }
    }
}

// sort by increasing delta frequency and type (i.e. name)
bool DeviceSinkAPI::ChannelInstanceRegistration::operator<(const ChannelInstanceRegistration& other) const
{
    if (m_gui && other.m_gui)
    {
        if (m_gui->getCenterFrequency() == other.m_gui->getCenterFrequency())
        {
            return m_gui->getName() < other.m_gui->getName();
        }
        else
        {
            return m_gui->getCenterFrequency() < other.m_gui->getCenterFrequency();
        }
    }
    else
    {
        return false;
    }
}

