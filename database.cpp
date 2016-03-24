/****************************************************************************
**
** Druid - Is a piece of program for read text file and store as json data.
** This is part of it's code.
** Copyright (C) 2016  Gustavo Brondani Schenkel
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "database.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QDebug>
#include <QtCore/QProcess>

Database::Database(QObject *parent) : QObject(parent)
{
    qDebug() << "teste";
    startServer();
}

void Database::insertToDB(QRegularExpressionMatch match){
    /* Job entry's RegExp
    "(?<bufferReadDate>\\d{2}/\\d{2}/\\d{4})\\s"
    "(?<bufferReadTime>\\d{2}:\\d{2}:\\d{2})\\s-\\s"
    "(?<machine>\\w{4})\\."
    "(?<code>\\w{6}\\d{2})\\s+"
    "(?<jobName>\\w+)\\s+"
    "ZN(?<osNumber>\\d{6})\\s+"
    "(?<jobNumber>\\d{5})\\s"
    "(?<entryDate>\\d{2}/\\d{2}/\\d{2})\\s"
    "(?<entryTime>\\d{2}:\\d{2}:\\d{2})"
    */

    QJsonObject serviceOrder;
    serviceOrder["osNumber"] = match.captured("osNumber");
    serviceOrder["entryDate"] = match.captured("entryDate");
    serviceOrder["entryTime"] = match.captured("entryTime");

    QJsonObject job;
    job["jobName"] = match.captured("jobName");
    job["jobNumber"] = match.captured("jobNumber");
    job["machine"] = match.captured("machine");

    QJsonArray jobs;
    jobs.append(job);

    serviceOrder["jobs"] = jobs;

    QJsonDocument jDoc;
    jDoc.setObject(serviceOrder);

    /*qDebug() << jDoc;

    QJsonObject bla;
    bla["jobName"] = "PKOS382";
    bla["jobNumber"] = "48597";
    bla["machine"] = "SYSB";
    QJsonObject guga = jDoc.object();
    QJsonArray jobs1 = guga["jobs"].toArray();
    jobs1.append(bla);
    guga["jobs"] = jobs1;
    jDoc.setObject(guga);

    qDebug() << guga;*/

}

void Database::inputData(QRegularExpressionMatch match)
{
    if (match.captured("code") == "PWETRT10") {
        qDebug() << "match okay";
        insertToDB(match);
    }

}

void Database::client()
{
    QString program = "C:/mongodb/bin/mongod.exe";
    QStringList arguments;
    arguments << "--journal";

    QProcess *server = new QProcess();
    server->start(program, arguments);
}

void Database::startServer()
{
    QString program = "C:/mongodb/bin/mongod.exe";
    QStringList arguments;
    arguments << "--journal";

    QProcess *server = new QProcess();
    server->start(program, arguments);
}
