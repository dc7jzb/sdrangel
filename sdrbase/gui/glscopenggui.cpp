///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017 F4EXB                                                      //
// written by Edouard Griffiths                                                  //
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

#include "glscopenggui.h"
#include "ui_glscopenggui.h"
#include "util/simpleserializer.h"

GLScopeNGGUI::GLScopeNGGUI(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GLScopeNGGUI),
    m_messageQueue(0),
    m_glScope(0),
    m_scopeVis(0),
    m_sampleRate(0)
{
    ui->setupUi(this);
}

GLScopeNGGUI::~GLScopeNGGUI()
{
    delete ui;
}

void GLScopeNGGUI::setBuddies(MessageQueue* messageQueue, ScopeVisNG* scopeVis, GLScopeNG* glScope)
{
    m_messageQueue = messageQueue;
    m_scopeVis = scopeVis;
    m_glScope = glScope;
    applySettings();
}

void GLScopeNGGUI::setSampleRate(int sampleRate)
{
    m_sampleRate = sampleRate;
}

void GLScopeNGGUI::resetToDefaults()
{
}


QByteArray GLScopeNGGUI::serialize() const
{
    // TODO
    SimpleSerializer s(1);
    return s.final();
}

bool GLScopeNGGUI::deserialize(const QByteArray& data)
{
    // TODO
    SimpleDeserializer d(data);

    if(!d.isValid()) {
        resetToDefaults();
        return false;
    }

    if(d.getVersion() == 1) {
        return true;
    } else {
        resetToDefaults();
        return false;
    }
}

void GLScopeNGGUI::applySettings()
{
}

bool GLScopeNGGUI::handleMessage(Message* message)
{
    return false;
}