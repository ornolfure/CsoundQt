/*
    Copyright (C) 2008-2016 Andres Cabrera
    mantaraya36@gmail.com

    This file is part of CsoundQt.

    CsoundQt is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    CsoundQt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy o    ScoreEvent *event = 0;
    while (!csound_event_queue.try_dequeue(event)) {
        delete event;
    }
    char *score_text = 0;
    while (!csound_score_queue.try_dequeue(score_text)) {
        free(score_text);
    }
f the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/


// code based partly on CsoundHtmlWrapper by Michael Gogins https://github.com/gogins/gogins.github.io/tree/master/csound_html5

#include "csoundhtmlwrapper.h"
#include <QApplication>
#include <QDebug>

CsoundHtmlWrapper::CsoundHtmlWrapper(QObject *parent) :
    QObject(parent),
    m_csoundEngine(nullptr),
    message_callback(nullptr),
    csound((CSOUND *)nullptr)
{
}

CsoundHtmlWrapper::~CsoundHtmlWrapper() {
}

void CsoundHtmlWrapper::setCsoundEngine(CsoundEngine *csEngine)
{
    m_csoundEngine = csEngine;
	if (m_csoundEngine) {
         csound.SetCsound(m_csoundEngine->getCsound());
    }
}

int CsoundHtmlWrapper::compileCsd(const QString &filename) {
    if (!csound.GetCsound()) {
        return -1;
    }
#if CS_APIVERSION>=4
    return csound.CompileCsd(filename.toLocal8Bit());
#else
    return csound.CompileCsd(filename.toLocal8Bit().data());
#endif
}

int CsoundHtmlWrapper::compileCsdText(const QString &text) {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.CompileCsdText(text.toLocal8Bit());
}

int CsoundHtmlWrapper::compileOrc(const QString &text) {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.CompileOrc(text.toLocal8Bit());
}

double CsoundHtmlWrapper::evalCode(const QString &text) {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.EvalCode(text.toLocal8Bit());
}

double CsoundHtmlWrapper::get0dBFS() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.Get0dBFS(); //cs->Get0dBFS();
}

int CsoundHtmlWrapper::getApiVersion() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.GetAPIVersion();
}

double CsoundHtmlWrapper::getControlChannel(const QString &name) {
    if (!csound.GetCsound()) {
        return -1;
    }
    int result = 0;
    double value = csound.GetControlChannel(name.toLocal8Bit(), &result);
    return value;
}

qint64 CsoundHtmlWrapper::getCurrentTimeSamples() { // FIXME: unknown type int64_t qint64
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.GetCurrentTimeSamples();
}

QString CsoundHtmlWrapper::getEnv(const QString &name) { // not sure, if it works... test with setGlobalEnv
    if (!csound.GetCsound()) {
        return QString();
    }
    return csound.GetEnv(name.toLocal8Bit());
}

int CsoundHtmlWrapper::getKsmps() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.GetKsmps();
}

int CsoundHtmlWrapper::getNchnls() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.GetNchnls();
}

int CsoundHtmlWrapper::getNchnlsInput() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.GetNchnlsInput();
}

QString CsoundHtmlWrapper::getOutputName() {
    if (!csound.GetCsound()) {
        return QString();
    }
    return QString(csound.GetOutputName());
}

double CsoundHtmlWrapper::getScoreOffsetSeconds() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.GetScoreOffsetSeconds();
}

double CsoundHtmlWrapper::getScoreTime() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.GetScoreTime();
}

int CsoundHtmlWrapper::getSr() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.GetSr();
}

QString CsoundHtmlWrapper::getStringChannel(const QString &name) {
    if (!csound.GetCsound()) {
        return QString();
    }
    char buffer[0x100];
    csound.GetStringChannel(name.toLocal8Bit(), buffer);
    return QString(buffer);
}

int CsoundHtmlWrapper::getVersion() {
    return csound.GetVersion();
}

bool CsoundHtmlWrapper::isPlaying() {
    if (!m_csoundEngine)
        return false;
    else
        return m_csoundEngine->isRunning();
}

int CsoundHtmlWrapper::isScorePending() {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.IsScorePending();
}

void CsoundHtmlWrapper::message(const QString &text) {
    if (!csound.GetCsound()) {
        return;
    }
    csound.Message("%s", text.toLocal8Bit().constData());
}

int CsoundHtmlWrapper::perform() {
    if (!csound.GetCsound()) {
        return -1;
    }
    // Perform in a separate thread of execution,
    // but do not reset Csound (CsoundEngine will do that).
    return csound.Perform(false);
}

int CsoundHtmlWrapper::readScore(const QString &text) {
    if (!csound.GetCsound()) {
        return -1;
    }
    csound.ReadScore(text.toLocal8Bit());
    return 0;
}

void CsoundHtmlWrapper::reset() {
    if (!csound.GetCsound()) {
        return;
    }
    csound.Reset();
}

void CsoundHtmlWrapper::rewindScore() {
    if (!csound.GetCsound()) {
        return;
    }
    csound.RewindScore();
}

int CsoundHtmlWrapper::runUtility(const QString &command, int argc, char **argv) {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.RunUtility(command.toLocal8Bit(), argc, argv); // probably does not work from JS due char **
}

int CsoundHtmlWrapper::scoreEvent(char opcode, const double *pfields, long field_count) {
    if (!csound.GetCsound()) {
        return -1;
    }
    csound.ScoreEvent(opcode, pfields, field_count);
    return 0;
}

void CsoundHtmlWrapper::setControlChannel(const QString &name, double value) {
    if (!csound.GetCsound()) {
        return;
    }
    csound.SetControlChannel(name.toLocal8Bit(), value);
}

int CsoundHtmlWrapper::setGlobalEnv(const QString &name, const QString &value) {
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.SetGlobalEnv(name.toLocal8Bit(), value.toLocal8Bit());
}

void CsoundHtmlWrapper::setInput(const QString &name){
    if (!csound.GetCsound()) {
        return;
    }
#if CS_APIVERSION>=4
    csound.SetInput(name.toLocal8Bit());
#else
    csound.SetInput(name.toLocal8Bit().data());
#endif
}

void CsoundHtmlWrapper::setMessageCallback(QObject *callback){
    qDebug();
    callback->dumpObjectInfo();
}

int CsoundHtmlWrapper::setOption(const QString &name){
    if (!csound.GetCsound()) {
        return -1;
    }
#if CS_APIVERSION>=4
    return csound.SetOption(name.toLocal8Bit().data());
#else
    return csound.SetOption(name.toLocal8Bit().data());
#endif
}

void CsoundHtmlWrapper::setOutput(const QString &name, const QString &type, const QString &format){
    if (!csound.GetCsound()) {
        return;
    }
#if CS_APIVERSION>=4
    csound.SetOutput(name.toLocal8Bit(), type.toLocal8Bit(), format.toLocal8Bit());
#else
    csound.SetOutput(name.toLocal8Bit().data(), type.toLocal8Bit().data(), format.toLocal8Bit().data());
#endif
}

void CsoundHtmlWrapper::setScoreOffsetSeconds(double value){
    if (!csound.GetCsound()) {
        return;
    }
    csound.SetScoreOffsetSeconds(value);
}

void CsoundHtmlWrapper::setScorePending(bool value){
    if (!csound.GetCsound()) {
        return;
    }
    csound.SetScorePending((int) value);
}

void CsoundHtmlWrapper::setStringChannel(const QString &name, const QString &value){
    if (!csound.GetCsound()) {
        return;
    }
    csound.SetStringChannel(name.toLocal8Bit(), value.toLocal8Bit().data());
}

int CsoundHtmlWrapper::start(){
    int result = 0;
    if (!csound.GetCsound()) {
        return -1;
    }
    result = csound.Start();
    return result;
}

void CsoundHtmlWrapper::stop(){
    if (!csound.GetCsound()) {
        return;
    }
    csound.Stop();
}

double CsoundHtmlWrapper::tableGet(int table_number, int index){
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.TableGet(table_number, index);
}

int CsoundHtmlWrapper::tableLength(int table_number){
    if (!csound.GetCsound()) {
        return -1;
    }
    return csound.TableLength(table_number);
}

void CsoundHtmlWrapper::tableSet(int table_number, int index, double value){
    if (!csound.GetCsound()) {
        return;
    }
    csound.TableSet(table_number, index, value);
}



