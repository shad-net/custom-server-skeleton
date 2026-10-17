#pragma once

#include "http_server.h"

void handleRequest(const HttpRequest& request, const QString& endpoint, const HttpServer::Responder& respond);
