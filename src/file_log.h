#pragma once

#include <QString>

bool startFileLog(const QString& path, qint64 maxBytes, QString* error);
